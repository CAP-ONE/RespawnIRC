#include <QApplication>

#include "mainWindow.hpp"
#include "settingTool.hpp"
#include "parsingTool.hpp"
#include "shortcutTool.hpp"
#include "styleTool.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");

    QApplication app(argc, argv);
    QSettings setting(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);

    settingToolClass::setSettings(&setting);
    settingToolClass::initializeDefaultListsOption();
    shortcutToolClass::loadShortcutRule("shortcut");
    shortcutToolClass::loadShortcutRule("stickerToSmiley", "<img class=\"img-stickers\" src=\"http://jv.stkr.fr/p/", "\"/>", "<img src=\"resources/smileys/", "\"/>");
    styleToolClass::getModelInfo("");

    qRegisterMetaType<ajaxInfoStruct>("ajaxInfoStruct");
    qRegisterMetaType<messageStruct>("messageStruct");
    qRegisterMetaType<QList<messageStruct> >("QList<messageStruct>");
    qRegisterMetaType<QPair<QString,QString> > ("QPair<QString,QString>");
    qRegisterMetaType<QList<QPair<QString,QString> > >("QList<QPair<QString,QString> >");

    mainWindowClass mainWindow;
    mainWindow.show();

    return app.exec();
}
