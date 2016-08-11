#ifndef HIGHLIGHTER_HPP
#define HIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QString>
#include <QTextCharFormat>
#include "hunspell/hunspell.hxx"

class QTextDocument;
class QTextCodec;

class highlighterClass : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    highlighterClass(QTextDocument* parent = 0);
    ~highlighterClass();
    void enableSpellChecking(const bool state);
    bool setDic(const QString newSpellDic);
    void styleChanged();
public slots:
    void addWordToDic(QString word);
protected:
    void highlightBlock(const QString& text);
    void spellCheck(const QString& text);
    bool checkWord(QString word);
private:
    QString spellDic;
    QString spellEncoding;
    Hunspell* spellChecker = nullptr;
    bool spellCheckActive = false;
    bool spellerError = true;
    QTextCharFormat spellCheckFormat;
    QTextCodec* codec = nullptr;
};

#endif
