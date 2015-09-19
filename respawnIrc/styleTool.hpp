#ifndef STYLETOOL_HPP
#define STYLETOOL_HPP

#include <QtCore>

struct modelInfoStruct
{
    QString quoteModel;
    QString blacklistModel;
    QString editModel;
    QString normalDateColor;
    QString editDateColor;
    QString normalPseudoColor;
    QString userPseudoColor;
};

class styleToolClass
{
public:
    static QString getStyle(QString themeName);
    static QString getModel(QString themeName);
    static modelInfoStruct getModelInfo(QString themeName);
};

#endif // STYLETOOL_HPP
