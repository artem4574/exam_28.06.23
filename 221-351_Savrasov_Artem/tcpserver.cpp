#include "tcpserver.h"
#include <QDebug>
#include <QCoreApplication>

tcpserver::~tcpserver(){
    mTcpServer->close();
}

tcpserver::tcpserver(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &tcpserver::slotNewConnection);
    if(!mTcpServer->listen(QHostAddress::Any, 33333)) qDebug() << "server is not started";
        else qDebug() << "server is started";
}

void tcpserver::slotNewConnection(){
    if (count_client >= 6) return; //  ограничение количества клиентов
    QTcpSocket * my_socket;
    my_socket = mTcpServer->nextPendingConnection();
    connect(my_socket, &QTcpSocket::readyRead, this, &tcpserver::slotServerRead);
    connect(my_socket, &QTcpSocket::disconnected, this, &tcpserver::slotClientDisconnected);
    count_client++;
    TcpSocket.append(my_socket);
}

void tcpserver::slotServerRead(){
    QByteArray read_arr;
    QString answer;
    QString str;
    int k = 0;
    QTcpSocket* my_socket = (QTcpSocket*)sender();
    while(my_socket->bytesAvailable()>0){
        read_arr = my_socket->readAll();
        str.append(read_arr);
    }
    read_arr.clear();
    for(int i = 0; i< TcpSocket.size();i++){
        if(my_socket == TcpSocket.at(i)) break;
        k++;
    }
    answer = str.trimmed();
    for (int i = 2; i < str.size();i++) {
        if((i+1)%3==0) answer.append(str.at(i));
    }
    sendToClient(answer + "\n\r", k);
}

void tcpserver::slotClientDisconnected(){
    QTcpSocket * disSoc = (QTcpSocket*)sender();
    for(int i = 0; i<TcpSocket.size();i++){
        if(disSoc == TcpSocket.at(i)){
            TcpSocket.removeAt(i);
            count_client--;
            break;
        }
    }
}

void tcpserver::sendToClient(QString resp, int position){
    for(int i = 0; i<TcpSocket.size();i++)
        if (i != position) TcpSocket[i]->write(resp.toUtf8());
}
