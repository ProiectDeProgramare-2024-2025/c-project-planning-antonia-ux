#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <string>
#include "comun.h"
#include "stock_manager.h"

class OrderManager
{
public:
    void loadOrders(const std::string &filename = "comenzi.txt");
    void listOrders() const;
    void report(const std::string &barcode, const StockManager &stock) const;

private:
    struct OrderLine
    {
        std::string barcode;
        int quantity;
        double price;
    };

    struct Order
    {
        Date date;
        std::vector<OrderLine> items;
    };

    std::vector<Order> orders;
};

#endif // ORDER_MANAGER_H
