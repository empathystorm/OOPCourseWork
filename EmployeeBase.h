#ifndef EMPLOYEEBASE_H
#define EMPLOYEEBASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QMainWindow>

#include <QDebug>
#include <QSqlError>

class EmployeeBase {
public:
    EmployeeBase(QMainWindow* mainWindow, QString const& file_name) {
        //созданте базы данных
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(file_name);
        query = new QSqlQuery(db);
        if (!db.open()) {
            throw "can't open database";
        }
        if (!db.tables().contains("Employee")) {
            query->clear();
            QString db_input = "CREATE TABLE Employee(ID INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, department TEXT, salary INTEGER, experience INTEGER)";
            if (!query->exec(db_input)) {
                qDebug() << "Unable to create table: " << query->lastError();
            }
            query->clear();
        }

        //создание модели
        model = new QSqlTableModel(mainWindow, db);
        model->setTable("Employee");
        model->select();
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("ФИО"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Отдел"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Зарплата"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Стаж"));
    }

    EmployeeBase(QMainWindow* mainWindow) {
        EmployeeBase(mainWindow, "DB");
    }

    QSqlTableModel*& get_model() {
        return model;
    }

    ~EmployeeBase() {
        delete query;
        delete model;
    }
private:
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
};

#endif // EMPLOYEEBASE_H
