#include "producthandling.h"
#include "ui_producthandling.h"

ProductHandling::ProductHandling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductHandling)
{
    m_mode = true;
    ui->setupUi(this);
    QObject::connect(ui->line_barcode, &QLineEdit::returnPressed, ui->button_barcodereturn, &QPushButton::click);
    QObject::connect(ui->button_barcodereturn, &QPushButton::clicked, this, &ProductHandling::searchBarcode);
    QObject::connect(ui->button_modeswitch, &QPushButton::clicked, this, &ProductHandling::toggleMode);
}

ProductHandling::~ProductHandling()
{
    delete ui;
}

void ProductHandling::searchBarcode()
{
    ui->label->setText(ui->line_barcode->text());
}

void ProductHandling::setMode(bool new_mode)
{
    m_mode = new_mode;
    if(m_mode)
    {
        ui->button_modeswitch->setText("remove items");
        ui->label_mode->setText("adding items to storage");
    } else {
        ui->button_modeswitch->setText("add items");
        ui->label_mode->setText("removing items from storage");
    }
}

void ProductHandling::toggleMode()
{
    if(m_mode)
        setMode(false);
    else
        setMode(true);
}

void ProductHandling::show()
{
    // TODO This is not working yet.
    // I want to set focus to the line edit every time I open this window.
    // Also, it is not clearing the line edit - reckon this is not the method to be called by the show signal...
    ui->line_barcode->clear();
    QMainWindow::show();
    ui->line_barcode->setFocus();
}
