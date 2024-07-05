#ifndef DELETE_FORM_H
#define DELETE_FORM_H

#include <QDialog>

namespace Ui {
class Delete_form;
}

class Delete_form : public QDialog
{
    Q_OBJECT

public:
    explicit Delete_form(QWidget *parent = nullptr);
    ~Delete_form();

private:
    Ui::Delete_form *ui;
};

#endif // DELETE_FORM_H
