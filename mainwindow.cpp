#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(BROADCAST_PORT, QUdpSocket::ShareAddress);

    initializeState();
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onConnectedButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeState() {
    ui->sendButton->setEnabled(false);
}

void MainWindow::processPendingDatagrams()
 {
     if (udpSocket->hasPendingDatagrams()) {
         QHostAddress addr;
         QByteArray datagram;
         datagram.resize(udpSocket->pendingDatagramSize());
         udpSocket->readDatagram(datagram.data(), datagram.size(), &addr);
         ui->listWidget->addItem(tr("Received datagram: \"%1\"").arg(datagram.data()));

         ui->sendButton->setEnabled(true);
         client = new Client(addr, PORT);
     }
 }

void MainWindow::onConnectedToServer()
{
    ui->listWidget->addItem("Connected");
    client->sendData(QString("Hello World"));
}

void MainWindow::onMessageReceived(QString* data)
{
    QListWidgetItem *item = new QListWidgetItem(*data);
    ui->listWidget->addItem(item);
    qDebug() << data;
}

void MainWindow::onConnectedButtonClicked()
{
    if (client == NULL)
    {
        ui->listWidget->addItem("Connect to port 10000");
        client = new Client(PORT);
        connect(client, SIGNAL(onConnectedToServer()), this, SLOT(onConnectedToServer()));
        connect(client, SIGNAL(messageReceived(QString)), this, SLOT(onMessageReceived(QString*)));
    }
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
