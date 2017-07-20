#include "fridgeexplorer.h"
#include "ui_fridgeexplorer.h"

Fridgeexplorer::Fridgeexplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fridgeexplorer)
{
    ui->setupUi(this);
}

Fridgeexplorer::~Fridgeexplorer()
{
    delete ui;
}
