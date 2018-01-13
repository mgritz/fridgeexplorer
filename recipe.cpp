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

void Recipe::displayOnWidget(QGroupBox* recipeDetailsWidget)
{
    m_rdWidget.setupUi(recipeDetailsWidget);

    qDebug() << "Filling UI for " << m_title;
    m_rdWidget.line_title->setText(m_title);
    m_rdWidget.line_location->setText(m_location);

    // update duration buttons
    if (m_requiredTime <= 30)
        m_rdWidget.radio_is_quick->setChecked(true);
    else if (m_requiredTime <= 60)
        m_rdWidget.radio_is_normal->setChecked(true);
    else
        m_rdWidget.radio_is_slow->setChecked(true);

    // update serving checkboxes
    m_rdWidget.check_is_breakfast->setChecked(false);
    m_rdWidget.check_is_lunch->setChecked(false);
    m_rdWidget.check_is_dinner->setChecked(false);
    m_rdWidget.check_is_mobile->setChecked(false);
    m_rdWidget.check_is_dessert->setChecked(false);
    QSetIterator<serving_options_type> it_s(m_serving);
    while (it_s.hasNext())
    {
        switch (it_s.next()) {
        case SERVE_DESSERT:
            m_rdWidget.check_is_dessert->setChecked(true);
            break;
        case SERVE_TAKE:
            m_rdWidget.check_is_mobile->setChecked(true);
            break;
        case SERVE_DINNER:
            m_rdWidget.check_is_dinner->setChecked(true);
            break;
        case SERVE_LUNCH:
            m_rdWidget.check_is_lunch->setChecked(true);
            break;
        case SERVE_BREAKFAST:
            m_rdWidget.check_is_breakfast->setChecked(true);
            break;
        default:
            qDebug() << "unknown serving type " << it_s.peekPrevious();
        }
    }

    // update effort checkboxes
    m_rdWidget.check_is_difficult->setChecked(false);
    m_rdWidget.check_needs_waiting->setChecked(false);
    QSetIterator<effort_options_type> it_e(m_effort);
    while (it_e.hasNext())
    {
        switch (it_e.next()) {
        case EFFORT_DIFFICULT:
            m_rdWidget.check_is_difficult->setChecked(true);
            break;
        case EFFORT_WAITING:
            m_rdWidget.check_needs_waiting->setChecked(true);
            break;
        default:
            qDebug() << "unknown effort type " << it_e.peekPrevious();
        }
    }

    // list all ingredients
    m_rdWidget.textEdit_ingredients->clear();
    for (auto it = m_ingredients.begin(); it != m_ingredients.end(); ++it)
    {
        QString line;
        line += QString::number(it->amount).rightJustified(5,' ') + " "
                + it->measure.rightJustified(5,' ') + " " + it->name + "\n";
        m_rdWidget.textEdit_ingredients->insertPlainText(line);
    }
}

void Recipe::ingredientsSetAvailability(const QMap<int, bool>& ingredientIDtoAvailability)
{
    // list all ingredients
    m_rdWidget.textEdit_ingredients->clear();
    for (auto it = m_ingredients.begin(); it != m_ingredients.end(); ++it)
    {
        QString line;

        if (!ingredientIDtoAvailability[it->ingredientID])
            line += "<font color=\"red\">";

        line += QString::number(it->amount).rightJustified(5,' ') + " "
                + it->measure.rightJustified(5,' ') + " " + it->name;

        if (!ingredientIDtoAvailability[it->ingredientID])
            line += "</font>";

        line += "<br>";
        m_rdWidget.textEdit_ingredients->insertPlainText(line);
    }
}

