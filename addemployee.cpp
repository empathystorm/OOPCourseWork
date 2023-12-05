#include "addemployee.h"
#include "ui_addemployee.h"
#include <QMessageBox>

addemployee::addemployee(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addemployee)
{
    ui->setupUi(this);
    setWindowTitle("Добавить запись");
}

addemployee::~addemployee()
{
    delete ui;
}

bool addemployee::isInt(const QString &str)
{
    bool ok;
    str.toInt(&ok);
    return ok;
}

void addemployee::on_pushButtonAdd_clicked()
{
    QString name = ui->lineEditName->text();
    QString department = ui->lineEditDepartment->text();
    QString salary = ui->lineEditSalary->text();
    QString experience = ui->lineEditExperience->text();
    if (name.isEmpty() || department.isEmpty() || salary.isEmpty() || experience.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Вы не заполнили все поля!");
        return;
    }
    if (!isInt(salary) || !isInt(experience)) {
        QMessageBox::warning(this, "Ошибка", "Вы ввели не число в поле зарплаты/стажа");
        return;
    }
    emit signal_add(name, department, salary, experience);
    close();
}

