#pragma once

#include <QObject>
#include <QJsonObject>
#include <functional>
#include "../headers/NetworkManager.hpp"

class Q_DECL_EXPORT HandlerManager
{

    public:
        HandlerManager();
        ~HandlerManager();
    private:
        NetworkManager *networkManager = new NetworkManager(true);
        std::map<QString, std::function<void(QJsonObject)>> handlerList;
        QString peerReceiver;

        void handleJson(QJsonObject jsonReceived);
        void onCheckPeer(QJsonObject json);
        void onCheckPeerSuccess(QJsonObject json);

    signals:
        void checkPeerSuccessSignal();
};
