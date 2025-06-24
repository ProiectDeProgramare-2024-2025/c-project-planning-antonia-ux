#include "cart_manager.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

CartManager::CartManager(const std::string &file) : filename(file)
{
    load();
}

void CartManager::load()
{
    cart.clear();
    std::ifstream fin(filename);
    std::string bc;
    int qty;
    while (fin >> bc >> qty)
        cart.emplace_back(bc, "", qty, 0.0);
}

void CartManager::save()
{
    std::ofstream fout(filename);
    for (auto &p : cart)
        fout << p.barcode << " " << p.quantity << "\n";
}

void CartManager::add(const std::string &barcode, int qty, StockManager &stock)
{
    Product *sp = stock.find(barcode);
    if (!sp)
    {
        std::cout << RED << "Product not found.\n"
                  << RESET;
        return;
    }

    for (auto &p : cart)
    {
        if (p.barcode == barcode)
        {
            p.quantity += qty;
            save();
            std::cout << YELLOW << "Quantity updated in cart.\n"
                      << RESET;
            return;
        }
    }

    cart.emplace_back(barcode, sp->name, qty, sp->price);
    save();
    std::cout << GREEN << "Product added to cart.\n"
              << RESET;
}

void CartManager::remove(const std::string &barcode)
{
    auto it = std::remove_if(cart.begin(), cart.end(),
                             [&](const Product &p)
                             { return p.barcode == barcode; });

    if (it != cart.end())
    {
        cart.erase(it, cart.end());
        save();
        std::cout << GREEN << "Removed from cart.\n"
                  << RESET;
    }
    else
    {
        std::cout << RED << "Product not in cart.\n"
                  << RESET;
    }
}

void CartManager::clear()
{
    cart.clear();
    save();
}

void CartManager::view(const StockManager &stock) const
{
    if (cart.empty())
    {
        std::cout << YELLOW << "Cart is empty.\n"
                  << RESET;
        return;
    }

    std::cout << BOLDWHITE << "Cart Contents:\n"
              << RESET;
    for (const auto &p : cart)
    {
        const Product *sp = stock.find(p.barcode);
        std::string name = sp ? sp->name : "unknown";
        double price = sp ? sp->price : 0.0;
        std::cout << CYAN << p.barcode << RESET
                  << " (" << name << ") x" << p.quantity
                  << " @ $" << std::fixed << std::setprecision(2) << price << "\n";
    }
}

const std::vector<Product> &CartManager::getCart() const
{
    return cart;
}
