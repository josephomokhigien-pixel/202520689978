#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();
    void setValues(const QString &name, int r, int g, int b, bool visible);
    void getValues(QString &name, int &r, int &g, int &b, bool &visible);

private:
    Ui::OptionDialog *ui;
private slots:
};

#endif // OPTIONDIALOG_H
