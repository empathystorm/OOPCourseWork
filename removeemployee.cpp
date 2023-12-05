#include "removeemployee.h"
#include "ui_removeemployee.h"
#include <QMessageBox>

RemoveEmployee::RemoveEmployee(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveEmployee)
{
    ui->setupUi(this);
    setWindowTitle("Удалить запись");
}

RemoveEmployee::~RemoveEmployee()
{
    delete ui;
}

bool RemoveEmployee::isInt(const QString &str)
{
    bool ok;
    str.toInt(&ok);
    return ok;
}

void RemoveEmployee::on_pushButtonDelete_2_clicked()
{
    QString ID = ui->lineEditID->text();
    if (ID.isEmpty() || !isInt(ID)) {
        QMessageBox::warning(this, "Ошибка", "Неверно введён ID!");
        return;
    }
    emit signal_remove(ID);
    close();
}

