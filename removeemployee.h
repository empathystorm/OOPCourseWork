#ifndef REMOVEEMPLOYEE_H
#define REMOVEEMPLOYEE_H

#include <QDialog>

namespace Ui {
class RemoveEmployee;
}

class RemoveEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveEmployee(QWidget *parent = nullptr);
    ~RemoveEmployee();

private:
    Ui::RemoveEmployee *ui;
    bool isInt(QString const&);

signals:
    void signal_remove(QString);
private slots:
    void on_pushButtonDelete_2_clicked();
};

#endif // REMOVEEMPLOYEE_H
