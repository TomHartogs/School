#include "client.h"
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

QT_USE_NAMESPACE

Client::Client(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent), noResponse(false), m_url(url), m_debug(debug), replyMessage("")
{
  if (m_debug)
    qDebug() << "WebSocket server:" << url;

  connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
  connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);

  timer = new QElapsedTimer();
  timer->start();

  m_webSocket.open(m_url);
  while(m_webSocket.state() != QAbstractSocket::ConnectedState)
  {
      if(timer->elapsed() > timeOut)
      {
        qDebug() << "Failed to connect";
        exit(EXIT_FAILURE);
      }
    QCoreApplication::processEvents();
  }
}

Client::~Client()
{
  m_webSocket.close();
}

QString Client::sendMessage(QString message)
{
  timer->restart();

  m_webSocket.sendTextMessage(message);
  replyMessage = "";
  while(replyMessage == "")
  {
      if(timer->elapsed() > timeOut)
        return "Response time-out";
    QCoreApplication::processEvents();
  }
  return replyMessage;
}

void Client::onConnected()
{
  if (m_debug)
    qDebug() << "WebSocket connected";
  connect(&m_webSocket, &QWebSocket::textMessageReceived,this, &Client::onTextMessageReceived);
}

void Client::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    replyMessage = message;
}
