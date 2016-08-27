#include "ircbot.h"

IrcBot::IrcBot(QObject *parent) : QObject(parent), IRCBotSocket(new QTcpSocket(this))
{
    qDebug() << "IRCBot Object created";
}

IrcBot::IrcBot(QString server, int port, QString nickname, QString realname, QString channel, QString username) :
    serverBot(server), portBot(port), nicknameBot(nickname),  realnameBot(realname),
    channelBot(channel), usernameBot(username), IRCBotSocket(new QTcpSocket(this))
{
    qDebug() << "IRCBot Object created";
}

void IrcBot::Listen(QString server, int port, QString nickname, QString realname, QString channel, QString username) const
{
    connect(IRCBotSocket, SIGNAL(connected()), this, SLOT(connectedBot()));
    connect(IRCBotSocket, SIGNAL(disconnected()), this, SLOT(disconnectedBot()));
    connect(IRCBotSocket, SIGNAL(readyRead()), this, SLOT(readyReadBot()));

    IRCBotSocket->connectToHost(server, port);

    //Alright, I have a pending request to connect to an IRC server. I'll wait xTime to connect or else I'll just say I could not.
    if (!IRCBotSocket->waitForConnected()) //wait 3 sec
    {
        qDebug() << "Could not connect to irc server" << IRCBotSocket->errorString();
    } else
    {
        qDebug() << "We are now connect to IRC. Yeah !!!";
    }
}

void IrcBot::sendMessage(QString message, QString channel) const
{
    QByteArray package;
    package.append("PRIVMSG #");
    package.append(channel);
    package.append(" :");
    package.append(message);
    package.append("\r\n");
    IRCBotSocket->write(package);
    IRCBotSocket->flush();
}

void IrcBot::sendNick(QString nickname) const
{
    QByteArray package;
    package.append("NICK ");
    package.append(nickname);
    package.append("\r\n");
    IRCBotSocket->write(package);
    IRCBotSocket->flush();
}

void IrcBot::sendUser(QString username, QString realname) const
{
    QByteArray package;
    package.append("USER ");
    package.append(username);
    package.append(" 8 *; ");
    package.append(realname);
    package.append("\r\n");
    IRCBotSocket->write(package);
    IRCBotSocket->flush();
}

void IrcBot::sendJoin(QString channel) const
{
    QByteArray package;
    package.append("JOIN #");
    package.append(channel);
    package.append("\r\n");
    IRCBotSocket->write(package);
    IRCBotSocket->flush();
}

void IrcBot::connectedBot()
{
    this->sendNick(nicknameBot);
    this->sendUser(usernameBot, realnameBot);
    this->sendJoin(channelBot);
}

void IrcBot::disconnectedBot()
{

}

void IrcBot::readyReadBot()
{
    QByteArray array;
    while (!(array = IRCBotSocket->readLine()).isNull()) {
        qDebug() << array;
    }
}
