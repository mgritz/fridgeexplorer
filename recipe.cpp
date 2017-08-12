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
    qDebug() << "Filling UI for " << m_title;
    ui->line_title->setText(m_title);
    ui->line_location->setText(m_location);
    // TODO fill rest of UI with values
}
