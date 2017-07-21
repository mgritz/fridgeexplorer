#include "fridgeexplorer.h"
#include "ui_fridgeexplorer.h"

#include <QTime>

Fridgeexplorer::Fridgeexplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fridgeexplorer)
{
    m_productHandler = new ProductHandling(this);

    startTimer(1000);
    ui->setupUi(this);
    QObject::connect(ui->button_add, &QPushButton::clicked, this, &Fridgeexplorer::showProductHandling_add);
    QObject::connect(ui->button_remove, &QPushButton::clicked, this, &Fridgeexplorer::showProductHandling_rem);

}

Fridgeexplorer::~Fridgeexplorer()
{
    delete ui;
}

void Fridgeexplorer::timerEvent(QTimerEvent * event)
{
    ui->label_time->setText(QTime::currentTime().toString("hh:mm:ss t"));
}

void Fridgeexplorer::showProductHandling_add()
{
    m_productHandler->setMode(true);
    m_productHandler->show();
}

void Fridgeexplorer::showProductHandling_rem()
{
    m_productHandler->setMode(false);
    m_productHandler->show();
}
