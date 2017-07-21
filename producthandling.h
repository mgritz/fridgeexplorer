#ifndef PRODUCTHANDLING_H
#define PRODUCTHANDLING_H

#include <QMainWindow>

namespace Ui {
class ProductHandling;
}

class ProductHandling : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductHandling(QWidget *parent = 0);
    ~ProductHandling();

    void setMode(bool new_mode);

private slots:
    void searchBarcode();
    void toggleMode();

private:
    Ui::ProductHandling *ui;
    bool m_mode;
};

#endif // PRODUCTHANDLING_H
