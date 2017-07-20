#ifndef FRIDGEEXPLORER_H
#define FRIDGEEXPLORER_H

#include <QMainWindow>

namespace Ui {
class Fridgeexplorer;
}

class Fridgeexplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fridgeexplorer(QWidget *parent = 0);
    ~Fridgeexplorer();

private:
    Ui::Fridgeexplorer *ui;
};

#endif // FRIDGEEXPLORER_H
