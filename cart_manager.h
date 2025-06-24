#ifndef CART_MANAGER_H
#define CART_MANAGER_H

#include <vector>
#include <string>
#include "comun.h"
#include "stock_manager.h"

class CartManager
{
private:
    std::vector<Product> cart;
    std::string filename;

public:
    CartManager(const std::string &file = "cos_cumparaturi.txt");

    void load();
    void save();
    void add(const std::string &barcode, int qty, StockManager &stock);
    void remove(const std::string &barcode);
    void clear();
    void view(const StockManager &stock) const;
    const std::vector<Product> &getCart() const;
};

#endif // CART_MANAGER_H
