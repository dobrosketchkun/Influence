#include "../headers/NetworkManager.hpp"

NetworkManager::NetworkManager(QObject *parent, bool isServer)  : QObject(parent)
{
    udpSocket = new QUdpSocket();

    if (isServer)
    {
        udpSocket->bind(QHostAddress::AnyIPv6, 16532);
        QObject::connect(udpSocket, &QUdpSocket::readyRead, this, &NetworkManager::processTheDatagram);
    }

    myIPv6 = new QString(localIPv6());
}

void NetworkManager::sendDatagram(QJsonObject data, QString ipv6)
{
    QHostAddress ip = QHostAddress(ipv6);
    QByteArray baDatagram;
    QJsonDocument jBuff = QJsonDocument(data);
    baDatagram = jBuff.toJson(QJsonDocument::Compact);
    udpSocket->writeDatagram(baDatagram, ip, 16532);
}

void NetworkManager::processTheDatagram()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(udpSocket->pendingDatagramSize()) ;
        udpSocket->readDatagram (baDatagram.data(), baDatagram.size()) ;
    } while (udpSocket->hasPendingDatagrams()) ;

    QJsonDocument jbuff = QJsonDocument::fromJson(baDatagram);
    QJsonObject j = QJsonObject(jbuff.object());
    emit jsonReceived(j);
}

QString NetworkManager::localIPv6()
{
    QHostAddress address;
    QString addressString;
    foreach (address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv6Protocol && address != QHostAddress(QHostAddress::LocalHostIPv6) && (address.toString()).contains("fc"))
        {
            addressString = address.toString();
            break;
        }
        else
        {
            addressString = "null";
        }
    }
    return addressString;
}

NetworkManager::~NetworkManager()
{
    delete udpSocket;
}
