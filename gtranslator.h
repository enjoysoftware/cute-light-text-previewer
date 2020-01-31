#ifndef GTRANSLATOR_H
#define GTRANSLATOR_H
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
class GTranslator
{
public:
    explicit GTranslator(QString targetLang_, QString sourceLang_, QString text_, QWidget *parentDialog);
    ~GTranslator();
    QString translate();
private:
    QString targetLang,sourceLang,text;
    QWidget *parentDialog;
    QString getData();
signals:

};

#endif // GTRANSLATOR_H
