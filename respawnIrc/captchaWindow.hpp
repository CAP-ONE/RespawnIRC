#ifndef CAPTCHAWINDOW_HPP
#define CAPTCHAWINDOW_HPP

#include <QtGui>
#include <QtCore>
#include <QtNetwork>

class captchaWindowClass : public QDialog
{
    Q_OBJECT
public:
    captchaWindowClass(QString captchaLink, QWidget* parent);
    ~captchaWindowClass();
public slots:
    void showCaptcha();
    void sendCaptchaCode();
signals:
    void codeForCaptcha(QString captchaCode);
private:
    QLabel labPixCaptcha;
    QLineEdit captchaCodeLine;
    QNetworkAccessManager networkManager;
    QNetworkReply* reply;
};

#endif
