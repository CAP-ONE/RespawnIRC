SOURCES += \
    main.cpp \
    mainWindow.cpp \
    respawnIrc.cpp \
    connectWindow.cpp \
    parsingTool.cpp \
    selectTopicWindow.cpp \
    captchaWindow.cpp \
    showTopicMessages.cpp

QT += \
    network

HEADERS += \
    mainWindow.hpp \
    respawnIrc.hpp \
    connectWindow.hpp \
    parsingTool.hpp \
    selectTopicWindow.hpp \
    captchaWindow.hpp \
    showTopicMessages.hpp

RC_FILE = respawnIrc.rc
