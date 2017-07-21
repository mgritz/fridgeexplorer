#ifndef PRODUCTHANDLING_H
#define PRODUCTHANDLING_H

#include <QMainWindow>

namespace Ui {
class ProductHandling;
}

class ProductHandling : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductHandling(QWidget *parent = 0);
    ~ProductHandling();

private:
    Ui::ProductHandling *ui;
};

#endif // PRODUCTHANDLING_H
