#include "producthandling.h"
#include "ui_producthandling.h"

ProductHandling::ProductHandling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductHandling)
{
    ui->setupUi(this);
}

ProductHandling::~ProductHandling()
{
    delete ui;
}
