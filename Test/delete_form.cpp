#include "delete_form.h"
#include "ui_delete_form.h"

Delete_form::Delete_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete_form)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), SLOT(delete_com()));
    connect(this, SIGNAL(rejected()), SLOT(close()));
}

Delete_form::~Delete_form()
{
    delete ui;
}

void Delete_form::getName(const QString& str){
    account =str;
}
void Delete_form::delete_com(){
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit_2->date();
    QString formate_date1, formate_date2;
QString command1, command2, command3;
    if(d1.month()<10){
            formate_date1="2024-0"+QString::number(d1.month());
    }else formate_date1="2024-"+QString::number(d1.month());
    if(d1.day()<10){
        formate_date1+=QString("-0"+QString::number(d1.day()));
    }else formate_date1+=QString("-"+QString::number(d1.day()));
    //////////////////////////////////////////
    if(d2.month()<10){
            formate_date2="2024-0"+QString::number(d2.month());
    }else formate_date2="2024-"+QString::number(d2.month());
    if(d2.day()<10){
        formate_date2+=QString("-0"+QString::number(d2.day()));
    }else formate_date2+=QString("-"+QString::number(d2.day()));

    QSqlDatabase db=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db.setDatabaseName("../DB/My_db.db");
    db.open();
    if(!db.isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }
    QSqlQuery query(db);
    QString command="DELETE FROM Orders WHERE Name glob '"+account+"' AND Composition glob '"+ui->comp->text()
            +"' AND Count = "+ui->count->text()+" AND Order_date glob '"+formate_date1+"' AND Date_of_completion glob '"+formate_date2+"';";
    query.exec(command);

}
