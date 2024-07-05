#include "validator.h"

bool Validator::check_customer(const QString& _login, const QString& _password){
     if(_login.isEmpty()||_password.isEmpty()) return 0;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../DB/My_db.db");
    db.open();
    if(!db.isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }
    QSqlQuery query(db);
    QString command="SELECT * FROM Personal_data WHERE Login glob '"+_login+"' AND Password glob '"+_password+"';";
    query.exec(command);
    db.close();
    QSqlRecord rec= query.record();
    query.next();
    if(query.value(rec.indexOf("Login")) .toString()==_login&&query.value(rec.indexOf( "Password") ) .toString()==_password)
        return 1;
    else return 0;

}
bool Validator::check_correctness(const QString &_login, const QString &_password){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../DB/My_db.db");
    db.open();
    if(!db.isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }
    QSqlQuery query(db);
    QString command1="SELECT Login FROM Personal_data WHERE Login glob '"+_login+"';";
    query.exec(command1);
     QSqlRecord rec= query.record();
    query.next();
    QRegularExpression exp1("^\\w{4,20}$"), exp2("^[a-zA-Z0-9]{4,20}$");
    if(exp1.match(_login).hasMatch()&&exp2.match(_password).hasMatch()&&query.value(rec.indexOf("Login")).toString()!=_login){
        db.close();
        return 1;
    }else{
        db.close();
        return 0;
    }
}
bool Validator::check_rights(const QString &_login){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../DB/My_db.db");
    db.open();
    if(!db.isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }
    QSqlQuery query(db);
    QString command1="SELECT Right FROM Personal_data WHERE Login glob '"+_login+"';";
    query.exec(command1);
     QSqlRecord rec= query.record();
    query.next();
    db.close();
    if(query.value(rec.indexOf("Right")) .toString()=="direction")
        return 1;
    else return 0;
}
