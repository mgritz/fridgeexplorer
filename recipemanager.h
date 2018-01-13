#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

#include <QMainWindow>
#include <QListWidgetItem>

class Recipe;

namespace Ui {
class RecipeManager;
}

class RecipeManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecipeManager(QWidget *parent = 0);
    ~RecipeManager();

    void show();

public slots:
    void showRecipeDetails(QListWidgetItem* item);

private:
    void clearRecipeDetailsContainer(void);
    void fillRecipeDetailsContainer(Recipe *recipe);
    Ui::RecipeManager *ui;
};

#endif // RECIPEMANAGER_H
