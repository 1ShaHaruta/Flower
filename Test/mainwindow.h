#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QListView>
#include "input_device.h"
#include "insert_form.h"
#include "delete_form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
void change_status();
void set_account(const QString& str);
void on_action_triggered();

void on_action_2_triggered();

void on_action_3_triggered();

void on_action_4_triggered();

void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

void on_comboBox_activated(int index);

void on_comboBox_2_activated(int index);

void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    Input_Dialog* password_dlg;
    Insert_form* insert_frm;
    Delete_form* delete_frm;
    QSqlDatabase *db;
    QString account;
    bool direction=false;
};
#endif // MAINWINDOW_H
