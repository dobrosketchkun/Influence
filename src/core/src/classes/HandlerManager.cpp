#include "../headers/HandlerManager.hpp"

HandlerManager::HandlerManager(QObject *parent)  : QObject(parent)
{
    using namespace std::placeholders;
    handlerList = {
            {"checkPeer", std::bind(&HandlerManager::onCheckPeer, this, _1)},
            {"checkPeerSuccess", std::bind(&HandlerManager::onCheckPeerSuccess, this, _1)},
    };

    QObject::connect(networkManager, &NetworkManager::jsonReceived, this, &HandlerManager::handleJson);
}

HandlerManager::~HandlerManager()
{
    delete networkManager;
}

void HandlerManager::handleJson(QJsonObject jsonReceived)
{
    QString action = jsonReceived["action"].toString();
    peerReceiver = jsonReceived["peerID"].toString();
    handlerList[action](jsonReceived);
}

void HandlerManager::onCheckPeer(QJsonObject json)
{
    QJsonObject jsonSend;
    jsonSend["action"] = "checkPeerSuccess";
    jsonSend["peerID"] = *networkManager->myIPv6;
    networkManager->sendDatagram(jsonSend, peerReceiver);
}

void HandlerManager::onCheckPeerSuccess(QJsonObject json)
{
    emit checkPeerSuccessSignal();
}
