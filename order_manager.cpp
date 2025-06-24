#include "order_manager.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void OrderManager::loadOrders(const std::string &filename)
{
    orders.clear();
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cerr << RED << "Failed to open orders file: " << filename << RESET << "\n";
        return;
    }

    int day, month, year;
    while (fin >> day >> month >> year)
    {
        Order o;
        o.date = Date(day, month, year);

        std::string barcode;
        int qty;
        double price;

        while (fin >> barcode && barcode != "#")
        {
            fin >> qty >> price;
            o.items.push_back({barcode, qty, price});
        }

        orders.push_back(o);
    }
}

void OrderManager::listOrders() const
{
    for (const auto &o : orders)
    {
        std::cout << BOLDWHITE << "Date: " << o.date << RESET << "\n";
        for (const auto &line : o.items)
        {
            std::cout << "  " << CYAN << line.barcode << RESET
                      << " x" << line.quantity
                      << " @ $" << std::fixed << std::setprecision(2) << line.price << "\n";
        }
        std::cout << "\n";
    }
}

void OrderManager::report(const std::string &barcode, const StockManager &stock) const
{
    const Product *prod = stock.find(barcode);
    std::string name = prod ? prod->name : "unknown";
    double totalQty = 0;
    double totalSum = 0;

    for (const auto &o : orders)
    {
        for (const auto &line : o.items)
        {
            if (line.barcode == barcode)
            {
                totalQty += line.quantity;
                totalSum += line.quantity * line.price;
            }
        }
    }

    std::cout << BOLDWHITE << "Report for barcode: " << barcode << " (" << name << ")\n"
              << RESET;
    std::cout << "  Total quantity sold: " << YELLOW << totalQty << RESET << "\n";
    std::cout << "  Total revenue: $" << GREEN << std::fixed << std::setprecision(2) << totalSum << RESET << "\n";
}
