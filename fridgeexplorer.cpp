#include "fridgeexplorer.h"
#include "ui_fridgeexplorer.h"

#include <QTime>

Fridgeexplorer::Fridgeexplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fridgeexplorer)
{
    startTimer(1000);
    ui->setupUi(this);
}

Fridgeexplorer::~Fridgeexplorer()
{
    delete ui;
}

void Fridgeexplorer::timerEvent(QTimerEvent * event)
{
    ui->label_time->setText(QTime::currentTime().toString("hh:mm:ss t"));
}
