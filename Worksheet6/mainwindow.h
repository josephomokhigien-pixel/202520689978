#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPartList.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void statusUpdateMessage(const QString &message, int timeout);

public slots:
    void handleButton1();
    void handleButton2();

private:
    Ui::MainWindow *ui;
     ModelPartList* partList;
};
#endif // MAINWINDOW_H
