#pragma once

#include <QObject>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

class NetworkManager : public QObject
{
    Q_OBJECT

    public:
        explicit NetworkManager(bool isServer = false, QObject *parent = nullptr);
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
