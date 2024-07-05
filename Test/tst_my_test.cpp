#include <QtTest>
#include <QTest>
#include "delete_form.h"
#include "input_device.h"
#include "mainwindow.h"
#include "validator.h"
#include "insert_form.h"
// add necessary includes here

class My_test : public QObject
{
    Q_OBJECT

public:
    My_test();
    ~My_test();

private slots:
    void test_case1();
void check_customer();
void check_rights();
void check_correctness();
};

My_test::My_test()
{
}

My_test::~My_test()
{

}

void My_test::test_case1()
{

}

void My_test::check_customer()
{
    Validator val;
QCOMPARE(val.check_customer("login","password"),false);
QCOMPARE(val.check_customer("IlyaSirotkin","11062005"),true);
QCOMPARE(val.check_customer("",""),false);
}
void My_test::check_rights()
{
    Validator val;
QCOMPARE(val.check_rights("login"),false);
QCOMPARE(val.check_rights("IlyaSirotkin"),true);
}
void My_test::check_correctness()
{
    Validator val;
QCOMPARE(val.check_correctness("login*-+","password"),false);
QCOMPARE(val.check_correctness("",""),false);
QCOMPARE(val.check_correctness("Логин","Пароль"),false);
}
QTEST_APPLESS_MAIN(My_test)

#include "tst_my_test.moc"
