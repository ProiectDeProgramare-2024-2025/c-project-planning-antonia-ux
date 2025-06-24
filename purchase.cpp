#include "purchase.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void purchase(StockManager &stock, CartManager &cart)
{
    // Check stock availability for each product in the cart
    for (const auto &p : cart.getCart())
    {
        Product *sp = stock.find(p.barcode);
        if (!sp || sp->quantity < p.quantity)
        {
            std::cout << RED << "Not enough stock for: " << p.barcode << "\n"
                      << RESET;
            return;
        }
    }

    // Deduct quantities from stock
    for (const auto &p : cart.getCart())
    {
        Product *sp = stock.find(p.barcode);
        sp->quantity -= p.quantity;
    }

    stock.save();

    // Append order to file
    std::ofstream fout("comenzi.txt", std::ios::app);
    if (!fout)
    {
        std::cout << RED << "Failed to open orders file.\n"
                  << RESET;
        return;
    }

    Date d = Date::today();
    fout << d.getDay() << " " << d.getMonth() << " " << d.getYear() << "\n";

    for (const auto &p : cart.getCart())
        fout << p.barcode << " " << p.quantity << " "
             << std::fixed << std::setprecision(2) << p.price << "\n";

    fout << "#\n";

    cart.clear();

    std::cout << GREEN << "Purchase complete.\n"
              << RESET;
}
