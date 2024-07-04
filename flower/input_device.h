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

class Validator{
public:
    static bool check_customer(const QString& _login, const QString& _password);
    static bool check_rights(const QString& _login);
    static bool check_correctness(const QString& _login, const QString& _password);
};

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
