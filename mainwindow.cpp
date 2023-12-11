#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    setWindowTitle("База данных сотрудников");

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
}

void MainWindow::slot_add(QString name, QString department, QString salary, QString experience)
{
    base.add_record(name, department, salary, experience);
}

void MainWindow::slot_remove(QString ID)
{
    base.remove_record(ID);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    base.filter_text(arg1);
    ui->tableView->setModel(base.get_model());
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    base.filter_numbers(arg1, ui->comboBox->currentIndex(), ui->comboBox_2->currentIndex());
    ui->tableView->setModel(base.get_model());
}


void MainWindow::on_actionAdd_triggered()
{
    AddEmployee->show();
}


void MainWindow::on_actionDelete_triggered()
{
    formRemove->show();
}


void MainWindow::on_actionCreate_triggered()
{
    base.create(this);

    ui->tableView->setModel(base.get_model());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile()) {
        base.create(this, file_name);
        ui->tableView->setModel(base.get_model());
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}


void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::about(this,
                       "О программе",
                       "Курсовая работа по дисциплине ООП\n"
                       "Тема: Класс, характеризующий сотрудника предприятия\n"
                       "Вариант 2\n"
                       "Выполнил студент группы ИКПИ-24\n"
                       "Борисов Александр\n"
                       "Санкт-Петербург\n"
                       "2023 год");
}


void MainWindow::on_action_triggered()
{
    exit(0);
}

