#include "recipe.h"
#include "ui_recipemanager.h"

#include <QDebug>

Recipe::Recipe(const QString& name,
               const QString& location,
               const QSet<serving_options_type> serving,
               const QSet<effort_options_type> effort,
               QObject *parent)
    : QObject(parent)
{
    m_title = name;
    m_location = location;
    m_serving = serving;
    m_effort = effort;
}

bool Recipe::registerIngredient(const QString& ingredient, const int amount)
{
    return false;
}

void Recipe::fillOutUi(Ui::RecipeManager *ui)
{

}
