#include "viewer_mainwin.h"
#include "ui_viewer_mainwin.h"
#include <QIcon>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#define ICON_OPEN QIcon::fromTheme("document-open")
#define ICON_PRINT QIcon::fromTheme("document-print")
#define ICON_EXIT QIcon::fromTheme("application-exit")
QString const extern APP_NAME;
viewer_mainwin::viewer_mainwin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actionSetup();
    iconSetup();
    QDir::setCurrent(QDir::homePath());
    ui->actionAbout->setText(tr("&About %1").arg(APP_NAME));
}

viewer_mainwin::~viewer_mainwin()
{
    delete ui;
}
void viewer_mainwin::actionSetup(){
    qDebug() << tr("Connecting actions...");
    connect(ui->actionOpen_O,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->action_Print,SIGNAL(triggered()),this,SLOT(filePrint()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showabout()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    qDebug() << tr("Done");
    about_=new AboutDialog();
}
void viewer_mainwin::iconSetup(){
    qDebug() << tr("Setting up icons");
    ui->actionOpen_O->setIcon(ICON_OPEN);
    ui->action_Print->setIcon(ICON_PRINT);
    ui->actionExit->setIcon(ICON_EXIT);
    qDebug() << tr("Done");
}
void viewer_mainwin::fileOpen(){
    QFileDialog filed;
    QString name=filed.getOpenFileName(this,tr("Open file"),QDir::currentPath(),tr("Text files(*.txt);;HTML document(*.html *.htm);;All files(*.*)"));
    if (name.isEmpty()){
        return;
    }
    QString content=loadFile(name);
    ui->textEdit->setText(content);
    QFileInfo forpath(name);
    QDir::setCurrent(forpath.absolutePath());
}
void viewer_mainwin::filePrint(){
}
QString viewer_mainwin::loadFile(QString filename){
    QFile qfilename(filename);
    if (!qfilename.open(QIODevice::ReadOnly)) {
        QString errMsg = qfilename.errorString();
        QMessageBox::critical(this,tr("Error"),tr("Can't open %1:\n%2").arg(qfilename.fileName(),errMsg));
        return tr("Error:\n%1").arg(errMsg);
    }
    QTextStream in(&qfilename);
    QString line;
    int lines;
    lines=0;
    while (!in.atEnd()){
        lines++;
        line +=in.readLine()+"\n";
    }
    ui->statusbar->showMessage(tr("Opened \"%1\" :%2 lines").arg(filename,QString::number(lines)));
    return line;
}
void viewer_mainwin::showabout(){
    about_->show();
}
