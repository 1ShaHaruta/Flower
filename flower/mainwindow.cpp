#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow), password_dlg(new Input_Dialog), db(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    //ui->centralwidget->hide();
    password_dlg->show();
    connect(password_dlg, SIGNAL(is_direction()), this, SLOT(change_status()));
    connect(password_dlg, SIGNAL(send_account(const QString&)), this, SLOT(set_account(const QString&)));
    connect(password_dlg, SIGNAL(rejected()), this, SLOT(close()));
    db->setDatabaseName("/home/ilya/Рабочий стол/Flower/DB/My_db.db");
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
    ui->name->setText(str+", status: ");
    direction=true;
}

