#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    client = NULL;

    ui->setupUi(this);

    client = new Client(PORT);
    client->startListenIp(BROADCAST_PORT);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onConnectedButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));
    connect(client, SIGNAL(connectedToServer()), this, SLOT(onConnectedToServer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onConnectedToServer()
{
    ui->listWidget->addItem("Connect to port 10000");
    connect(client, SIGNAL(messageReceived(QString)), this, SLOT(onMessageReceived(QString)));

    ui->listWidget->addItem("Connected");
    client->sendData(QString("Hello World"));
}

void MainWindow::onMessageReceived(QString data)
{
    QListWidgetItem *item = new QListWidgetItem(data);
    ui->listWidget->addItem(item);
    qDebug() << data;
}

void MainWindow::onConnectedButtonClicked()
{
}

void MainWindow::onSendButtonClicked()
{
    if (client == NULL) {
        return;
    }

    QString msg = ui->plainTextEdit->toPlainText();
    ui->listWidget->addItem(msg);
    client->sendData(msg);
}
