#include "recipemanager.h"
#include "ui_recipemanager.h"

#include "databaseinterface.h"
#include "globalsettings.h"

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

void RecipeManager::show()
{
    DatabaseInterface db(globalSettings->value("database/path", "").toString(), this);
    if (db.isValid())
        ui->list_recipes->addItems(db.listRecipies());

    QMainWindow::show();
}
