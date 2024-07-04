#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include "validator.h"


class Input_Dialog:public QDialog{
    Q_OBJECT
private:
    QLineEdit* line1,*line2;
    QPushButton *Sign_up,*Sign_in, *Cancel;
private slots:
    void check();
    void newone();
signals:
    void is_direction();
    void send_account(const QString&);
public:
    Input_Dialog(QWidget* pwgt = 0);
    ~Input_Dialog();
};

#endif // INPUT_DEVICE_H
