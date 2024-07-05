#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow), password_dlg(new Input_Dialog)
{
//, db(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
    password_dlg->show();
    connect(password_dlg, SIGNAL(is_direction()), this, SLOT(change_status()));
    connect(password_dlg, SIGNAL(send_account(const QString&)), this, SLOT(set_account(const QString&)));
    connect(password_dlg, SIGNAL(rejected()), this, SLOT(close()));
    QPalette pal1;
    pal1.setBrush (this->backgroundRole () ,QBrush (QPixmap ("../Images/roza_1920x1080.jpg")));
    this->setPalette(pal1);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_status(){
    ui->status->setText("direction");
    direction=true;
}

void MainWindow::set_account(const QString& str){
    account=str;
    ui->name->setText(ui->name->text()+str+", Status: ");
}


void MainWindow::on_action_triggered()
{
    if(direction){
    db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("../DB/My_db.db");
    db->open();
    if(!db->isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }
    QSqlQuery query(*db);
    QString command1="SELECT * FROM Flowers";
    query.exec(command1);
     QSqlRecord rec= query.record();
     QString buf;
     ui->textBrowser->clear();
    while (query.next()){
    buf="Название: "+query.value(rec.indexOf("Name")).toString()+"  Сорт: "+query.value(rec.indexOf("Sort")).toString()
            +"  Стоимость: "+query.value(rec.indexOf("Cost")).toString();
    ui->textBrowser->append(buf);
   }
       db->close();
    }else {
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>У Вас недостаточно прав</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }
}


void MainWindow::on_action_2_triggered()
{
    if(direction){
        db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        db->setDatabaseName("../DB/My_db.db");
        db->open();
        if(!db->isOpen()){
            QMessageBox msg(QMessageBox::Information, "Message",
                            "<b>База данных не открыта</b>"
                            ,QMessageBox::Ok);
            msg.exec();
        }
        QSqlQuery query2(*db), query(*db);
        QString command1="SELECT * FROM Composition", command2;
        query.exec(command1);
         QSqlRecord rec= query.record(), rec2;
         QString buf, flower_name;
         double cost;
         ui->textBrowser->clear();

        while (query.next()){
            flower_name=query.value(rec.indexOf("Flower_name")).toString();
            command2="SELECT Cost FROM Flowers WHERE Name glob '"+flower_name+"';";
            query2.exec(command2);
            rec2=query2.record();
            query2.next();
            cost=query2.value(rec2.indexOf("Cost")).toDouble();
        buf="Название: "+query.value(rec.indexOf("Name")).toString()+" Цветы: "+
                query.value(rec.indexOf("Flower_name")).toString()+"  Сорт: "+query.value(rec.indexOf("Sort_name")).toString()+
                "  Стоимость: "+QString::number(query.value(rec.indexOf("Count")).toInt()*cost);
        ui->textBrowser->append(buf);
       }
           db->close();
        }else {
            QMessageBox msg(QMessageBox::Information, "Message",
                            "<b>У Вас недостаточно прав</b>"
                            ,QMessageBox::Ok);
            msg.exec();
        }
    }



void MainWindow::on_action_3_triggered()
{
    if(direction){
        db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        db->setDatabaseName("../DB/My_db.db");
        db->open();
        if(!db->isOpen()){
            QMessageBox msg(QMessageBox::Information, "Message",
                            "<b>База данных не открыта</b>"
                            ,QMessageBox::Ok);
            msg.exec();
        }
        QSqlQuery query(*db);
        QString command1="SELECT * FROM Orders";
        query.exec(command1);
         QSqlRecord rec= query.record();
         QString buf;
         ui->textBrowser->clear();

        while (query.next()){
        buf="Заказчик: "+query.value(rec.indexOf("Name")).toString()+" Композиция: "+query.value(rec.indexOf("Composition")).toString()
                +" Количество: "+query.value(rec.indexOf("Count")).toString()+"  Стоимость: "+
                query.value(rec.indexOf("Cost")).toString()+"  Дата заказа: "+
                query.value(rec.indexOf("Order_date")).toString()+" Дата выполнения: "+
                query.value(rec.indexOf("Date_of_completion")).toString();
        ui->textBrowser->append(buf);
       }
           db->close();
        }else {
            QMessageBox msg(QMessageBox::Information, "Message",
                            "<b>У Вас недостаточно прав</b>"
                            ,QMessageBox::Ok);
            msg.exec();
        }
}


void MainWindow::on_action_4_triggered()
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
        db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        db->setDatabaseName("../DB/My_db.db");
        db->open();
        if(!db->isOpen()){
            QMessageBox msg(QMessageBox::Information, "Message",
                            "<b>База данных не открыта</b>"
                            ,QMessageBox::Ok);
            msg.exec();
        }
        QSqlQuery query(*db);
        QString command1="SELECT * FROM Orders WHERE Name glob '"+account+"';";
        query.exec(command1);
         QSqlRecord rec= query.record();
         QString buf;
         ui->textBrowser->clear();
         ui->textBrowser->append("Мои заказы: ");
        while (query.next()){
        buf="Композиция: "+query.value(rec.indexOf("Composition")).toString()
                +" Количество: "+query.value(rec.indexOf("Count")).toString()+"  Стоимость: "+
                query.value(rec.indexOf("Cost")).toString()+"  Дата заказа: "+
                query.value(rec.indexOf("Order_date")).toString()+" Дата выполнения: "+
                query.value(rec.indexOf("Date_of_completion")).toString();
        ui->textBrowser->append(buf);
       }
           db->close();
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
    QDate d1=ui->dateEdit_2->date(), d2=ui->dateEdit->date();
    QString formate_date1, formate_date2;

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
    db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("../DB/My_db.db");
    db->open();
    if(!db->isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }

    QSqlQuery query(*db);
    QString command1="SELECT Cost FROM Orders WHERE Date_of_completion BETWEEN '"+formate_date1+"' AND '"+formate_date2+"';";
    query.exec(command1);
     QSqlRecord rec= query.record();
     double cost=0;
     ui->textBrowser->clear();
     ui->textBrowser->append("Прибыль за указанный период: ");
    while (query.next()){
    cost+=query.value(rec.indexOf("Cost")).toDouble();
   }
     ui->textBrowser->append(QString::number(cost));
       db->close();
    }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
    db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("../DB/My_db.db");
    db->open();
    if(!db->isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }

    QSqlQuery query(*db);
    QString command1="SELECT Composition, COUNT(*) FROM Orders GROUP BY Composition";
    query.exec(command1);
     QSqlRecord rec= query.record();
     QString buf;
     ui->textBrowser->clear();
     ui->textBrowser->append("Популярность композиций: ");
    while (query.next()){
    buf=query.value(rec.indexOf("Composition")).toString()+"  Кол-во проданных штук: "+query.value(rec.indexOf("COUNT(*)")).toString();
    ui->textBrowser->append(buf);
   }

       db->close();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
    QDate d1=ui->dateEdit_2->date(), d2=ui->dateEdit->date();
    QString formate_date1, formate_date2;

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
    db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("../DB/My_db.db");
    db->open();
    if(!db->isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }

    QSqlQuery query(*db), query2(*db);
    QString command1="SELECT Composition, COUNT(*) FROM Orders WHERE Date_of_completion BETWEEN '"+formate_date1+"' AND '"+formate_date2+"' GROUP BY Composition;",
            command2;
    query.exec(command1);
     QSqlRecord rec= query.record(), rec2;
     QString buf;
     ui->textBrowser->clear();
     ui->textBrowser->append("Кол-во использованных цветов за указанный период: ");
    while (query.next()){
        command2="SELECT Flower_name FROM Composition WHERE Name glob '"+query.value(rec.indexOf("Composition")).toString()+"';";
        query2.exec(command2);
        rec2= query2.record();
        query2.next();
        buf=query2.value(rec2.indexOf("Flower_name")).toString()+"  Кол-во проданных штук: "+query.value(rec.indexOf("COUNT(*)")).toString();
        ui->textBrowser->append(buf);
    }

   }

       db->close();
    }
}


void MainWindow::on_comboBox_activated(int index)
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
    switch(index){
    case 0:
ui->comboBox->hide();
ui->comboBox->show();
        break;
    case 1:
        insert_frm=new Insert_form;
        insert_frm->getName(account);
        insert_frm->show();
        break;


    }
    }
}


void MainWindow::on_comboBox_2_activated(int index)
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
    switch(index){
    case 0:
ui->comboBox_2->hide();
ui->comboBox_2->show();
        break;
    case 1:
        delete_frm=new Delete_form;
        delete_frm->getName(account);
        delete_frm->show();
        break;


    }
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(account.isEmpty()){
        QMessageBox msg(QMessageBox::Information, "Message", "<b>Вы не вошли в систему</b>",QMessageBox::Ok);
        msg.exec();
    }else{
    QDate d1=ui->dateEdit_2->date(), d2=ui->dateEdit->date();
    QString formate_date1, formate_date2;

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
    db=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("../DB/My_db.db");
    db->open();
    if(!db->isOpen()){
        QMessageBox msg(QMessageBox::Information, "Message",
                        "<b>База данных не открыта</b>"
                        ,QMessageBox::Ok);
        msg.exec();
    }

    QSqlQuery query(*db);
    QString command1="SELECT * FROM Orders WHERE Order_Date glob '"+formate_date1+"';";

    query.exec(command1);
     QSqlRecord rec= query.record();
     QString buf;
     ui->textBrowser->clear();
     ui->textBrowser->append("Все заказы поступившие указанного числа: ");
    while (query.next()){
        buf="Заказчик: "+query.value(rec.indexOf("Name")).toString()+" Композиция: "+query.value(rec.indexOf("Composition")).toString()
                +" Количество: "+query.value(rec.indexOf("Count")).toString()+"  Стоимость: "+
                query.value(rec.indexOf("Cost")).toString()+"  Дата заказа: "+
                query.value(rec.indexOf("Order_date")).toString()+" Дата выполнения: "+
                query.value(rec.indexOf("Date_of_completion")).toString();
        ui->textBrowser->append(buf);
    }

   }

       db->close();
    }
}

