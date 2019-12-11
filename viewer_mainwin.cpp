#include "viewer_mainwin.h"
#include "ui_viewer_mainwin.h"
#include <QIcon>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#define ICON_OPEN QIcon::fromTheme("document-open")
#define ICON_PRINT QIcon::fromTheme("document-print")
viewer_mainwin::viewer_mainwin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actionSetup();
    iconSetup();
}

viewer_mainwin::~viewer_mainwin()
{
    delete ui;
}
void viewer_mainwin::actionSetup(){
    qDebug() << "Connecting...";
    connect(ui->actionOpen_O,SIGNAL(triggered()),this,SLOT(fileOpen()));
    qDebug() << "Done";
}
void viewer_mainwin::iconSetup(){
    qDebug() << "Setting up icons";
    ui->actionOpen_O->setIcon(ICON_OPEN);
    qDebug() << "Done";
}
void viewer_mainwin::fileOpen(){

}
