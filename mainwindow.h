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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void onConnectedToServer();
    void onMessageReceived(QString data);
    void onConnectedButtonClicked();
    void onSendButtonClicked();
};

#endif // MAINWINDOW_H
