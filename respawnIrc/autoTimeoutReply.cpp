#include "autoTimeoutReply.hpp"

autoTimeoutReplyClass::autoTimeoutReplyClass()
{
    timerForTimeout.setTimerType(Qt::CoarseTimer);
    timerForTimeout.setSingleShot(true);
    timerForTimeout.setInterval(8000);
    timerForTimeout.stop();
    currentReply = 0;

    QObject::connect(&timerForTimeout, &QTimer::timeout, this, &autoTimeoutReplyClass::timeoutCurrentReply);
}

QNetworkReply* autoTimeoutReplyClass::resetReply(QNetworkReply* newReply)
{
    currentReply = newReply;

    if(currentReply != 0)
    {
        timerForTimeout.start();
    }
    else
    {
        timerForTimeout.stop();
    }

    return currentReply;
}

void autoTimeoutReplyClass::timeoutCurrentReply()
{
    if(currentReply != 0)
    {
        if(currentReply->isRunning() == true)
        {
            currentReply->abort();
        }
    }
}
