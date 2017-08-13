#include "recipe.h"
#include "ui_recipemanager.h"

#include <QDebug>
#include <QSetIterator>



Recipe::Recipe(const QString& name,
               const QString& location, const int requiredTime,
               const QSet<serving_options_type> serving,
               const QSet<effort_options_type> effort,
               QObject *parent)
    : QObject(parent)
{
    m_title = name;
    m_location = location;
    m_requiredTime = requiredTime;
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

    // update duration buttons
    if (m_requiredTime <= 30)
        ui->radio_is_quick->setChecked(true);
    else if (m_requiredTime <= 60)
        ui->radio_is_normal->setChecked(true);
    else
        ui->radio_is_slow->setChecked(true);

    // update serving checkboxes
    ui->check_is_breakfast->setChecked(false);
    ui->check_is_lunch->setChecked(false);
    ui->check_is_dinner->setChecked(false);
    ui->check_is_mobile->setChecked(false);
    ui->check_is_dessert->setChecked(false);
    QSetIterator<serving_options_type> it_s(m_serving);
    while (it_s.hasNext())
    {
        switch (it_s.next()) {
        case SERVE_DESSERT:
            ui->check_is_dessert->setChecked(true);
            break;
        case SERVE_TAKE:
            ui->check_is_mobile->setChecked(true);
            break;
        case SERVE_DINNER:
            ui->check_is_dinner->setChecked(true);
            break;
        case SERVE_LUNCH:
            ui->check_is_lunch->setChecked(true);
            break;
        case SERVE_BREAKFAST:
            ui->check_is_breakfast->setChecked(true);
            break;
        default:
            qDebug() << "unknown serving type " << it_s.peekPrevious();
        }
    }

    // update effort checkboxes
    ui->check_is_difficult->setChecked(false);
    ui->check_needs_waiting->setChecked(false);
    QSetIterator<effort_options_type> it_e(m_effort);
    while (it_e.hasNext())
    {
        switch (it_e.next()) {
        case EFFORT_DIFFICULT:
            ui->check_is_difficult->setChecked(true);
            break;
        case EFFORT_WAITING:
            ui->check_needs_waiting->setChecked(true);
            break;
        default:
            qDebug() << "unknown effort type " << it_e.peekPrevious();
        }
    }
}

