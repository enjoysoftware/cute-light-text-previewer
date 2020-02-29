#include "gtranslator.h"
#include <gtranslatedialog.h>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#define REQUEST_URL "https://script.google.com/macros/s/AKfycbzjy4EguclwvcRAhCACuTcyPzEK5BFIQUR7UeoX31TOE7DRYZs/exec?target=%1&source=%2&text=%3"
GTranslator::GTranslator(QString targetLang_, QString sourceLang_, QString text_,QWidget *parent) :  targetLang(targetLang_),
    sourceLang(sourceLang_),text(text_),parentDialog(parent)
{
    qDebug() << "targetLang -> " << targetLang << endl <<
                "sourceLang -> " << sourceLang <<endl <<
                "text -> " << text ;

}
GTranslator::~GTranslator(){

}
QString GTranslator::translate(){
    qDebug() << "Translating from" << sourceLang << "to" << targetLang;
    QString data = getData();
    qDebug() << "Receved data:" << data;
    QJsonObject jsonObj= QJsonDocument::fromJson(data.toUtf8()).object();
    int code = jsonObj["code"].toInt();
    QString text= jsonObj["text"].toString();
    qDebug() << "Code:" << code << "Text:" << text;
    if(code !=200 && code != 1000){
        QMessageBox::warning(parentDialog,QObject::tr("Error"),QObject::tr("Error: Detail:%2").arg(text));
        return QObject::tr("Error: %1").arg(text);
    }else if(code == 1000){
        return QObject::tr("Error: %1").arg(text);
    }
    return text;
}
QString GTranslator::getData(){
        QNetworkRequest request;
        QUrl httpurl=QUrl(QString(REQUEST_URL).arg(targetLang,sourceLang,text));
        request.setUrl(httpurl);
        qDebug() << httpurl;
        QNetworkAccessManager accsMgr;
        accsMgr.setNetworkAccessible( QNetworkAccessManager::Accessible );
        QNetworkReply *reply = accsMgr.get(request);
        QEventLoop waitLoop;
        QObject::connect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
        waitLoop.exec();
        QObject::disconnect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
//        今後ここはwhileループにする予定
//        getStatusCode(reply,&waitLoop);
        if( reply->error() != QNetworkReply::NoError ){
            qCritical() << "Error: " << reply->errorString();
            QMessageBox::warning(parentDialog,QObject::tr("Error"),reply->errorString());
            return QObject::tr("{\"code\": 1000 ,\"text\": \"%1\"}").arg(reply->errorString());
        }else {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            switch (statusCode) {
                case 301:
                case 302:
                case 307:
                //Redirect
//                    qDebug() << "Redirected: " << reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
                    request.setUrl(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl());
                    reply = accsMgr.get(request);
                    QObject::connect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()) );
                    waitLoop.exec();
                    QObject::disconnect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));

                    break;

                case 200:
                default:
                qDebug() << "Error: language may be incorrect";
                return QObject::tr("{\"code\": 900 ,\"text\": \"What should have been redirected is not redirected. Check that the language specification is correct.\"}");
                break;
            }
}
        QByteArray return_value=reply->readAll();
        qDebug() << "Translator:" << QString::fromUtf8(return_value);
        return QString::fromUtf8(return_value);
}
