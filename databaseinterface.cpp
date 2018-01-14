#include "databaseinterface.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

QMap<serving_options_type, int> DatabaseInterface::servigToBits = populateServing();
QMap<effort_options_type, int> DatabaseInterface::effortToBits = populateEffort();

DatabaseInterface::DatabaseInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    qDebug() << "Opening database " << path;

    // TODO check and create lockfile?

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
        m_db_valid = false;
    }
    else
    {
        qDebug() << "Database: connection ok";
         m_db_valid = true;
    }
}

DatabaseInterface::~DatabaseInterface()
{
    if (m_db.isOpen())
        m_db.close();
        // TODO release lockfile?
}

QStringList DatabaseInterface::listRecipies(void)
{
    qDebug() << "Prompting all recipes...";

    QSqlQuery query("SELECT title FROM recipes;");

    QStringList retval;
    query.first();
    do {
        QString title = query.value(0).toString();
        qDebug() << title;
        retval.append(title);
    } while (query.next());

    return retval;
}

QMap<QString, int> DatabaseInterface::listFridgeContents(void)
{

}

QStringList DatabaseInterface::listIngredients(void)
{
    qDebug() << "Prompting all ingredients...";

    QSqlQuery query("SELECT class FROM ingredients;");

    QStringList retval;
    query.first();
    do {
        QString title = query.value(0).toString();
        qDebug() << title;
        retval.append(title);
    } while (query.next());

    return retval;
}

Recipe* DatabaseInterface::loadRecipe(QString name)
{
    qDebug() << "Querying for recipe " << name;

    QSqlQuery query;
    query.prepare("SELECT * FROM recipes WHERE title = (:title);");
    query.bindValue(":title", name);

    if(!query.exec()) {
        qDebug() << "Failed to query database for recipe named" << name;
        return nullptr;
    }

    // load first matching entry.
    query.first();
    QString location = query.value(2).toString();
    QSet<serving_options_type> serving = decodeServing(query.value(3).toInt());
    int time = query.value(4).toInt();
    QSet<effort_options_type> effort = decodeEffort(query.value(5).toInt());

    Recipe* recipe = new Recipe(name, location, time, serving, effort, this->parent());

    // load ingredients
    //    first, load ingredient usages
    int recipeID = query.value(0).toInt();

    query.prepare("SELECT * FROM ingredient_usages WHERE recipe_using = (:recipeID);");
    query.bindValue(":recipeID", recipeID);

    if(!query.exec())
    {
        qDebug() << "Failed to query database for ingredient_usages by " << name << ", id is " << recipeID;
        return nullptr;
    }

    QMap<int, int> ingredientIDtoAmount;
    query.first();
    do
    {
        ingredientIDtoAmount.insert(query.value(1).toInt(), query.value(3).toInt());
    } while(query.next());

    //    second, explore what ingredients are acutally used

    qDebug() << "This recipe uses: ";
    for (auto it = ingredientIDtoAmount.begin(); it != ingredientIDtoAmount.end(); ++it)
    {
        query.prepare("SELECT * FROM ingredients WHERE id = (:ingredientID);");
        query.bindValue(":ingredientID", it.key());
        if(!query.exec())
            qDebug() << "Failed to query database for ingredient with id " << it.key();
        else
        {
            query.first();
            ingredient_type new_ingredient = {
                .ingredientID = it.key(),
                .name = query.value(1).toString(),
                .amount = it.value(),
                .measure = query.value(2).toString()
            };
            qDebug() << "     " << new_ingredient.amount << new_ingredient.measure << " of " << new_ingredient.name;
            // store that information in the recipe.
            recipe->registerIngredient(new_ingredient);
        }
    }

    return recipe;
}

bool DatabaseInterface::storeRecipe(Recipe* newRecipe)
{
    int targetRecipeKey = 0;
    // Find ID of recipe. Don't reuse Recipe::m_id b/c it might have been modified since reading.
    QSqlQuery query;
    query.prepare("SELECT 1 FROM recipes WHERE title = (:title);");
    query.bindValue(":title", newRecipe->getTitle());
    if(!query.exec()){
        qDebug() << "Failed to query database for recipe named" << newRecipe->getTitle();
        return false;
    }

    if(query.first()){
        targetRecipeKey = query.value(0).toInt();
    } else {
        // entry not yet present. Obtain free ID to add.
        query.prepare("SELECT MAX(id) FROM recipes;");
        if(!query.exec()){
            qDebug() << "Failed to query db for max recipe id";
            return false;
        }
        query.first();
        targetRecipeKey = query.value(0).toInt() + 1;
    }

    // First, check and update ingredient usages.
    foreach (ingredient_type ingr, newRecipe->ingredientList()){
        int ingrUsageToUpdate = 0;

        query.prepare("SELECT 1 FROM ingredient_usages"
                      " WHERE ingredient = (:ingredientID)"
                      " AND recipe_using = (:recipeID);");
        query.bindValue(":ingredientID", ingr.ingredientID);
        query.bindValue(":recipeID", targetRecipeKey);

        if(!query.exec()){
            qWarning() << "Failed to query ingredient_usages for entries"
                        " connecting " << newRecipe->getTitle() << " to "
                     << ingr.name;
            return false;
        }

        if(query.first()){
             ingrUsageToUpdate = query.value(0).toInt();
        } else {
            // entry not yet present. Obtain free ID to add.
            query.prepare("SELECT MAX(id) FROM ingredient_usages;");
            if(!query.exec()){
                qWarning() << "Failed to query db for max ingredient_usages id";
                return false;
            }
            query.first();
            ingrUsageToUpdate = query.value(0).toInt() + 1;
        }

        query.prepare("REPLACE INTO ingredient_usages"
                      " (id, ingredient, recipe_using, amount)"
                      " VALUES (:id, :ingredient, :recipe, :amount);");
        query.bindValue(":id", ingrUsageToUpdate);
        query.bindValue(":ingredient", ingr.ingredientID);
        query.bindValue(":recipe", targetRecipeKey);
        query.bindValue(":amount", ingr.amount);
        if(!query.exec()){
            qWarning() << "Failed to update ingredient_usage "
                        " connecting " << newRecipe->getTitle() << " to "
                     << ingr.name;
            return false;
        }
        qDebug() << "Updated ingredient_usage connecting "
                 << newRecipe->getTitle() << " to " << ingr.name;
    }

    // Lastly insert or replace recipe
    query.prepare("REPLACE INTO recipes"
                  " (id, title, location, serves_for, time, effort)"
                  " VALUES (:id, :title, :location, :serves_for, :time, :effort);");
    query.bindValue(":id", targetRecipeKey);
    query.bindValue(":title", newRecipe->getTitle());
    query.bindValue(":location", newRecipe->getLocation());
    query.bindValue(":serves_for", encodeServing(newRecipe->getServingOptions()));
    query.bindValue(":time", newRecipe->getRequiredTime());
    query.bindValue(":effort", encodeEffort(newRecipe->getEffort()));
    if(!query.exec()){
        qWarning() << "Updating recipe id " << targetRecipeKey << " "
                   << newRecipe->getTitle() << " failed";
        return false;
    }

    qDebug() << "Updated recipe id " << targetRecipeKey << " "
             << newRecipe->getTitle();

    return true;
}

QSet<serving_options_type> DatabaseInterface::decodeServing(int servingField)
{
    QSet<serving_options_type> retval;
    for (auto it = servigToBits.begin(); it != servigToBits.end(); ++it)
        if(it.value() & servingField)
            retval.insert(it.key());

    return retval;
}

int DatabaseInterface::encodeServing(QSet<serving_options_type> servigOptions)
{
    int retval = 0;
    for (auto it = servigOptions.begin(); it != servigOptions.end(); ++it)
        retval |= servigToBits[*it];

    return retval;
}

QSet<effort_options_type> DatabaseInterface::decodeEffort(int effortField)
{
    QSet<effort_options_type> retval;
    for (auto it = effortToBits.begin(); it != effortToBits.end(); ++it)
        if(it.value() & effortField)
            retval.insert(it.key());
    return retval;
}

int DatabaseInterface::encodeEffort(QSet<effort_options_type> effortOptions)
{
    int retval = 0;
    for (auto it = effortOptions.begin(); it != effortOptions.end(); ++it)
        retval |= effortToBits[*it];

    return retval;
}

QMap<serving_options_type, int> DatabaseInterface::populateServing()
{
    QMap<serving_options_type, int> retval;
    retval.insert(SERVE_BREAKFAST, 0x01);
    retval.insert(SERVE_LUNCH, 0x02);
    retval.insert(SERVE_DINNER, 0x04);
    retval.insert(SERVE_TAKE, 0x08);
    retval.insert(SERVE_DESSERT, 0x10);
    return retval;
}

QMap<effort_options_type, int> DatabaseInterface::populateEffort()
{
    QMap<effort_options_type, int> retval;
    retval.insert(EFFORT_WAITING, 0x01);
    retval.insert(EFFORT_DIFFICULT, 0x02);
    return retval;
}

