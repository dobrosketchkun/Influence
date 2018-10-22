#pragma once

#include <QObject>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

class NetworkManager
{
    Q_OBJECT

    public:

        NetworkManager(bool isServer);
        ~NetworkManager();

        void sendDatagram(QJsonObject data, QString ipv6);

        static QString localIPv6();

        const QString *myIPv6;

    private:

        QUdpSocket* udpSocket;

    private slots:

        void processTheDatagram();

    signals:

        void jsonReceived(QJsonObject &jsonReceived);

};
