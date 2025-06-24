#ifndef STOCK_MANAGER_H
#define STOCK_MANAGER_H

#include <vector>
#include <string>
#include "comun.h" // Defines Product

class StockManager
{
private:
    std::vector<Product> stock;
    std::string filename;

public:
    explicit StockManager(const std::string &file = "stoc.txt");

    void load();
    void save();

    Product *find(const std::string &barcode);
    const Product *find(const std::string &barcode) const;

    void list() const;
    void addProduct(const Product &p);
    bool removeProduct(const std::string &barcode);
};

#endif // STOCK_MANAGER_H
