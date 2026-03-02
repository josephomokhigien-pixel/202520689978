#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage,   ui->statusbar, &QStatusBar::showMessage);
    this->partList = new ModelPartList("PartsList");
    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        ModelPart* childItem = new ModelPart({name, visible});
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            ModelPart* subItem = new ModelPart({name, visible});
            childItem->appendChild(subItem);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::handleButton1() {
    QMessageBox::information(this, "Click", "Button 1 clicked");
     emit statusUpdateMessage("Button 1 clicked", 0);
}

void MainWindow::handleButton2() {
    QMessageBox::information(this, "Click", "Button 2 clicked");
}
