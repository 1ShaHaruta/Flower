#include "delete_form.h"
#include "ui_delete_form.h"

Delete_form::Delete_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete_form)
{
    ui->setupUi(this);
}

Delete_form::~Delete_form()
{
    delete ui;
}
