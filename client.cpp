#include "client.h"

Client::Client(int port)
{
    socket = new QTcpSocket();

    connect(socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost("192.168.173.67", port);

}

Client::Client(QString host, int port)
{
    socket = new QTcpSocket();

    connect(socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost(host, port);

}

void Client::connectedToServer() {
    emit onConnectedToServer();
}

void Client::readData()
{
    emit messageReceived(QString(socket->readLine()));
}

void Client::sendData(QString data)
{
    if (socket->isOpen()) {
        socket->write(data.toLatin1());
    }
}
