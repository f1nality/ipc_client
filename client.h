#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QtNetwork>

#define PORT 10000
#define BROADCAST_PORT 10001

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    int port;
    QUdpSocket *udpSocket;
public:
    Client();
    Client(int port);
    void startConnectToServer(QHostAddress);
    void startListenIp(int);
signals:
    void messageReceived(QString);
    void connectedToServer();
    void serverFound();

public slots:
    void readData();
    void sendData(QString data);
    void onConnectedToServer();
    void processPendingDatagrams();
};

#endif // CLIENT_H
