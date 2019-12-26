#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileInfo>
#include "aboutdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class viewer_mainwin : public QMainWindow
{
    Q_OBJECT

public:
    viewer_mainwin(QWidget *parent = nullptr);
    ~viewer_mainwin();

private:
    void iconSetup();
    void actionSetup();
    QString loadFile(QString);
    Ui::MainWindow *ui;
    AboutDialog *about_;

private slots:
    void fileOpen();
    void filePrint();
    void showabout();
};
#endif // MAINWINDOW_H
