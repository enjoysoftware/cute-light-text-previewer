#include "gtranslator.h"
#include <gtranslatedialog.h>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QProgressDialog>
//↓リリースする際は、ブランチ名を合わせる。例：hotfix→develop→master
#define FETCH_URL "https://raw.githubusercontent.com/enjoysoftware/cute-light-text-previewer/master/Api_fetch_url_new.txt"
//Emergency緊急↓
#define REQUEST_URL_TMP "https://script.google.com/macros/s/AKfycbwq9ro5yWQdKXW4_QD0MCiw7WLuXiovK3V9aRmW/exec"
GTranslator::GTranslator(const QString& targetLang_, const QString& sourceLang_, const QString& text_,QWidget *parent) :  targetLang(targetLang_),
    sourceLang(sourceLang_),text(text_),parentDialog(parent)
{
    qDebug() << "targetLang -> " << targetLang << "\n" <<
                "sourceLang -> " << sourceLang << "\n" <<
                "text -> " << text;
    url = getUrl();
}
GTranslator::~GTranslator(){

}
QString GTranslator::translate(){
    qDebug() << "Translating from" << sourceLang << "to" << targetLang;
    QString data = getData();
//    qDebug() << "Received data:" << data;
    QJsonObject jsonObj= QJsonDocument::fromJson(data.toUtf8()).object();
    QString stat = jsonObj["stat"].toString();
    QString text= jsonObj["text"].toString();
    qDebug() << "Status:" << stat << "Text:" << text.mid(0,4) + "...";
    if(stat == "local-error" || stat == "error"){
        QMessageBox::critical(parentDialog,QObject::tr("Error"),QObject::tr("Error: %1").arg(text));
        return QObject::tr("Error: %1").arg(text);
    }else if(stat == "service-closed"){
        QMessageBox::information(parentDialog,QObject::tr("Sorry,This service has ended"),QObject::tr("Sorry, translation functionality is no longer provided. "
                                                                            "Functions other than the translation function can still be used."
                                                                            "Message from server:%1").arg(text));
        return QObject::tr("Translation service has ended");
    }else if(stat == "ok"){
            return text;
    }else if(stat == "warning"){
        QMessageBox::warning(parentDialog,QObject::tr("Warning"),QObject::tr("Warning: %1").arg(text));
        return QObject::tr("Warning: %1").arg(text);
    }else{

        QMessageBox::critical(parentDialog,QObject::tr("Invalid status: %1").arg(stat),QObject::tr("An error has occurred that should not normally occur.\n"
                                                                                     "-Try rebuilding or reinstalling this application.\n"
                                                                                     "-There may be a problem with the API on the Web. Please wait a while and try again. \n"
                                                                                     "- Please retry after updating version of this software."));
        return QObject::tr("Invalid status: %1").arg(stat);
    }
}
QString GTranslator::getData(){
        QNetworkRequest request;
        QUrl httpurl=QUrl(url);
        request.setUrl(httpurl);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        qDebug() << "URL:" << httpurl;
        QUrlQuery postData;
        postData.addQueryItem("text", text);
        postData.addQueryItem("source", sourceLang);
        postData.addQueryItem("target", targetLang);
        QNetworkAccessManager accsMgr;
//        accsMgr.setNetworkAccessible( QNetworkAccessManager::Accessible );
        QNetworkReply *reply = accsMgr.post(request,postData.toString(QUrl::FullyEncoded).toUtf8());
        QEventLoop waitLoop;
        QObject::connect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
        waitLoop.exec();
        QObject::disconnect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
        if( reply->error() != QNetworkReply::NoError ){
            qCritical() << "Error: " << reply->errorString();
            QMessageBox::warning(parentDialog,QObject::tr("Error"),reply->errorString());
            return QObject::tr("{\"stat\": \"local-error\" ,\"text\": \"%1\"}").arg(reply->errorString());
        }else {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            switch (statusCode) {
                case 301:
                case 302:
                case 307:
                //Redirect
//                    qDebug() << "Redirected: " << reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
                    request.setUrl(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl());
                    reply = accsMgr.get(request);//,postData.toString(QUrl::FullyEncoded).toUtf8());
                    QObject::connect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()) );
                    waitLoop.exec();
                    QObject::disconnect( reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
                    break;
                case 200:
                qDebug() << "Code is 200";
                break;
                default:
                qDebug() << "Error: language may be incorrect";
                return QObject::tr("{\"stat\": \"local-error\" ,\"text\": \"What should have been redirected is not redirected. \n"
                                   "- Check that the language specification is correct.\n"
                                   "- The target string may be too long. Try shortening the string.\"}");
                break;
            }
}
        QByteArray return_value=reply->readAll();
//        qDebug() << "Translator:" << QString::fromUtf8(return_value);
        return QString::fromUtf8(return_value);
}
QString GTranslator::getUrl(){
    QString urltmp;
    QNetworkRequest request;
    QUrl httpurl(FETCH_URL);
    request.setUrl(httpurl);
    QNetworkAccessManager accsMgr;
//    accsMgr.setNetworkAccessible(QNetworkAccessManager::Accessible);
    QNetworkReply *reply = accsMgr.get(request);
    QEventLoop *eventloop = new QEventLoop();
    QObject::connect(reply,SIGNAL(finished()),eventloop,SLOT(quit()));
    eventloop->exec();
    delete eventloop;
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if( reply->error() != QNetworkReply::NoError ){
        QMessageBox::warning(parentDialog,QObject::tr("Error"),QObject::tr("An error occurred while getting the download URL.\n"
                                                                     "Error message:%1\n"
                                                                     "There may be a bug in the program. Use the latest version of the program.\n"
                                                                     "In this case, a standard URL is used. As a result, errors may occur and translation may not be performed correctly.").arg(reply->errorString()));
        urltmp = REQUEST_URL_TMP;
    }else if(statusCode != 200){
        QMessageBox::warning(parentDialog,QObject::tr("Error"),QObject::tr(
        "An error occurred when accessing."
        "HTTP %1"
        "Use the default URL.").arg(statusCode));
        urltmp = REQUEST_URL_TMP;
    }else{
        qDebug()  << "Fetched success.";
        urltmp = QString::fromUtf8(reply->readAll());
    }
    urltmp = urltmp.trimmed();
    return urltmp;
}
