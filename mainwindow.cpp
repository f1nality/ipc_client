#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onConnectedButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
        connect(client, SIGNAL(messageReceived(QString*)), this, SLOT(onMessageReceived(QString*)));
    }
}

void MainWindow::onSendButtonClicked()
{
    ui->listWidget->addItem(ui->plainTextEdit->toPlainText());
}
