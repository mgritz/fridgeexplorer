#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

#include <QMainWindow>

namespace Ui {
class RecipeManager;
}

class RecipeManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecipeManager(QWidget *parent = 0);
    ~RecipeManager();

private:
    Ui::RecipeManager *ui;
};

#endif // RECIPEMANAGER_H
