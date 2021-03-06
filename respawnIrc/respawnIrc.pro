SOURCES += \
    main.cpp \
    mainWindow.cpp \
    respawnIrc.cpp \
    connectWindow.cpp \
    parsingTool.cpp \
    selectTopicWindow.cpp \
    showTopicMessages.cpp \
    ignoreListWindow.cpp \
    addPseudoWindow.cpp \
    settingTool.cpp \
    multiTypeTextBox.cpp \
    checkUpdate.cpp \
    accountListWindow.cpp \
    colorPseudoListWindow.cpp \
    showListOfTopic.cpp \
    styleTool.cpp \
    selectThemeWindow.cpp \
    spellTextEdit.cpp \
    highlighter.cpp \
    autoTimeoutReply.cpp \
    containerForTopicsInfos.cpp \
    sendMessages.cpp \
    selectStickerWindow.cpp \
    getTopicMessages.cpp \
    preferencesWindow.cpp \
    shortcutTool.cpp \
    addCookiesWindow.cpp \
    imageDownloadTool.cpp \
    webNavigator.cpp \
    viewThemeInfos.cpp

QT += \
    network \
    widgets \
    multimedia \
    webenginewidgets

HEADERS += \
    mainWindow.hpp \
    respawnIrc.hpp \
    connectWindow.hpp \
    parsingTool.hpp \
    selectTopicWindow.hpp \
    showTopicMessages.hpp \
    ignoreListWindow.hpp \
    addPseudoWindow.hpp \
    settingTool.hpp \
    multiTypeTextBox.hpp \
    checkUpdate.hpp \
    colorPseudoListWindow.hpp \
    accountListWindow.hpp \
    showListOfTopic.hpp \
    styleTool.hpp \
    selectThemeWindow.hpp \
    spellTextEdit.hpp \
    highlighter.hpp \
    autoTimeoutReply.hpp \
    containerForTopicsInfos.hpp \
    sendMessages.hpp \
    selectStickerWindow.hpp \
    getTopicMessages.hpp \
    preferencesWindow.hpp \
    shortcutTool.hpp \
    addCookiesWindow.hpp \
    imageDownloadTool.hpp \
    webNavigator.hpp \
    viewThemeInfos.hpp

RC_FILE = respawnIrc.rc

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT.lib

CONFIG += c++11

unix|win32: LIBS += -L$$PWD/../hunspell/lib/ -llibhunspell

INCLUDEPATH += $$PWD/../hunspell/include
DEPENDPATH += $$PWD/../hunspell/include
