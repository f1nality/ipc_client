#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

#define PORT 10000

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
public:
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
