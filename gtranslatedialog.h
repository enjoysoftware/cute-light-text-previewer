#ifndef GTRANSLATEDIALOG_H
#define GTRANSLATEDIALOG_H

#include <QDialog>

namespace Ui {
class GTranslateDialog;
}

class GTranslateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GTranslateDialog(QWidget *parent = nullptr);
    ~GTranslateDialog();
    QString targetLang;
    QString sourceLang;
    QString text;
private:
    Ui::GTranslateDialog *ui;
    QString language;
};

#endif // GTRANSLATEDIALOG_H
