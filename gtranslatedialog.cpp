#include "gtranslatedialog.h"
#include "ui_gtranslatedialog.h"
#include "gtranslator.h"
#include "ui_viewer_mainwin.h"
#include <QLocale>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
GTranslateDialog::GTranslateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GTranslateDialog)
{
    ui->setupUi(this);
    ui->translateButton->setEnabled(false);
    connect(ui->sourceLangBox,SIGNAL(textChanged(const QString &)),this,SLOT(boxCheck()));
    QString locale=QLocale::system().name();
    QFile langfile("resources/lang.list");
    if(!langfile.open(QIODevice::ReadOnly | QFile::Text)){
    QMessageBox::information(this,"Debug",langfile.errorString());
    }else{
        QTextStream str(&langfile);
        QString list;
        while(!str.atEnd()){
        list = str.readLine().trimmed();
        qDebug() << list;
        QStringList data = list.split("=");
        ui->comboBox->addItem(data[0],data[1]);
        qDebug() << data[0] << "," << data[1];
        }
        langfile.close();
    }
}

GTranslateDialog::~GTranslateDialog()
{
    delete ui;
}
void GTranslateDialog::setText(const QString& tmptext){
    text = tmptext;
    return;
}
void GTranslateDialog::showEvent(QShowEvent *){
    ui->translatedText->setPlainText(text);
}
void GTranslateDialog::boxCheck(){
//    if(ui->sourceLangBox->text() != "" && ui->targetLangBox->text() != ""){
//        ui->translateButton->setEnabled(true);
//    }else{
//        ui->translateButton->setEnabled(false);
//    }
}
void GTranslateDialog::startTranslate(){
//    GTranslator translator(ui->targetLangBox->text(),ui->sourceLangBox->text(),text,this);
//    ui->translatedText->setPlainText(translator.translate());
}
