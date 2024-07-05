#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
class Validator{
public:
    static bool check_customer(const QString& _login, const QString& _password);
    static bool check_rights(const QString& _login);
    static bool check_correctness(const QString& _login, const QString& _password);
};

#endif // VALIDATOR_H
