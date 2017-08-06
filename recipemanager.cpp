#include "recipemanager.h"
#include "ui_recipemanager.h"

RecipeManager::RecipeManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecipeManager)
{
    ui->setupUi(this);
}

RecipeManager::~RecipeManager()
{
    delete ui;
}
