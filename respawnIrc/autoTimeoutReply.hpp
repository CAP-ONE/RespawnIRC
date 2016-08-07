#ifndef AUTOTIMEOUTREPLY_HPP
#define AUTOTIMEOUTREPLY_HPP

#include <QObject>

class QNetworkReply;
class QTimer;

class autoTimeoutReplyClass : public QObject
{
    Q_OBJECT
public:
    autoTimeoutReplyClass(QObject* parent = 0);
    QNetworkReply* resetReply(QNetworkReply* newReply = nullptr);
    void updateTimeoutTime(int newTimeoutTimeInSeconds = 0);
public slots:
    void timeoutCurrentReply();
private:
    QNetworkReply* currentReply = nullptr;
    QTimer* timerForTimeout;
};

#endif
