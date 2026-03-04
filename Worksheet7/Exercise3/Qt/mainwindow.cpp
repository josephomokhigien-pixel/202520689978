#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "optiondialog.h"
#include <QDialog>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->viewport()->installEventFilter(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton1);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage,   ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked,  this, &MainWindow::handleTreeClicked);
    ui->treeView->addAction(ui->actionItem_Options);

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
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

}



MainWindow::~MainWindow()
{

    delete ui;
}
void MainWindow::handleButton1() {
    QMessageBox::information(this, "Click", "Button 1 clicked");
     emit statusUpdateMessage("Button 1 clicked", 0);
}

void MainWindow::handleButton2()
{
    OptionDialog dialog(this);

    // For now, just preload some values so you can SEE it works
    dialog.setValues("TestName", 128, 64, 255, true);

    if (dialog.exec() == QDialog::Accepted) {
        QString name;
        int r, g, b;
        bool vis;
        dialog.getValues(name, r, g, b, vis);

        emit statusUpdateMessage(
            QString("Dialog accepted: %1 RGB(%2,%3,%4) visible=%5")
                .arg(name).arg(r).arg(g).arg(b).arg(vis),
            0
            );
    } else {
        emit statusUpdateMessage("Dialog rejected", 0);
    }

}

void MainWindow::handleTreeClicked() {
    QModelIndex index = ui->treeView->currentIndex();

    ModelPart* selectedPart =
        static_cast<ModelPart*>(index.internalPointer());

    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage("Selected: " + text, 0);
}

void MainWindow::on_actionopen_file_triggered()
{
    // 1) Choose a file
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open text file",
        QString(),
        "Text Files (*.txt);;All Files (*.*)"
        );

    if (filePath.isEmpty())
        return;

    // 2) Get selected item in the tree
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) {
        emit statusUpdateMessage("Select a tree item first", 0);
        return;
    }

    ModelPart* item = static_cast<ModelPart*>(index.internalPointer());
    if (!item) return;

    // 3) Set item name to the file name (choose one of these)
    QFileInfo info(filePath);

    QString newLabel = info.fileName();      // e.g. hello.txt
    // QString newLabel = info.baseName();   // e.g. hello (no .txt)

    item->set(0, newLabel);  // column 0 = "Part" name

    // 4) Refresh the view
    QModelIndex left  = index.sibling(index.row(), 0);
    QModelIndex right = index.sibling(index.row(), 1);
    emit partList->dataChanged(left, right);

    emit statusUpdateMessage("Renamed item to: " + newLabel, 0);
}
void MainWindow::on_actionItem_Options_triggered()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) {
        emit statusUpdateMessage("Select an item first", 0);
        return;
    }

    ModelPart *item = static_cast<ModelPart*>(index.internalPointer());
    if (!item) return;

    // ---- read current values from ModelPart ----
    QString name = item->data(0).toString();

    int r = static_cast<int>(item->getColourR());
    int g = static_cast<int>(item->getColourG());
    int b = static_cast<int>(item->getColourB());

    bool vis = item->visible();

    // ---- open dialog pre-filled ----
    OptionDialog dialog(this);
    dialog.setValues(name, r, g, b, vis);

    // ---- if OK: save back into ModelPart ----
    if (dialog.exec() == QDialog::Accepted)
    {
        dialog.getValues(name, r, g, b, vis);

        item->set(0, name); // column 0 = Part name
        item->setColour(static_cast<unsigned char>(r),
                        static_cast<unsigned char>(g),
                        static_cast<unsigned char>(b));
        item->setVisible(vis);

        // Update "Visible?" column too so the tree shows it (column 1)
        item->set(1, vis ? "true" : "false");

        // refresh view
        partList->dataChanged(index, index);
        emit statusUpdateMessage("Item updated", 0);
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->treeView->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton)
        {
            QModelIndex index = ui->treeView->indexAt(mouseEvent->pos());
            if (index.isValid())
                ui->treeView->setCurrentIndex(index); // <-- makes your currentIndex correct
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
