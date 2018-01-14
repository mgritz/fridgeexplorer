#include "recipeeditor.h"
#include "ui_recipeeditor.h"

#include <QDebug>
#include <QComboBox>
#include <QStringList>

#include "databaseinterface.h"
#include "globalsettings.h"

RecipeEditor::RecipeEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeEditor)
{
    ui->setupUi(this);
    QObject::connect(ui->ingredient_table, &QTableWidget::doubleClicked,
                     this, &RecipeEditor::addIngredientLineToUi);
}

RecipeEditor::~RecipeEditor()
{
    delete ui;
}

void RecipeEditor::addIngredientLineToUi(void)
{
    int newRow = ui->ingredient_table->rowCount();
    ui->ingredient_table->insertRow(newRow);

    QComboBox* ingredient = new QComboBox(ui->ingredient_table);
    ingredient->setEditable(true);
    ui->ingredient_table->setCellWidget(newRow, 0, ingredient);
    ingredient->addItem("...NEW INGREDIENT");

    DatabaseInterface db(globalSettings->value("database/path", "").toString(), this);
    if (!db.isValid()){
        qWarning() << "Recipe database invalid!";
        return;
    }
    QStringList ingredientsFromDb = db.listIngredients();
    ingredientsFromDb.sort();

    ingredient->addItems(ingredientsFromDb);
}
