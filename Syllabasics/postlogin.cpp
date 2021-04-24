#include "postlogin.h"
#include "ui_postlogin.h"

PostLogin::PostLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PostLogin)
{
    ui->setupUi(this);
}

PostLogin::~PostLogin()
{
    delete ui;
}
