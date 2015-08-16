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
    errorMode = false;

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

void showTopicMessagesClass::setTopicToErrorMode()
{
    if(errorMode == false)
    {
        QMessageBox messageBox;
        errorMode = true;
        if(firstTimeGetMessages == true)
        {
            topicLink.clear();
            topicName.clear();
            timerForGetMessage.stop();
            messagesBox.clear();
            setMessageStatus("Erreur, topic invalide.");
            setNumberOfConnected("", true);
            messageBox.warning(this, "Erreur", "Le topic n'existe pas.");
        }
        else
        {
            setMessageStatus("Erreur, impossible de récupérer les messages.");
            messageBox.warning(this, "Erreur", "Le programme n'a pas réussi à récupérer les messages cette fois ci, mais il continuera à essayer tant que l'onglet est ouvert.");
        }
    }
    else
    {
        setMessageStatus("Erreur, impossible de récupérer les messages.");
    }
    retrievesMessage = false;
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
    QString colorOfDate;
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

    if(firstTimeGetMessages == false || newTopicLink.isEmpty() == true)
    {
        QList<messageStruct> listOfEntireMessage = parsingToolClass::getListOfEntireMessages(source);

        if(listOfEntireMessage.size() == 0)
        {
            setTopicToErrorMode();
            return;
        }
        else
        {
            errorMode = false;
        }

        for(int i = 0; i < listOfEntireMessage.size(); ++i)
        {
            QMap<int, QString>::const_iterator listOfEditIterator = listOfEdit.find(listOfEntireMessage.at(i).idOfMessage);
            if((listOfEntireMessage.at(i).idOfMessage > idOfLastMessage || (listOfEditIterator != listOfEdit.end() && listOfEditIterator.value() != listOfEntireMessage.at(i).lastTimeEdit))
                    && listOfIgnoredPseudo->indexOf(listOfEntireMessage.at(i).pseudo.toLower()) == -1)
            {
                if(pseudoOfUser.toLower() == listOfEntireMessage.at(i).pseudo.toLower())
                {
                    colorOfPseudo = "blue";
                }
                else
                {
                    colorOfPseudo = "dimgrey";
                }

                if(listOfEditIterator != listOfEdit.end() && listOfEditIterator.value() != listOfEntireMessage.at(i).lastTimeEdit)
                {
                    colorOfDate = "green";
                }
                else
                {
                    colorOfDate = "black";
                    idOfLastMessage = listOfEntireMessage.at(i).idOfMessage;
                }

                messagesBox.append("<table><tr><td>[<a style=\"color: " + colorOfDate + ";text-decoration: none\" href=\"http://www.jeuxvideo.com/" +
                                   listOfEntireMessage.at(i).pseudo.toLower() +
                                   "/forums/message/" + QString::number(listOfEntireMessage.at(i).idOfMessage) + "\">" + listOfEntireMessage.at(i).date +
                                   "</a>] &lt;<a href=\"http://www.jeuxvideo.com/profil/" + listOfEntireMessage.at(i).pseudo.toLower() +
                                   "?mode=infos\"><span style=\"color: " + colorOfPseudo + ";text-decoration: none\">" +
                                   listOfEntireMessage.at(i).pseudo + "</span></a>&gt;</td><td>" + listOfEntireMessage.at(i).message + "</td></tr></table>");
                messagesBox.verticalScrollBar()->updateGeometry();
                messagesBox.verticalScrollBar()->setValue(messagesBox.verticalScrollBar()->maximum());
                listOfEdit[listOfEntireMessage.at(i).idOfMessage] = listOfEntireMessage.at(i).lastTimeEdit;
                emit newMessagesAvailable();
            }
        }

        while(listOfEdit.size() > 20)
        {
            listOfEdit.erase(listOfEdit.begin());
        }
    }

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
