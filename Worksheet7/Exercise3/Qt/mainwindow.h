#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPartList.h"
#include <vtkSmartPointer.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class vtkRenderer;
class vtkGenericOpenGLRenderWindow;

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
    void handleTreeClicked();
    void updateRender();
    void updateRenderFromTree(ModelPart* item);

private slots:
    void on_actionopen_file_triggered();
    void on_actionItem_Options_triggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::MainWindow *ui;
     ModelPartList* partList;

    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
};
#endif // MAINWINDOW_H
