#include "input_device.h"

void Input_Dialog::check(){
    if(!this->line1->text().isEmpty()||!this->line2->text().isEmpty())
if(Validator::check_customer(this->line1->text(), this->line2->text())){
    if(Validator::check_rights(this->line1->text()))
        emit is_direction();
    emit send_account(this->line1->text());
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
    db.setDatabaseName("/home/ilya/Рабочий стол/Flower/DB/My_db.db");
    db.open();
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

  bool Validator::check_customer(const QString& _login, const QString& _password){
      QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
      db.setDatabaseName("/home/ilya/Рабочий стол/Flower/DB/My_db.db");
      db.open();
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
      db.setDatabaseName("/home/ilya/Рабочий стол/Flower/DB/My_db.db");
      db.open();
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
      db.setDatabaseName("/home/ilya/Рабочий стол/Flower/DB/My_db.db");
      db.open();
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
