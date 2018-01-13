#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QSet>
#include <QString>
#include <QMap>

#include "recipemanager.h"
#include "ui_recipewidget.h"

typedef enum{
    SERVE_DESSERT,
    SERVE_TAKE,
    SERVE_DINNER,
    SERVE_LUNCH,
    SERVE_BREAKFAST
} serving_options_type;

typedef enum{
    EFFORT_DIFFICULT,
    EFFORT_WAITING
} effort_options_type;


typedef struct{
    int ingredientID;
    QString name;
    int amount;
    QString measure;
} ingredient_type;

class Recipe : public QObject
{
    Q_OBJECT
public:
    /** defines Recipe from arguments */
    explicit Recipe(const QString& name,
                    const QString& location,
                    const int requiredTime,
                    const QSet<serving_options_type> serving,
                    const QSet<effort_options_type> effort,
                    QObject *parent = nullptr);

    void registerIngredient(const ingredient_type ingredient) { m_ingredients.append(ingredient); }
    QList<ingredient_type> ingredientList(void) const { return m_ingredients; }

    void displayOnWidget(QGroupBox* recipeDetailsWidget);
    void ingredientsSetAvailability(const QMap<int, bool>& ingredientIDtoAvailability);

private:
    int m_id;
    QString m_title;
    QString m_location;
    int m_requiredTime;
    QSet<serving_options_type> m_serving;
    QSet<effort_options_type> m_effort;
    QList<ingredient_type> m_ingredients;
    Ui::RecipeDetails m_rdWidget;
};

#endif // RECIPE_H
