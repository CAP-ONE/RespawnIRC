#include "parsingTool.hpp"

void parsingToolClass::getListOfHiddenInputFromThisForm(QString& source, QString formName, QList<QPair<QString, QString> >& listOfInput)
{
    QRegExp expForForm("(<form [^>]*" + formName + ".*</form>)");
    expForForm.setMinimal(true);
    source.contains(expForForm);
    source = expForForm.cap(1);

    QRegExp expForInput("<input ([^=]*)=\"([^\"]*)\" ([^=]*)=\"([^\"]*)\" ([^=]*)=\"([^\"]*)\"/>");
    int posForExpForInput = 0;
    while((posForExpForInput = expForInput.indexIn(source, posForExpForInput)) != -1)
    {
        if(expForInput.cap(1) == "type")
        {
            if(expForInput.cap(3) == "name")
            {
                listOfInput.push_back(QPair<QString, QString>(expForInput.cap(4), expForInput.cap(6)));
            }
            else
            {
                listOfInput.push_back(QPair<QString, QString>(expForInput.cap(6), expForInput.cap(4)));
            }
        }
        else if(expForInput.cap(3) == "type")
        {
            if(expForInput.cap(1) == "name")
            {
                listOfInput.push_back(QPair<QString, QString>(expForInput.cap(2), expForInput.cap(6)));
            }
            else
            {
                listOfInput.push_back(QPair<QString, QString>(expForInput.cap(6), expForInput.cap(2)));
            }
        }
        else
        {
            if(expForInput.cap(1) == "name")
            {
                listOfInput.push_back(QPair<QString, QString>(expForInput.cap(2), expForInput.cap(4)));
            }
            else
            {
                listOfInput.push_back(QPair<QString, QString>(expForInput.cap(4), expForInput.cap(2)));
            }
        }
        posForExpForInput += expForInput.matchedLength();
    }
}

QString parsingToolClass::getLastPageOfTopic(QString source)
{
    int currentPage = 0;
    QString lastPage;
    QRegExp expForCurrentPage("<span class=\"page-active\">([^<]*)</span>");
    expForCurrentPage.setMinimal(true);
    source.contains(expForCurrentPage);
    currentPage = expForCurrentPage.cap(1).toInt();

    QRegExp expForPageLink("<span><a href=\"([^\"]*)\" class=\"lien-jv\">([^<]*)</a></span>");
    int posForExpForPageLink = 0;
    while((posForExpForPageLink = expForPageLink.indexIn(source, posForExpForPageLink)) != -1)
    {
        if(expForPageLink.cap(2).toInt() > currentPage)
        {
            currentPage = expForPageLink.cap(2).toInt();
            lastPage = "http://www.jeuxvideo.com" + expForPageLink.cap(1);
        }

        posForExpForPageLink += expForPageLink.matchedLength();
    }

    return lastPage;
}

QList<int> parsingToolClass::getListOfMessageID(QString source)
{
    QList<int> listOfMessageIDInNumber;
    QList<QString> listOfMessageIDInString;
    QRegExp expForMessageID("<div class=\"bloc-message-forum \" id=\"post_[^\"]*\" data-id=\"([^\"]*)\">");

    listOfMessageIDInString = getListOfThisCapNumber(source, expForMessageID, 1);

    for(int i = 0; i < listOfMessageIDInString.size(); ++i)
    {
        listOfMessageIDInNumber.push_back(listOfMessageIDInString.at(i).toInt());
    }

    return listOfMessageIDInNumber;
}

QList<QString> parsingToolClass::getListOfPseudo(QString source)
{
    QRegExp expForPseudo("<span class=\"JvCare [^ ]* bloc-pseudo-msg text-[^\"]*\" target=\"_blank\">[^a-zA-Z0-9_\\[\\]-]*([a-zA-Z0-9_\\[\\]-]*)[^<]*</span>");

    return getListOfThisCapNumber(source, expForPseudo, 1);
}

QList<QString> parsingToolClass::getListOfDate(QString source)
{
    QRegExp expForDate("<div class=\"bloc-date-msg\">[^<]*<span class=\"JvCare [^ ]* lien-jv\" target=\"_blank\">[^ ]* [^ ]* [^ ]* [^ ]* ([0-9:]*)[^<]*</span>");

    return getListOfThisCapNumber(source, expForDate, 1);
}

QList<QString> parsingToolClass::getListOfMessage(QString source)
{
    QList<QString> listOfMessage;
    QRegExp expForMessage("<div class=\"bloc-contenu\"><div class=\"txt-msg  text-enrichi-forum \">(.*)</div>");
    expForMessage.setMinimal(true);

    listOfMessage = getListOfThisCapNumber(source, expForMessage, 1);

    for(int i = 0; i < listOfMessage.size(); ++i)
    {
        listOfMessage[i] = parsingMessages(listOfMessage.at(i));
    }

    return listOfMessage;
}

QString parsingToolClass::parsingMessages(QString thisMessage)
{
    QRegExp expForSmiley("<img src=\"[^\"]*\" alt=\"[^\"]*\" data-def=\"SMILEYS\" data-code=\"([^\"]*)\" title=\"[^\"]*\" />");
    QRegExp expForStickers("<img class=\"img-stickers\" src=\"([^\"]*)\"/>");
    QRegExp expForLongLink("<span class=\"JvCare [^\"]*\" rel=\"nofollow\" target=\"_blank\" title=\"([^\"]*)\">[^<]*<i></i><span>[^<]*</span>[^<]*</span>");
    QRegExp expForShortLink("<span class=\"JvCare [^\"]*\" rel=\"nofollow\" target=\"_blank\">([^<]*)</span>");
    QRegExp expForNoelshack("<a href=\"([^\"]*)\" data-def=\"NOELSHACK\" target=\"_blank\"><img class=\"img-shack\" [^>]*></a>");
    QRegExp expForSpoilLine("<span class=\"bloc-spoil-jv en-ligne\"><span class=\"contenu-spoil\">([^<]*)</span></span>");
    QRegExp expForSpoilBlock("<span class=\"bloc-spoil-jv\"><span class=\"contenu-spoil\">([^<]*)</span></span>");
    QRegExp expForAllJVCare("<span class=\"JvCare [^\"]*\">([^<]*)</span>");

    thisMessage.replace("\n", "");

    replaceWithCapNumber(thisMessage, expForSmiley, 1);
    replaceWithCapNumber(thisMessage, expForStickers, 1, true);
    replaceWithCapNumber(thisMessage, expForLongLink, 1, true);
    replaceWithCapNumber(thisMessage, expForShortLink, 1, true);
    replaceWithCapNumber(thisMessage, expForNoelshack, 1, true);
    replaceWithCapNumber(thisMessage, expForSpoilLine, 1, false, "<strong> !!! SPOIL !!! </strong>", "<strong> !!! SPOIL !!! </strong>");
    replaceWithCapNumber(thisMessage, expForSpoilBlock, 1, false, "<br /><br /><strong>!!! SPOIL !!! </strong>", "<strong> !!! SPOIL !!!</strong>");
    replaceWithCapNumber(thisMessage, expForAllJVCare, 1);

    thisMessage.replace(QRegExp("</p> *<p>"), "<br /><br />");
    thisMessage.replace("<p>", "");
    thisMessage.replace("</p>", "");

    return thisMessage;
}

QNetworkRequest parsingToolClass::buildRequestWithThisUrl(QString url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", "RespawnIRC");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Cookie", "");
    request.setRawHeader("Connection", "Keep-Alive");

    return request;
}

QList<QString> parsingToolClass::getListOfThisCapNumber(QString& source, QRegExp exp, int capNumber)
{
    QList<QString> listOfString;
    int posForExp = 0;
    while((posForExp = exp.indexIn(source, posForExp)) != -1)
    {
        listOfString.push_back(exp.cap(capNumber));
        posForExp += exp.matchedLength();
    }

    return listOfString;
}

void parsingToolClass::replaceWithCapNumber(QString& source, QRegExp exp, int capNumber, bool createLink, QString stringBefore, QString stringAfter)
{
    int posForExp = 0;
    QString newString;

    while((posForExp = exp.indexIn(source, posForExp)) != -1)
    {
        newString = stringBefore;

        if(createLink == false)
        {
            newString += exp.cap(capNumber);
        }
        else
        {
            newString += "<a href=\"" + exp.cap(capNumber) +"\">" + exp.cap(capNumber) + "</a>";
        }

        newString += stringAfter;

        source.replace(posForExp, exp.cap(0).length(), newString);
        posForExp += newString.length();
    }
}