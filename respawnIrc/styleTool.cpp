#include <QFile>
#include <QStringList>
#include <QCoreApplication>
#include <QTextStream>
#include <QVector>
#include <QDir>
#include <QList>
#include <QFontDatabase>

#include "styleTool.hpp"

namespace
{
    colorInfoForMessageAndOtherStruct colorInfoForMessageAndOther;
    QList<QString> listOfFontsAlreadyLoaded;
}

QString styleToolClass::getStyle(QString themeName)
{
    QFile thisFile(QCoreApplication::applicationDirPath() + "/themes/" + themeName + "/style.css");
    if(themeName.isEmpty() == false && thisFile.open(QFile::ReadOnly | QFile::Text) == true)
    {
        QTextStream textStream(&thisFile);
        return textStream.readAll();
    }
    else
    {
        return "";
    }
}

QString styleToolClass::getModel(QString themeName)
{
    QFile thisFile(QCoreApplication::applicationDirPath() + "/themes/" + themeName + "/model.txt");
    if(themeName.isEmpty() == false && thisFile.open(QFile::ReadOnly | QFile::Text) == true)
    {
        QTextStream textStream(&thisFile);
        return textStream.readAll();
    }
    else
    {
        return "<table><tr><td><%BUTTON_QUOTE%><%BUTTON_BLACKLIST%><%BUTTON_EDIT%><%BUTTON_DELETE%>[<a style=\"color: <%DATE_COLOR%>;text-decoration: none\" href=\"http://www.jeuxvideo.com/"
                "<%PSEUDO_LOWER%>/forums/message/<%ID_MESSAGE%>\"><%DATE_MESSAGE%></a>] &lt;<a href=\"http://www.jeuxvideo.com/profil/"
                "<%PSEUDO_LOWER%>?mode=infos\"><span style=\"color: <%PSEUDO_COLOR%>;text-decoration: none\"><%PSEUDO_PSEUDO%>"
                "</span></a>&gt;</td><td><%MESSAGE_MESSAGE%><%SIGNATURE_MODEL%></td></tr></table>";
    }
}

modelInfoStruct styleToolClass::getModelInfo(QString themeName)
{
    QStringList listOfInfos;
    QVector<QString> listOfLine;
    modelInfoStruct modelInfo;
    QFile thisFile(QCoreApplication::applicationDirPath() + "/themes/" + themeName + "/modelInfo.cfg");

    listOfInfos.push_back("<a style=\"color: black;text-decoration: none\" href=\"quote:<%ID_MESSAGE%>:[<%DATE_MESSAGE%>] <<%PSEUDO_PSEUDO%>>\">[C]</a> ");
    listOfInfos.push_back("<a style=\"color: black;text-decoration: none\" href=\"blacklist:<%PSEUDO_LOWER%>\">[B]</a> ");
    listOfInfos.push_back("<a style=\"color: black;text-decoration: none\" href=\"edit:<%ID_MESSAGE%>\">[E]</a> ");
    listOfInfos.push_back("black"); //normal date color
    listOfInfos.push_back("green"); //edited date color
    listOfInfos.push_back("dimgrey"); //normal pseudo color
    listOfInfos.push_back("blue");  //user pseudo color

    listOfInfos.push_back("blue"); //link color
    listOfInfos.push_back("black"); //spoil color
    listOfInfos.push_back("grey"); //quote color
    listOfInfos.push_back("red"); //underline color

    listOfInfos.push_back("#3a9d23"); //modo pseudo color
    listOfInfos.push_back("#db0f0f"); //admin pseudo color
    listOfInfos.push_back("darkorange"); //pemt date color

    listOfInfos.push_back("rgba(100, 100, 100, 0.25)"); //quote background color
    listOfInfos.push_back("black"); //quote text color

    listOfInfos.push_back("<a style=\"color: black;text-decoration: none\" href=\"delete:<%ID_MESSAGE%>\">[S]</a> ");

    listOfInfos.push_back("green"); //edit message color

    listOfInfos.push_back("<hr><span style=\"font-size: 1px;\"><br></span><i><%SIGNATURE_SIGNATURE%></i>");
    listOfInfos.push_back("<i><%MESSAGE_TO_UPDATE%></i>");
    listOfInfos.push_back("<img width=60 height=60 src=\"<%AVATAR_LINK%>\">");

    if(themeName.isEmpty() == false && thisFile.open(QFile::ReadOnly | QFile::Text) == true)
    {
        QTextStream textStream(&thisFile);
        while(textStream.atEnd() == false)
        {
            listOfLine.push_back(textStream.readLine());
        }
    }

    while(listOfLine.size() < listOfInfos.size())
    {
        listOfLine.push_back(listOfInfos.at(listOfLine.size()));
    }

    modelInfo.quoteModel = listOfLine.at(0);
    modelInfo.blacklistModel = listOfLine.at(1);
    modelInfo.editModel = listOfLine.at(2);
    modelInfo.normalDateColor = listOfLine.at(3);
    modelInfo.editDateColor = listOfLine.at(4);
    modelInfo.normalPseudoColor = listOfLine.at(5);
    modelInfo.userPseudoColor = listOfLine.at(6);

    colorInfoForMessageAndOther.linkColor = listOfLine.at(7);
    colorInfoForMessageAndOther.spoilColor = listOfLine.at(8);
    colorInfoForMessageAndOther.tableBorderColor = listOfLine.at(9);
    colorInfoForMessageAndOther.underlineColor = listOfLine.at(10);

    modelInfo.modoPseudoColor = listOfLine.at(11);
    modelInfo.adminPseudoColor = listOfLine.at(12);
    modelInfo.pemtDateColor = listOfLine.at(13);

    colorInfoForMessageAndOther.tableBackgroundColor = listOfLine.at(14);
    colorInfoForMessageAndOther.tableTextColor = listOfLine.at(15);

    modelInfo.deleteModel = listOfLine.at(16);

    colorInfoForMessageAndOther.editMessageColor = listOfLine.at(17);

    modelInfo.signatureModel = listOfLine.at(18);
    modelInfo.updateMessageForEditModel = listOfLine.at(19);
    modelInfo.avatarModel = listOfLine.at(20);

    return modelInfo;
}

const colorInfoForMessageAndOtherStruct& styleToolClass::getColorInfo()
{
    return colorInfoForMessageAndOther;
}

QString styleToolClass::getImagePathOfThemeIfExist(QString themeName)
{
    QDir imgDir(QCoreApplication::applicationDirPath() + "/themes/" + themeName + "/img/");

    if(themeName.isEmpty() == false && imgDir.exists() == true)
    {
        return imgDir.path();
    }

    return "";
}

void styleToolClass::loadThemeFont(QString themeName)
{
    QDir fontDir(QCoreApplication::applicationDirPath() + "/themes/" + themeName + "/fonts/");
    QStringList listOfFontsInDir;

    if(themeName.isEmpty() == false && fontDir.exists() == true)
    {
        listOfFontsInDir = fontDir.entryList(QDir::Files);
    }

    for(QString& thisFont : listOfFontsInDir)
    {
        if(listOfFontsAlreadyLoaded.indexOf(thisFont.toLower()) == -1)
        {
            QFontDatabase::addApplicationFont(fontDir.path() + "/" + thisFont);
            listOfFontsAlreadyLoaded.append(thisFont.toLower());
        }
    }
}
