#ifndef RECIPEEDITOR_H
#define RECIPEEDITOR_H

#include <QDialog>

namespace Ui {
class RecipeEditor;
}

class RecipeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeEditor(QWidget *parent = 0);
    ~RecipeEditor();

private slots:
    void addIngredientLineToUi(void);

private:
    Ui::RecipeEditor *ui;
};

#endif // RECIPEEDITOR_H
