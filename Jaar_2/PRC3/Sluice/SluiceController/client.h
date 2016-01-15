#pragma once

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QElapsedTimer>

#define timeOut 1000

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);
    ~Client();
    QString sendMessage(QString message);
    bool noResponse;

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    QElapsedTimer* timer;
    QString replyMessage;
};

