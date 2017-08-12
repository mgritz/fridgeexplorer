#include "recipemanager.h"
#include "ui_recipemanager.h"

#include "databaseinterface.h"
#include "globalsettings.h"

RecipeManager::RecipeManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecipeManager)
{
    ui->setupUi(this);
    QObject::connect(ui->list_recipes, &QListWidget::itemClicked, this, &RecipeManager::showRecipeDetails);
}

RecipeManager::~RecipeManager()
{
    delete ui;
}

void RecipeManager::show()
{
    DatabaseInterface db(globalSettings->value("database/path", "").toString(), this);
    if (db.isValid())
        ui->list_recipes->addItems(db.listRecipies());

    QMainWindow::show();
}

void RecipeManager::showRecipeDetails(QListWidgetItem* item)
{
    DatabaseInterface db(globalSettings->value("database/path", "").toString(), this);
    if (db.isValid())
    {
        Recipe* selectedRecipe = db.loadRecipe(item->text());
        if (selectedRecipe != nullptr)
        {
            selectedRecipe->fillOutUi(ui);
            delete selectedRecipe;
        }
    }
}
