#include "viewer_mainwin.h"
#include "ui_viewer_mainwin.h"
#include <QIcon>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QPrintDialog>
#include <QMessageBox>
#include "defines.h"
QString const extern APP_NAME;
viewer_mainwin::viewer_mainwin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actionSetup();
    iconSetup();
    is_opened = false;
    is_empty = false;
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
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(setEmptyStatus()));
    qDebug() << tr("Done");
    this->setContextMenuPolicy(Qt::NoContextMenu);
    about_=new AboutDialog();
    ui->action_Print->setEnabled(is_opened);
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
    QString name=filed.getOpenFileName(this,tr("Open file"),QDir::currentPath(),tr("Text files(*.txt);;"
                                                                                   "HTML document(*.html *.htm);;"
                                                                                   "All files(*.* *)"));
    if (name.isEmpty()){
        return;
    }
    QString content=loadFile(name);
    ui->textEdit->setText(content);
    QFileInfo forpath(name);
    QDir::setCurrent(forpath.absolutePath());
}
void viewer_mainwin::filePrint(){
    QPrintDialog pdlg;
    if(is_empty){
        if(QMessageBox::question(this,tr("Question"),tr("This file is empty.\nDo you want to continue?")) == QMessageBox::No) {
            return;
        }
    }
    int res=pdlg.exec();
    if(res == QPrintDialog::Accepted){
        ui->textEdit->print((QPagedPaintDevice*)pdlg.printer());
}
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
    is_opened = true;
    return line;
}
void viewer_mainwin::showabout(){
    about_->show();
}
void viewer_mainwin::setEmptyStatus(){
    ui->action_Print->setEnabled(is_opened);
    if (is_opened){
    if(ui->textEdit->toPlainText() == ""){
        is_empty = true;
        qDebug() << tr("Empty in textEdit");
    }
    }
}
