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
    static Recipe* selectedRecipe = nullptr;
    DatabaseInterface db(globalSettings->value("database/path", "").toString(), this);
    if (db.isValid())
    {
        if (selectedRecipe != nullptr){
            clearRecipeDetailsContainer();
            selectedRecipe->deleteLater();
        }

        selectedRecipe = db.loadRecipe(item->text());

        if (selectedRecipe != nullptr){
            fillRecipeDetailsContainer(selectedRecipe);
        }
    }
}


void RecipeManager::clearRecipeDetailsContainer(void)
{
    if (ui->recipe_details_cont->layout() != nullptr)
        delete ui->recipe_details_cont->layout();
}

void RecipeManager::fillRecipeDetailsContainer(Recipe* recipe)
{
    // If the container has no layout add one.
    if (ui->recipe_details_cont->layout() == nullptr){
        QHBoxLayout* newlayout = new QHBoxLayout(ui->recipe_details_cont);
        ui->recipe_details_cont->setLayout(newlayout);
    }
    // Add the acutal container to the layout
    QGroupBox* newcont = new QGroupBox(ui->recipe_details_cont);
    ui->recipe_details_cont->layout()->addWidget(newcont);

    // Initialize the recipe's detailed output there.
    recipe->displayOnWidget(newcont);
}
