#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

#include "addemployee.h"
#include "removeemployee.h"
#include "EmployeeBase.h"

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

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

    void on_actionCreate_triggered();

    void on_actionOpen_triggered();

    void on_actionInfo_triggered();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    addemployee *AddEmployee;
    RemoveEmployee *formRemove;
    EmployeeBase base;

public slots:
    void slot_add(QString, QString, QString, QString);
    void slot_remove(QString);
};
#endif // MAINWINDOW_H


