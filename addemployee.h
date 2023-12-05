#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>

namespace Ui {
class addemployee;
}

class addemployee : public QDialog
{
    Q_OBJECT

public:
    explicit addemployee(QWidget *parent = nullptr);
    ~addemployee();

private slots:
    void on_pushButtonAdd_clicked();

private:
    Ui::addemployee *ui;
    bool isInt(QString const&);

signals:
    void signal_add(QString, QString, QString, QString);
};

#endif // ADDEMPLOYEE_H
