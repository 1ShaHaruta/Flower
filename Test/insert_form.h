#ifndef INSERT_FORM_H
#define INSERT_FORM_H

#include <QDialog>

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Insert_form;
}

class Insert_form : public QDialog
{
    Q_OBJECT

public:
    explicit Insert_form(QWidget *parent = nullptr);
    void getName(const QString& str);
    ~Insert_form();
private slots:
    void insert();
private:
    Ui::Insert_form *ui;
    QString account;
};

#endif // INSERT_FORM_H
