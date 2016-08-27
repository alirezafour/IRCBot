#ifndef IRCBOT_H
#define IRCBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMap>
#include <functional>
#include <QString>

class IrcBot : public QObject
{
    Q_OBJECT
public:
    explicit IrcBot(QObject *parent = 0);
    IrcBot(QString server, int port, QString nickname, QString realname, QString channel, QString username);
    void Listen(QString server, int port, QString nickname, QString realname, QString channel, QString username) const;
    void sendMessage(QString message, QString channel) const;

signals:

public slots:

private:
    void sendNick(QString nickname) const;
    void sendUser(QString username, QString realname) const;
    void sendJoin(QString channel) const;
    //Members
    QTcpSocket *IRCBotSocket;
    QString serverBot;
    int portBot;
    QString nicknameBot;
    QString realnameBot;
    QString channelBot;
    QString usernameBot;
private slots:
    void connectedBot(); //Does not need to be named this.
    void disconnectedBot();
    void readyReadBot();
};

#endif // IRCBOT_H
