#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);

    // Optional: set ranges if you didn't in Designer
    ui->spinBoxR->setRange(0, 255);
    ui->spinBoxG->setRange(0, 255);
    ui->spinBoxB->setRange(0, 255);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::setValues(const QString &name, int r, int g, int b, bool visible)
{
    ui->lineEditName->setText(name);
    ui->spinBoxR->setValue(r);
    ui->spinBoxG->setValue(g);
    ui->spinBoxB->setValue(b);
    ui->checkBoxVisible->setChecked(visible);
}

void OptionDialog::getValues(QString &name, int &r, int &g, int &b, bool &visible)
{
    name = ui->lineEditName->text();
    r = ui->spinBoxR->value();
    g = ui->spinBoxG->value();
    b = ui->spinBoxB->value();
    visible = ui->checkBoxVisible->isChecked();
}
