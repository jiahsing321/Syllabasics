#ifndef POSTLOGIN_H
#define POSTLOGIN_H

#include <QMainWindow>

namespace Ui {
class PostLogin;
}

class PostLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit PostLogin(QWidget *parent = 0);
    ~PostLogin();

private:
    Ui::PostLogin *ui;
};

#endif // POSTLOGIN_H
