#include <QCoreApplication>
#include "ircbot.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
      IrcBot myBot("irc.freenode.net", 6667, "s3nder2", "s3nder2", "sayhifromqt", "s3nder2");
      myBot.Listen("irc.freenode.net", 6667, "s3nder2", "s3nder2", "sayhifromqt", "s3nder2");
      myBot.sendMessage("سلام من آمدم :D", "sayhifromqt");
    return a.exec();
}
