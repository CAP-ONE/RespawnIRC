#include "selectStickerWindow.hpp"

selectStickerWindowClass::selectStickerWindowClass(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    setAttribute(Qt::WA_DeleteOnClose);

    stickerBrowser.setContextMenuPolicy(Qt::CustomContextMenu);
    stickerBrowser.setReadOnly(true);
    stickerBrowser.setOpenExternalLinks(false);
    stickerBrowser.setOpenLinks(false);
    stickerBrowser.setSearchPaths(QStringList(QCoreApplication::applicationDirPath()));
    stickerBrowser.setMinimumWidth(380);
    stickerBrowser.setMinimumHeight(380);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(&stickerBrowser);
    mainLayout->setMargin(0);

    setLayout(mainLayout);
    setWindowTitle("Choisir un sticker");

    loadListOfStickers();

    QObject::connect(&stickerBrowser, &QListView::customContextMenuRequested, this, &selectStickerWindowClass::createContextMenu);
    QObject::connect(&stickerBrowser, &QTextBrowser::anchorClicked, this, &selectStickerWindowClass::linkClicked);
}

void selectStickerWindowClass::loadListOfStickers()
{
    QDir themeDir(QCoreApplication::applicationDirPath() + "/ressources/stickers/");
    QStringList listOfStickers;

    if(themeDir.exists() == true)
    {
        listOfStickers = themeDir.entryList(QDir::Files);
    }

    for(int i = 0; i < listOfStickers.size(); ++i)
    {
        stickerBrowser.insertHtml("<a href=\"sticker:" + listOfStickers.at(i).left(listOfStickers.at(i).size() - 4) +
                                  "\"><img src=\"ressources/stickers/" + listOfStickers.at(i) + "\" /></a>");
    }
}

void selectStickerWindowClass::linkClicked(const QUrl &link)
{
    QString linkInString = link.toDisplayString();

    emit addThisSticker("[[sticker:p/" + linkInString.remove(0, linkInString.indexOf(':') + 1) + "]]");
}

void selectStickerWindowClass::createContextMenu(const QPoint &thisPoint)
{
    (void)thisPoint;
    close();
}
