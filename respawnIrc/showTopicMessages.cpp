#include "showTopicMessages.hpp"
#include "parsingTool.hpp"

showTopicMessagesClass::showTopicMessagesClass(QList<QString>* newListOfIgnoredPseudo, QWidget* parent) : QWidget(parent)
{
    messagesBox.setReadOnly(true);
    messagesBox.setOpenExternalLinks(true);
    timerForGetMessage.setInterval(4000);
    timerForGetMessage.stop();
    listOfIgnoredPseudo = newListOfIgnoredPseudo;
    messagesStatus = "Rien.";
    reply = 0;
    firstTimeGetMessages = true;
    retrievesMessage = false;
    idOfLastMessage = 0;
    linkHasChanged = false;

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&messagesBox);
    layout->setMargin(0);

    setLayout(layout);

    connect(&timerForGetMessage, SIGNAL(timeout()), SLOT(getMessages()));
}

void showTopicMessagesClass::startGetMessage()
{
    if(retrievesMessage == false && topicLink.isEmpty() == false)
    {
        timerForGetMessage.start();
        getMessages();
    }
}

const QList<QPair<QString, QString> >& showTopicMessagesClass::getListOfInput()
{
    return listOfInput;
}

QString showTopicMessagesClass::getTopicLink()
{
    return topicLink;
}

QString showTopicMessagesClass::getTopicName()
{
    return topicName;
}

QString showTopicMessagesClass::getCaptchaLink()
{
    return captchaLink;
}

QString showTopicMessagesClass::getMessagesStatus()
{
    return messagesStatus;
}

QString showTopicMessagesClass::getNumberOfConnected()
{
    return numberOfConnected;
}

void showTopicMessagesClass::setNewCookies(QList<QNetworkCookie> newCookies, QString newPseudoOfUser)
{
    networkManager.setCookieJar(new QNetworkCookieJar(this)); //fuite ?
    networkManager.cookieJar()->setCookiesFromUrl(newCookies, QUrl("http://www.jeuxvideo.com"));
    pseudoOfUser = newPseudoOfUser;

    startGetMessage();
}

void showTopicMessagesClass::setNewTopic(QString newTopic)
{
    messagesBox.clear();
    topicName.clear();
    topicLink = newTopic;
    linkHasChanged = true;
    firstTimeGetMessages = true;
    idOfLastMessage = 0;

    setMessageStatus("Nouveau topic.");
    setNumberOfConnected("", true);
    startGetMessage();
}

void showTopicMessagesClass::setMessageStatus(QString newStatus)
{
    messagesStatus = newStatus;
    emit newMessageStatus();
}

void showTopicMessagesClass::setNumberOfConnected(QString newNumber, bool forceSet)
{
    if(newNumber.isEmpty() == false || forceSet == true)
    {
        if(newNumber != numberOfConnected)
        {
            numberOfConnected = newNumber;
            emit newNumberOfConnected();
        }
    }
}

void showTopicMessagesClass::getMessages()
{
    if(retrievesMessage == false)
    {
        retrievesMessage = true;

        if(reply == 0)
        {
            QNetworkRequest request = parsingToolClass::buildRequestWithThisUrl(topicLink);
            setMessageStatus("Récupération des messages en cours...");
            linkHasChanged = false;
            reply = networkManager.get(request);
            connect(reply, SIGNAL(finished()), this, SLOT(analyzeMessages()));
        }
        else
        {
            retrievesMessage = false;
        }
    }
}

void showTopicMessagesClass::analyzeMessages()
{
    QString newTopicLink;
    QString colorOfPseudo;
    QString source = reply->readAll();
    reply->deleteLater();
    reply = 0;

    if(linkHasChanged == true)
    {
        retrievesMessage = false;
        return;
    }

    setMessageStatus("Récupération des messages terminé !");
    setNumberOfConnected(parsingToolClass::getNumberOfConnected(source));

    newTopicLink = parsingToolClass::getLastPageOfTopic(source);

    if(firstTimeGetMessages == true)
    {
        topicName = parsingToolClass::getNameOfTopic(source);

        if(topicName.isEmpty() == false)
        {
            emit newNameForTopic(topicName);
        }
    }

//a changer // enfin j'sais pas
    if(firstTimeGetMessages == false || newTopicLink.isEmpty() == true)
    {
        QList<int> listOfMessageID = parsingToolClass::getListOfMessageID(source);
        QList<QString> listOfPseudo = parsingToolClass::getListOfPseudo(source);
        QList<QString> listOfDate = parsingToolClass::getListOfDate(source);
        QList<QString> listOfMessage = parsingToolClass::getListOfMessage(source);

        if((listOfMessageID.size() == listOfPseudo.size() && listOfPseudo.size() == listOfDate.size() && listOfDate.size() == listOfMessage.size()) == false || listOfDate.size() == 0)
        {
            QMessageBox messageBox;
            topicLink.clear();
            topicName.clear();
            timerForGetMessage.stop();
            messagesBox.clear();
            setMessageStatus("Erreur.");
            setNumberOfConnected("", true);
            messageBox.warning(this, "Erreur", "Un problème est survenu lors de la récupération des messages.");
            retrievesMessage = false;
            return;
        }

        for(int i = 0; i < listOfMessageID.size(); ++i)
        {
            if(listOfMessageID.at(i) > idOfLastMessage && listOfIgnoredPseudo->indexOf(listOfPseudo.at(i).toLower()) == -1)
            {
                if(pseudoOfUser.toLower() == listOfPseudo.at(i).toLower())
                {
                    colorOfPseudo = "blue";
                }
                else
                {
                    colorOfPseudo = "dimgrey";
                }

                messagesBox.append("<table><tr><td>[<a style=\"color: black;text-decoration: none\" href=\"http://www.jeuxvideo.com/" + listOfPseudo.at(i).toLower() +
                                   "/forums/message/" + QString::number(listOfMessageID.at(i)) + "\">" + listOfDate.at(i) +
                                   "</a>] &lt;<a href=\"http://www.jeuxvideo.com/profil/" + listOfPseudo.at(i).toLower() +
                                   "?mode=infos\"><span style=\"color: " + colorOfPseudo + ";text-decoration: none\">" +
                                   listOfPseudo.at(i) + "</span></a>&gt;</td><td>" + listOfMessage.at(i) + "</td></tr></table>");
                messagesBox.verticalScrollBar()->updateGeometry();
                messagesBox.verticalScrollBar()->setValue(messagesBox.verticalScrollBar()->maximum());
                idOfLastMessage = listOfMessageID.at(i);
                emit newMessagesAvailable();
            }
        }
    }
//fin
    if(pseudoOfUser.isEmpty() == false)
    {
        listOfInput.clear();
        parsingToolClass::getListOfHiddenInputFromThisForm(source, "form-post-topic form-post-message", listOfInput);
        captchaLink = parsingToolClass::getCaptchaLink(source);
    }

    firstTimeGetMessages = false;
    retrievesMessage = false;

    if(newTopicLink.isEmpty() == false)
    {
        topicLink = newTopicLink;
        startGetMessage();
    }
}
