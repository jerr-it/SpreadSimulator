#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Button_Run_pressed();

    void on_actionSave_Config_triggered();

    void on_actionLoad_Config_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
