#ifndef SHOWTOPICMESSAGES_HPP
#define SHOWTOPICMESSAGES_HPP

#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>

#include "colorPseudoListWindow.hpp"
#include "autoTimeoutReply.hpp"
#include "parsingTool.hpp"
#include "styleTool.hpp"

class showTopicMessagesClass : public QWidget
{
    Q_OBJECT
public:
    showTopicMessagesClass(QList<QString>* newListOfIgnoredPseudo, QList<pseudoWithColorStruct> *newListOfColorPseudo, QString currentThemeName, QWidget* parent = 0);
    void startGetMessage();
    const QList<QPair<QString, QString> >& getListOfInput();
    QString getTopicLink();
    QString getTopicName();
    QString getMessagesStatus();
    QString getNumberOfConnectedAndMP();
    QString getPseudoUsed();
    QString getColorOfThisPseudo(QString pseudo);
    const QList<QNetworkCookie>& getListOfCookies();
    void setNewCookies(QList<QNetworkCookie> newCookies, QString newPseudoOfUser, bool updateMessages = true);
    void setMessageStatus(QString newStatus);
    void setNumberOfConnectedAndMP(QString newNumber, bool forceSet = false);
    void setTopicToErrorMode();
    void updateSettingInfo();
public slots:
    void setNewTheme(QString newThemeName);
    void setNewTopic(QString newTopic);
    void linkClicked(const QUrl& link);
    bool getEditInfo(int idOfMessageToEdit = 0, bool useMessageEdit = true);
    void getQuoteInfo(QString idOfMessageQuoted);
    void getMessages();
    void loadFirstPageFinish();
    void loadSecondPageFinish();
    void analyzeEditInfo();
    void analyzeQuoteInfo();
    void analyzeMessages();
signals:
    void quoteThisMessage(QString messageToQuote);
    void addToBlacklist(QString pseudoToBlacklist);
    void editThisMessage(int idOfMessageEdit, bool useMessageEdit);
    void newMessageStatus();
    void newNumberOfConnectedAndMP();
    void setEditInfo(int idOfMessageEdit, QString messageEdit, QString infoToSend, bool useMessageEdit);
    void newMessagesAvailable();
    void newNameForTopic(QString newName);
    void newCookiesHaveToBeSet();
private:
    QTextBrowser messagesBox;
    QString baseModel;
    modelInfoStruct baseModelInfo;
    QList<QNetworkCookie> currentCookieList;
    autoTimeoutReplyClass timeoutForFirstPage;
    autoTimeoutReplyClass timeoutForSecondPage;
    autoTimeoutReplyClass timeoutForEditInfo;
    autoTimeoutReplyClass timeoutForQuoteInfo;
    QNetworkReply* replyForFirstPage;
    QNetworkReply* replyForSecondPage;
    QNetworkReply* replyForEditInfo;
    QNetworkReply* replyForQuoteInfo;
    QNetworkAccessManager* networkManager;
    QTimer timerForGetMessage;
    QList<QPair<QString, QString> > listOfInput;
    QList<QString>* listOfIgnoredPseudo;
    QList<pseudoWithColorStruct> *listOfColorPseudo;
    QMap<int, QString> listOfEdit;
    QString messagesStatus;
    QString numberOfConnectedAndMP;
    QString topicLink;
    QString topicName;
    QString pseudoOfUser;
    QString ajaxInfo;
    QString oldAjaxInfo;
    QString lastMessageQuoted;
    QString lastDate;
    bool showQuoteButton;
    bool showBlacklistButton;
    bool showEditButton;
    bool showStickers;
    bool loadTwoLastPage;
    bool ignoreNetworkError;
    bool secondPageLoading;
    bool firstTimeGetMessages;
    bool retrievesMessage;
    bool linkHasChanged;
    bool errorMode;
    bool oldUseMessageEdit;
    bool needToGetMessages;
    bool errorLastTime;
    bool needToSetCookies;
    bool colorModoAndAdminPseudo;
    bool colorPEMT;
    bool getFirstMessageOfTopic;
    bool warnWhenEdit;
    messageStruct firstMessageOfTopic;
    int idOfLastMessage;
    int idOfLastMessageOfUser;
    int oldIdOfLastMessageOfUser;
    int numberOfMessageShowedFirstTime;
    int stickersSize;
};

#endif
