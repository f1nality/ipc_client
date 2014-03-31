#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

#define PORT 10000
#define BROADCAST_PORT 10001

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
public:
    Client(QString host, int port);
    Client(int port);
signals:
    void onMessageReceived(QString*);
    void onConnectedToServer();
    void messageReceived(QString);
public slots:
    void readData();
    void sendData(QString data);
    void connectedToServer();
};

#endif // CLIENT_H
