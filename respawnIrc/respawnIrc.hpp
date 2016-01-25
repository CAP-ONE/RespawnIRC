#ifndef RESPAWNIRC_HPP
#define RESPAWNIRC_HPP

#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>

#include "containerForTopicsInfos.hpp"
#include "sendMessages.hpp"
#include "colorPseudoListWindow.hpp"
#include "accountListWindow.hpp"
#include "multiTypeTextBox.hpp"
#include "checkUpdate.hpp"

class respawnIrcClass : public QWidget
{
    Q_OBJECT
public:
    respawnIrcClass(QWidget* parent = 0);
    void loadSettings();
    containerForTopicsInfosClass* getCurrentWidget();
    multiTypeTextBoxClass* getMessageLine();
    void addButtonToButtonLayout();
    void selectThisTab(int number);
    void setButtonInButtonLayoutVisible(bool visible);
    void useThisFavorite(int index);
    QString addThisFavorite(int index);
    void delThisFavorite(int index);
    void updateSettingInfoForList();
    static const QString currentVersionName;
public slots:
    void showConnect();
    void showAccountListWindow();
    void showSelectSticker();
    void showSelectTopic();
    void showSelectTheme();
    void showIgnoreListWindow();
    void showColorPseudoListWindow();
    void showUpdateTopicTimeWindow();
    void showNumberOfMessageShowedFirstTimeWindow();
    void showStickersSizeWindow();
    void showAbout();
    void addNewTab();
    void addNewTabWithTopic(QString newTopicLink);
    void removeTab(int index);
    void checkForUpdate();
    void updateTopic();
    void reloadTopic();
    void reloadAllTopic();
    void goToCurrentTopic();
    void goToCurrentForum();
    void disconnectFromAllTabs();
    void disconnectFromCurrentTab();
    void disconnectFromThisPseudo(QString thisPseudo);
    void addThisPeudoToBlacklist(QString pseudoToAdd);
    void setUpdateTopicTime(int newTime);
    void setNumberOfMessageShowedFirstTime(int newNumber);
    void setStickersSize(int newSize);
    void setThisBoolOption(bool newVal);
    void setShowTextDecorationButton(bool newVal);
    void setNewCookies(QList<QNetworkCookie> newCookies, QString newPseudoOfUser, bool saveAccountList, bool savePseudo);
    void setNewCookiesForCurrentTopic(QList<QNetworkCookie> newCookies, QString newPseudoOfUser, bool savePseudo);
    void setNewCookiesForPseudo();
    void setNewTopic(QString newTopic);
    void setNewTheme(QString newThemeName);
    void reloadTheme();
    void setNewMessageStatus();
    void setNewNumberOfConnectedAndPseudoUsed();
    void setNewTopicName(QString topicName);
    void saveListOfAccount();
    void saveListOfIgnoredPseudo();
    void saveListOfColorPseudo();
    void warnUserForNewMessages();
    void currentTabChanged(int newIndex);
    void messageHaveToBePosted();
    void editLastMessage();
    void setEditMessage(int idOfMessageToEdit = 0, bool useMessageEdit = true);
    void clipboardChanged();
signals:
    void themeChanged(QString newThemeName);
protected:
    void focusInEvent(QFocusEvent * event);
private:
    static QRegularExpression expForSmileyToCode;
    QHBoxLayout* buttonLayout;
    sendMessagesClass sendMessages;
    QTabWidget tabList;
    QVector<QString> vectorOfFavoriteLink;
    QList<QNetworkCookie> currentCookieList; //?
    QList<containerForTopicsInfosClass*> listOfContainerForTopicsInfos;
    QList<QString> listOfTopicLink;
    QList<QString> listOfIgnoredPseudo;
    QList<pseudoWithColorStruct> listOfColorPseudo;
    QList<accountStruct> listOfAccount;
    QList<QString> listOfPseudoForTopic;
    QLabel messagesStatus;
    QLabel numberOfConnectedAndPseudoUsed;
    QString pseudoOfUser;
    QPixmap alertImage;
    checkUpdateClass checkUpdate;
    QString currentThemeName;
    bool beepWhenWarn;
    bool warnUser;
};

#endif
