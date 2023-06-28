#ifndef tcpserver_H
#define tcpserver_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QVector>
#include <QString>

class tcpserver : public QObject{
    Q_OBJECT
public:
    explicit tcpserver(QObject *parent = nullptr);
    ~tcpserver();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    void sendToClient(QString resp, int position);
private:
    QTcpServer * mTcpServer;
    QVector<QTcpSocket *> TcpSocket;
    int count_client = 0;
};
#endif
