#include "input_device.h"

void Input_Dialog::check(){
    if(!this->line1->text().isEmpty()||!this->line2->text().isEmpty())
if(Validator::check_customer(this->line1->text(), this->line2->text())){
    if(Validator::check_rights(this->line1->text()))
        emit is_direction();
    emit send_account(this->line1->text());
    this->accept();
    this->close();
}
else{
    QMessageBox msg(QMessageBox::Information, "Message","<b>Пользователь не найден</b>",QMessageBox::Ok);
    msg.setGeometry(855,540,250,100);
    msg.exec();
}
}

void Input_Dialog::newone(){
    if(!this->line1->text().isEmpty()||!this->line2->text().isEmpty())
if(Validator::check_correctness(this->line1->text(),this->line2->text())){
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
    QString command2="INSERT INTO Personal_data(Login, Password) VALUES(\""
            +this->line1->text()+ "\",\"" +this->line2->text()+ "\");";
    query.exec(command2);
    QMessageBox msg(QMessageBox::Information, "Message","<b>Регистрация прошла успешно</b>",QMessageBox::Ok);
    msg.setGeometry(855,540,250,100);
    msg.exec();
}else {

    QMessageBox msg(QMessageBox::Information, "Message",
                    "<b>Неверный формат логина или пароля (должны содержать латинские символы либо цифры, кол-во символов 4-20),"
                    "\n либо такой пользователь уже существует</b>"
                    ,QMessageBox::Ok);
    msg.setGeometry(855,540,250,100);
    msg.exec();
}

}

Input_Dialog::Input_Dialog(QWidget* pwgt):QDialog(pwgt) {
    line1=new QLineEdit;
    line2=new QLineEdit;
    QLabel* Login,* Password;
    Login=new QLabel("&Login");
    Password=new QLabel("&Password");

    Login->setBuddy(line1);
    Password->setBuddy(line2);
    Sign_in=new QPushButton("&Sign in");
    Sign_up=new QPushButton("&Sign up");
    Cancel = new QPushButton("&Cancel");
QString str1, str2;
str1=line1->text();
str2=line2->text();
    connect(Sign_in, SIGNAL(clicked()), SLOT(check()));
    connect(Sign_up, SIGNAL(clicked()), SLOT(newone()));
    connect(Cancel, SIGNAL(clicked()), SLOT(reject()));
    //Layout setup
    QGridLayout* Layout = new QGridLayout;

    Layout->addWidget(Login, 0, 0);
    Layout->addWidget(Password, 1, 0);
    Layout->addWidget(line1, 0, 1);
    Layout->addWidget(line2, 1, 1);
    Layout->addWidget(Sign_in, 2,0);
    Layout->addWidget(Sign_up, 2, 1);
    Layout->addWidget(Cancel, 2, 2);
    setLayout(Layout);
}
  Input_Dialog::~Input_Dialog(){
        delete line1;
        delete line2;
        delete Sign_in;
        delete Sign_up;
        delete Cancel;
    }


