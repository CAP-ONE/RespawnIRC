#include "showTopicMessages.hpp"
#include "parsingTool.hpp"
#include "settingTool.hpp"

showTopicMessagesClass::showTopicMessagesClass(QList<QString>* newListOfIgnoredPseudo, QList<pseudoWithColorStruct>* newListOfColorPseudo, QWidget* parent) : QWidget(parent)
{
    messagesBox.setReadOnly(true);
    messagesBox.setOpenExternalLinks(false);
    messagesBox.setOpenLinks(false);
    timerForGetMessage.setTimerType(Qt::CoarseTimer);
    updateSettingInfo(false);
    timerForGetMessage.stop();
    listOfIgnoredPseudo = newListOfIgnoredPseudo;
    listOfColorPseudo = newListOfColorPseudo;
    messagesStatus = "Rien.";
    replyForFirstPage = 0;
    replyForSecondPage = 0;
    replyForEditInfo = 0;
    replyForQuoteInfo = 0;
    firstTimeGetMessages = true;
    retrievesMessage = false;
    idOfLastMessage = 0;
    idOfLastMessageOfUser = 0;
    linkHasChanged = false;
    errorMode = false;
    secondPageLoading = false;

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(&messagesBox, 1);
    layout->addWidget(&showListOfTopic);
    layout->setMargin(0);

    setLayout(layout);

    QObject::connect(&timerForGetMessage, &QTimer::timeout, this, &showTopicMessagesClass::getMessages);
    QObject::connect(&messagesBox, &QTextBrowser::anchorClicked, this, &showTopicMessagesClass::linkClicked);
    QObject::connect(&showListOfTopic, &showListOfTopicClass::openThisTopic, this, &showTopicMessagesClass::setNewTopic);
    QObject::connect(&showListOfTopic, &showListOfTopicClass::openThisTopicInNewTab, this, &showTopicMessagesClass::openThisTopicInNewTab);
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

QString showTopicMessagesClass::getPseudoUsed()
{
    return pseudoOfUser;
}

QString showTopicMessagesClass::getColorOfThisPseudo(QString pseudo)
{
    for(int i = 0; i < listOfColorPseudo->size(); ++i)
    {
        if(listOfColorPseudo->at(i).pseudo == pseudo)
        {
            return "rgb(" + QString::number(listOfColorPseudo->at(i).red) + ", " + QString::number(listOfColorPseudo->at(i).green) + ", " + QString::number(listOfColorPseudo->at(i).blue) + ")";
        }
    }

    return "";
}

const QList<QNetworkCookie>& showTopicMessagesClass::getListOfCookies()
{
    return currentCookieList;
}

void showTopicMessagesClass::setNewCookies(QList<QNetworkCookie> newCookies, QString newPseudoOfUser)
{
    networkManager.clearAccessCache();
    networkManager.setCookieJar(new QNetworkCookieJar(this));
    networkManager.cookieJar()->setCookiesFromUrl(newCookies, QUrl("http://www.jeuxvideo.com"));
    currentCookieList = newCookies;
    pseudoOfUser = newPseudoOfUser;

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
            listOfEdit.clear();
            setMessageStatus("Erreur, topic invalide.");
            setNumberOfConnected("", true);
            messageBox.warning(this, "Erreur", "Le topic n'existe pas.");
        }
        else
        {
            setMessageStatus("Erreur, impossible de récupérer les messages.");
            if(ignoreNetworkError == false)
            {
                messageBox.warning(this, "Erreur sur " + topicName, "Le programme n'a pas réussi à récupérer les messages cette fois ci, mais il continuera à essayer tant que l'onglet est ouvert.");
            }
        }
    }
    else
    {
        setMessageStatus("Erreur, impossible de récupérer les messages.");
    }
    retrievesMessage = false;
}

void showTopicMessagesClass::updateSettingInfo(bool showListOfTopicIfNeeded)
{
    showQuoteButton = settingToolClass::getThisBoolOption("showQuoteButton");
    showBlacklistButton = settingToolClass::getThisBoolOption("showBlacklistButton");
    showEditButton = settingToolClass::getThisBoolOption("showEditButton");
    loadTwoLastPage = settingToolClass::getThisBoolOption("loadTwoLastPage");
    ignoreNetworkError = settingToolClass::getThisBoolOption("ignoreNetworkError");
    timerForGetMessage.setInterval(settingToolClass::getThisIntOption("updateTopicTime"));
    numberOfMessageShowedFirstTime = settingToolClass::getThisIntOption("numberOfMessageShowedFirstTime");

    if(settingToolClass::getThisBoolOption("showListOfTopic") == true)
    {
        if(showListOfTopic.isVisible() == false)
        {
            showListOfTopic.setForumLink(parsingToolClass::getForumOfTopic(topicLink));
            if(showListOfTopicIfNeeded == true)
            {
                showListOfTopic.setVisible(true);
            }
        }
    }
    else
    {
        if(showListOfTopic.isVisible() == true)
        {
            showListOfTopic.setForumLink("");
        }
        showListOfTopic.setVisible(false);
    }
}

void showTopicMessagesClass::setNewTopic(QString newTopic)
{
    messagesBox.clear();
    topicName.clear();
    listOfEdit.clear();
    topicLink = newTopic;
    linkHasChanged = true;
    firstTimeGetMessages = true;
    errorMode = false;
    idOfLastMessage = 0;
    idOfLastMessageOfUser = 0;

    showListOfTopic.setForumLink(parsingToolClass::getForumOfTopic(topicLink));

    setMessageStatus("Nouveau topic.");
    setNumberOfConnected("", true);
    startGetMessage();
}

void showTopicMessagesClass::linkClicked(const QUrl &link)
{
    QString linkInString = link.toDisplayString();

    if(linkInString.startsWith("quote"))
    {
        lastMessageQuoted.clear();
        linkInString.remove(0, linkInString.indexOf(':') + 1);
        lastMessageQuoted = linkInString.mid(linkInString.indexOf(':') + 1);
        getQuoteInfo(linkInString.left(linkInString.indexOf(':')));
    }
    else if(linkInString.startsWith("blacklist"))
    {
        emit addToBlacklist(linkInString.remove(0, linkInString.indexOf(':') + 1));
    }
    else if(linkInString.startsWith("edit"))
    {
        emit editThisMessage(linkInString.remove(0, linkInString.indexOf(':') + 1).toInt());
    }
    else
    {
        QDesktopServices::openUrl(link);
    }
}

bool showTopicMessagesClass::getEditInfo(int idOfMessageToEdit)
{
    if(ajaxInfo.isEmpty() == false && pseudoOfUser.isEmpty() == false && idOfLastMessageOfUser != 0)
    {
        if(replyForEditInfo == 0)
        {
            QString urlToGet;
            QNetworkRequest requestForEditInfo;

            if(idOfMessageToEdit == 0)
            {
                oldIdOfLastMessageOfUser = idOfLastMessageOfUser;
            }
            else
            {
                oldIdOfLastMessageOfUser = idOfMessageToEdit;
            }

            urlToGet = "http://www.jeuxvideo.com/forums/ajax_edit_message.php?id_message=" + QString::number(oldIdOfLastMessageOfUser) + "&" + ajaxInfo + "&action=get";
            requestForEditInfo = parsingToolClass::buildRequestWithThisUrl(urlToGet);
            oldAjaxInfo = ajaxInfo;
            ajaxInfo.clear();
            replyForEditInfo = networkManager.get(requestForEditInfo);
            QObject::connect(replyForEditInfo, &QNetworkReply::finished, this, &showTopicMessagesClass::analyzeEditInfo);

            return true;
        }
    }

    return false;
}

void showTopicMessagesClass::getQuoteInfo(QString idOfMessageQuoted)
{
    if(ajaxInfo.isEmpty() == false && replyForQuoteInfo == 0)
    {
        QNetworkRequest requestForQuoteInfo = parsingToolClass::buildRequestWithThisUrl("http://www.jeuxvideo.com/forums/ajax_citation.php");
        QString dataForQuote = "id_message=" + idOfMessageQuoted + "&" + ajaxInfo;
        replyForQuoteInfo = networkManager.post(requestForQuoteInfo, dataForQuote.toLatin1());
        QObject::connect(replyForQuoteInfo, &QNetworkReply::finished, this, &showTopicMessagesClass::analyzeQuoteInfo);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.warning(this, "Erreur", "Erreur, impossible de citer ce message, réessayez.");
    }
}

void showTopicMessagesClass::getMessages()
{
    if(retrievesMessage == false)
    {
        retrievesMessage = true;

        if(replyForFirstPage == 0)
        {
            QString beforeLastPage = parsingToolClass::getBeforeLastPageOfTopic(topicLink);
            QNetworkRequest requestForFirstPage = parsingToolClass::buildRequestWithThisUrl(topicLink);
            setMessageStatus("Récupération des messages en cours...");
            secondPageLoading = false;
            linkHasChanged = false;
            replyForFirstPage = networkManager.get(requestForFirstPage);
            QObject::connect(replyForFirstPage, &QNetworkReply::finished, this, &showTopicMessagesClass::loadFirstPageFinish);

            if(loadTwoLastPage == true && beforeLastPage.isEmpty() == false)
            {
                QNetworkRequest requestForSecondPage = parsingToolClass::buildRequestWithThisUrl(beforeLastPage);
                secondPageLoading = true;
                replyForSecondPage = networkManager.get(requestForSecondPage);
                QObject::connect(replyForSecondPage, &QNetworkReply::finished, this, &showTopicMessagesClass::loadSecondPageFinish);
            }
        }
        else
        {
            retrievesMessage = false;
        }
    }
}

void showTopicMessagesClass::loadFirstPageFinish()
{
    if(loadTwoLastPage == true && secondPageLoading == true)
    {
        if(replyForSecondPage != 0)
        {
            if(replyForSecondPage->isFinished() == true)
            {
                analyzeMessages();
            }
        }
    }
    else
    {
        analyzeMessages();
    }
}

void showTopicMessagesClass::loadSecondPageFinish()
{
    if(replyForFirstPage != 0)
    {
        if(replyForFirstPage->isFinished() == true)
        {
            analyzeMessages();
        }
    }
}

void showTopicMessagesClass::analyzeEditInfo()
{
    QString message;
    QString dataToSend = oldAjaxInfo + "&action=post";
    QList<QPair<QString, QString> > listOfEditInput;
    QString source = replyForEditInfo->readAll();
    replyForEditInfo->deleteLater();

    message = parsingToolClass::getMessageEdit(source);
    parsingToolClass::getListOfHiddenInputFromThisForm(source, "form-post-topic", listOfEditInput);

    for(int i = 0; i < listOfEditInput.size(); ++i)
    {
        dataToSend += "&" + listOfEditInput.at(i).first + "=" + listOfEditInput.at(i).second;
    }

    emit setEditInfo(oldIdOfLastMessageOfUser, message, dataToSend, parsingToolClass::getCaptchaLink(source));

    replyForEditInfo = 0;
}

void showTopicMessagesClass::analyzeQuoteInfo()
{
    QString messageQuote;
    QString source = replyForQuoteInfo->readAll();
    replyForQuoteInfo->deleteLater();

    messageQuote = parsingToolClass::getMessageQuote(source);

    messageQuote = ">" + QUrl::fromPercentEncoding(lastMessageQuoted.toLatin1()) + "\n>" + messageQuote;
    replyForQuoteInfo = 0;

    emit quoteThisMessage(messageQuote);
}

void showTopicMessagesClass::analyzeMessages()
{
    QString newTopicLink;
    QString colorOfPseudo;
    QString colorOfDate;
    QString buttonString;
    QString sourceFirst;
    QString sourceSecond;

    if(replyForFirstPage == 0)
    {
        return;
    }

    sourceFirst = replyForFirstPage->readAll();
    replyForFirstPage->deleteLater();
    replyForFirstPage = 0;

    if(loadTwoLastPage == true && secondPageLoading == true)
    {
        sourceSecond = replyForSecondPage->readAll();
        replyForSecondPage->deleteLater();
        replyForSecondPage = 0;
    }

    if(linkHasChanged == true)
    {
        retrievesMessage = false;
        return;
    }

    setMessageStatus("Récupération des messages terminée !");
    setNumberOfConnected(parsingToolClass::getNumberOfConnected(sourceFirst));

    newTopicLink = parsingToolClass::getLastPageOfTopic(sourceFirst);

    if(firstTimeGetMessages == true)
    {
        topicName = parsingToolClass::getNameOfTopic(sourceFirst);

        if(topicName.isEmpty() == false)
        {
            emit newNameForTopic(topicName);
        }
    }

    if(firstTimeGetMessages == false || newTopicLink.isEmpty() == true)
    {
        QList<messageStruct> listOfEntireMessage;

        if(sourceSecond.isEmpty() == false)
        {
            listOfEntireMessage = parsingToolClass::getListOfEntireMessages(sourceSecond);
        }

        listOfEntireMessage.append(parsingToolClass::getListOfEntireMessages(sourceFirst));

        if(listOfEntireMessage.size() == 0)
        {
            setTopicToErrorMode();
            return;
        }
        else
        {
            errorMode = false;
        }

        if(messagesBox.toPlainText().isEmpty() == true)
        {
            while(listOfEntireMessage.size() > numberOfMessageShowedFirstTime)
            {
                listOfEntireMessage.pop_front();
            }
        }

        for(int i = 0; i < listOfEntireMessage.size(); ++i)
        {
            QMap<int, QString>::const_iterator listOfEditIterator = listOfEdit.find(listOfEntireMessage.at(i).idOfMessage);
            if((listOfEntireMessage.at(i).idOfMessage > idOfLastMessage || (listOfEditIterator != listOfEdit.end() && listOfEditIterator.value() != listOfEntireMessage.at(i).lastTimeEdit))
                    && listOfIgnoredPseudo->indexOf(listOfEntireMessage.at(i).pseudo.toLower()) == -1)
            {
                buttonString.clear();
                colorOfPseudo.clear();
                colorOfPseudo = getColorOfThisPseudo(listOfEntireMessage.at(i).pseudo.toLower());

                if(colorOfPseudo.isEmpty() == true)
                {
                    if(pseudoOfUser.toLower() == listOfEntireMessage.at(i).pseudo.toLower())
                    {
                        colorOfPseudo = "blue";
                    }
                    else
                    {
                        colorOfPseudo = "dimgrey";
                    }
                }

                if(listOfEditIterator != listOfEdit.end() && listOfEditIterator.value() != listOfEntireMessage.at(i).lastTimeEdit)
                {
                    colorOfDate = "green";
                }
                else
                {
                    colorOfDate = "black";
                    idOfLastMessage = listOfEntireMessage.at(i).idOfMessage;

                    if(pseudoOfUser.toLower() == listOfEntireMessage.at(i).pseudo.toLower())
                    {
                        idOfLastMessageOfUser = idOfLastMessage;
                    }
                }

                if(showQuoteButton == true)
                {
                    buttonString += "<a style=\"color: black;text-decoration: none\" href=\"quote:" + QString::number(listOfEntireMessage.at(i).idOfMessage) + ":[" +
                            listOfEntireMessage.at(i).date + "] <" + listOfEntireMessage.at(i).pseudo + ">\">[C]</a> ";
                }

                if(pseudoOfUser.toLower() == listOfEntireMessage.at(i).pseudo.toLower())
                {
                    if(showEditButton == true)
                    {
                        buttonString += "<a style=\"color: black;text-decoration: none\" href=\"edit:" + QString::number(listOfEntireMessage.at(i).idOfMessage) + "\">[E]</a> ";
                    }
                }
                else if(showBlacklistButton == true)
                {
                    buttonString += "<a style=\"color: black;text-decoration: none\" href=\"blacklist:" + listOfEntireMessage.at(i).pseudo.toLower() + "\">[B]</a> ";
                }

                messagesBox.append("<table><tr><td>" + buttonString + "[<a style=\"color: " + colorOfDate + ";text-decoration: none\" href=\"http://www.jeuxvideo.com/" +
                                   listOfEntireMessage.at(i).pseudo.toLower() +
                                   "/forums/message/" + QString::number(listOfEntireMessage.at(i).idOfMessage) + "\">" + listOfEntireMessage.at(i).date +
                                   "</a>] &lt;<a href=\"http://www.jeuxvideo.com/profil/" + listOfEntireMessage.at(i).pseudo.toLower() +
                                   "?mode=infos\"><span style=\"color: " + colorOfPseudo + ";text-decoration: none\">" +
                                   listOfEntireMessage.at(i).pseudo + "</span></a>&gt;</td><td>" + listOfEntireMessage.at(i).message + "</td></tr></table>");
                messagesBox.verticalScrollBar()->updateGeometry();
                messagesBox.verticalScrollBar()->setValue(messagesBox.verticalScrollBar()->maximum());
                listOfEdit[listOfEntireMessage.at(i).idOfMessage] = listOfEntireMessage.at(i).lastTimeEdit;
                if(pseudoOfUser.toLower() != listOfEntireMessage.at(i).pseudo.toLower())
                {
                    emit newMessagesAvailable();
                }
            }
        }

        while(listOfEdit.size() > 40)
        {
            listOfEdit.erase(listOfEdit.begin());
        }
    }

    if(pseudoOfUser.isEmpty() == false)
    {
        ajaxInfo = parsingToolClass::getAjaxInfo(sourceFirst);
        listOfInput.clear();
        parsingToolClass::getListOfHiddenInputFromThisForm(sourceFirst, "form-post-topic", listOfInput);
        captchaLink = parsingToolClass::getCaptchaLink(sourceFirst);

        if(listOfInput.isEmpty() == true && ignoreNetworkError == false)
        {
            QMessageBox messageBox;
            messageBox.warning(this, "Erreur sur " + topicName + " avec " + pseudoOfUser, "Le compte semble invalide, si tel est vraiment le cas veuillez supprimer celui-ci de la liste des comptes et vous reconnecter avec.");
            pseudoOfUser.clear();
            emit newNumberOfConnected();
        }
    }

    firstTimeGetMessages = false;
    retrievesMessage = false;

    if(newTopicLink.isEmpty() == false)
    {
        topicLink = newTopicLink;
        startGetMessage();
    }
}
