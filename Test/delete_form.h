#ifndef DELETE_FORM_H
#define DELETE_FORM_H


#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include <QDialog>
namespace Ui {
class Delete_form;
}

class Delete_form : public QDialog
{
    Q_OBJECT

public:
    explicit Delete_form(QWidget *parent = nullptr);
    ~Delete_form();
    void getName(const QString& str);

private slots:
    void delete_com();
private:
    Ui::Delete_form *ui;
    QString account;
};

#endif // DELETE_FORM_H
