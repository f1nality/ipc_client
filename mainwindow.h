#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Client *client;
    QTimer *timer;
    QUdpSocket* udpSocket;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initializeState();
private slots:
    void onConnectedToServer();
    void onMessageReceived(QString* data);
    void onConnectedButtonClicked();
    void onSendButtonClicked();
    void processPendingDatagrams();
};

#endif // MAINWINDOW_H
