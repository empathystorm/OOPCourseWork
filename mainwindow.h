#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QHeaderView>

#include <QMessageBox>

#include <QDebug>
#include <QSqlError>

#include "addemployee.h"
#include "removeemployee.h"

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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    addemployee *AddEmployee;
    RemoveEmployee *formRemove;

public slots:
    void slot_add(QString, QString, QString, QString);
    void slot_remove(QString);
};
#endif // MAINWINDOW_H
