#ifndef DBIFACE_H
#define DBIFACE_H

#include <string>

extern class Recipe;
extern class Prodcut;

class DatabaseInterface
{
public:
    DatabaseInterface(std::string database_path);
    ~DatabaseInterface();

    int add_recipe(const Recipe* new_recipe);
    int add_product(const Product* new_product);

private:
    void* m_dbptr; // TODO replace with correct type for SQLite db

};

#endif // DBIFACE_H
