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
    EmployeeBase() {}

    void create(QMainWindow* mainWindow, QString const& file_name) {
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

    void create(QMainWindow* mainWindow) {
        create(mainWindow, "DB");
    }

    QSqlTableModel* get_model() {
        return model;
    }

    void add_record(QString name, QString department, QString salary, QString experience) {
        QString db_input = QString("INSERT INTO Employee (name,department,salary,experience) VALUES ('%1', '%2', %3, %4);").arg(name, department, salary, experience);
        if (!query->exec(db_input)) {
            qDebug() << "Unable to insert field: " << query->lastError();
        }
        query->clear();
        model->select();
    }

    void remove_record(QString ID) {
        QString db_input = QString("DELETE FROM Employee WHERE ID=%1;").arg(ID);
        if (!query->exec(db_input)) {
            qDebug() << "Unable to delete field: " << query->lastError();
        }
        query->clear();
        model->select();
    }

    void filter_text(const QString &arg1) {
        if (arg1 == "") {
            model->setFilter("");
            model->select();
            return;
        }
        model->setFilter(QString("name LIKE '%%1%' OR department LIKE '%%2%'").arg(arg1, arg1));
        model->select();
    }

    void filter_numbers(const QString &arg1, int index1, int index2) {
        if (arg1 == "") {
            model->setFilter("");
            model->select();
            return;
        }
        QStringList states = {"salary", "experience"};
        QStringList operations = {"=", "<", ">"};
        model->setFilter(QString("%1 %2 %3").arg(states[index1],
                                                 operations[index2],
                                                 arg1));
        model->select();
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
