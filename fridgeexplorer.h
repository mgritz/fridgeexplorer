#ifndef FRIDGEEXPLORER_H
#define FRIDGEEXPLORER_H

#include <QMainWindow>

#include "producthandling.h"
#include "recipemanager.h"

namespace Ui {
class Fridgeexplorer;
}

class Fridgeexplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fridgeexplorer(QWidget *parent = 0);
    ~Fridgeexplorer();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void showProductHandling_add();
    void showProductHandling_rem();
    void showRecipeManager();
    void selectDatabase();

private:
    Ui::Fridgeexplorer *ui;

    ProductHandling* m_productHandler;
    RecipeManager* m_recipeManager;
};

#endif // FRIDGEEXPLORER_H
