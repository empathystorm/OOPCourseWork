#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    setWindowTitle("База данных сотрудников");

    //созданте базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DB");
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
    model = new QSqlTableModel(this, db);
    model->setTable("Employee");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ФИО"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Отдел"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Зарплата"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Стаж"));

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //подключение к окну добавления записи
    AddEmployee = new addemployee;
    connect(AddEmployee, &addemployee::signal_add, this, &MainWindow::slot_add);

    //подключение к окну удаления записи
    formRemove = new RemoveEmployee;
    connect(formRemove, &RemoveEmployee::signal_remove, this, &MainWindow::slot_remove);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete query;
    delete model;
}

void MainWindow::slot_add(QString name, QString department, QString salary, QString experience)
{
    QString db_input = QString("INSERT INTO Employee (name,department,salary,experience) VALUES ('%1', '%2', %3, %4);").arg(name, department, salary, experience);
    if (!query->exec(db_input)) {
        qDebug() << "Unable to insert field: " << query->lastError();
    }
    query->clear();
    model->select();
}

void MainWindow::slot_remove(QString ID)
{
    QString db_input = QString("DELETE FROM Employee WHERE ID=%1;").arg(ID);
    if (!query->exec(db_input)) {
        qDebug() << "Unable to delete field: " << query->lastError();
    }
    query->clear();
    model->select();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1 == "") {
        model->setFilter("");
        model->select();
        ui->tableView->setModel(model);
        return;
    }
    model->setFilter(QString("name LIKE '%%1%' OR department LIKE '%%2%'").arg(arg1, arg1));
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (arg1 == "") {
        model->setFilter("");
        model->select();
        ui->tableView->setModel(model);
        return;
    }
    QStringList states = {"salary", "experience"};
    QStringList operations = {"=", "<", ">"};
    model->setFilter(QString("%1 %2 %3").arg(states[ui->comboBox->currentIndex()],
                                             operations[ui->comboBox_2->currentIndex()],
                                             arg1));
    model->select();
    ui->tableView->setModel(model);
}


void MainWindow::on_actionAdd_triggered()
{
    AddEmployee->show();
}


void MainWindow::on_actionDelete_triggered()
{
    formRemove->show();
}

