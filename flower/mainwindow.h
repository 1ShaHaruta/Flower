#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include "input_device.h"

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
private:
    Ui::MainWindow *ui;
    Input_Dialog* password_dlg;
    QSqlDatabase *db;
    QString account;
    bool direction;
};
#endif // MAINWINDOW_H
