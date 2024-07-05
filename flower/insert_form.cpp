#include "insert_form.h"
#include "ui_insert_form.h"

Insert_form::Insert_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insert_form)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), SLOT(insert()));
    connect(this, SIGNAL(rejected()), SLOT(close()));
}

Insert_form::~Insert_form()
{
    delete ui;
}

void Insert_form::getName(const QString& str){
    account=str;
}
void Insert_form::insert(){
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit_2->date();
    QString formate_date1, formate_date2;
    double cost;
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

    int day_count=d1.daysTo(d2);
    if(day_count>=0){
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
    command2="SELECT Flower_name, Count FROM Composition WHERE Name glob '"+ui->Composition->text()+"';";

    query.exec(command2);
    QSqlRecord rec=query.record();
    query.next();
    command3="SELECT Cost FROM Flowers WHERE Name glob '"+query.value(rec.indexOf("Flower_name")).toString()+"';";
     cost=query.value(rec.indexOf("Count")).toDouble();
      query.exec(command3);
      rec=query.record();
      query.next();
      cost*=query.value(rec.indexOf("Cost")).toDouble();
     cost*=ui->Count->text().toInt();
     if(day_count==1)
         cost=cost*1.25;
     else if(day_count>=2)
         cost=cost*1.15;
     command1="INSERT INTO Orders VALUES('"+account+"', '"+ui->Composition->text()+"', "+ui->Count->text()+", "
             +QString::number(cost)+", '"+formate_date1+"', '"+formate_date2+"');";
    query.exec(command1);
    db.close();
}
}
