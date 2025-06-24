#include "stock_manager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "utils.h"

StockManager::StockManager(const std::string &file) : filename(file)
{
    load();
}

void StockManager::load()
{
    stock.clear();
    std::ifstream fin(filename);
    if (!fin)
        return;

    int n;
    fin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::string bc, nm;
        int q;
        double pr;
        fin >> bc >> nm >> q >> pr;
        stock.emplace_back(bc, nm, q, pr);
    }
}

void StockManager::save()
{
    std::ofstream fout(filename);
    fout << stock.size() << "\n";
    for (const auto &p : stock)
        fout << p.barcode << " " << p.name << " " << p.quantity << " "
             << std::fixed << std::setprecision(2) << p.price << "\n";
}

Product *StockManager::find(const std::string &barcode)
{
    for (auto &p : stock)
        if (p.barcode == barcode)
            return &p;
    return nullptr;
}

const Product *StockManager::find(const std::string &barcode) const
{
    for (const auto &p : stock)
        if (p.barcode == barcode)
            return &p;
    return nullptr;
}

void StockManager::list() const
{
    if (stock.empty())
    {
        std::cout << YELLOW << "Stock is empty.\n"
                  << RESET;
        return;
    }

    std::cout << BOLDWHITE << "Available Products in Stock:\n"
              << RESET;
    for (const auto &p : stock)
    {
        p.print();
    }
}

void StockManager::addProduct(const Product &p)
{
    Product *existing = find(p.barcode);
    if (existing)
    {
        existing->quantity += p.quantity; // You might want to decide if quantity is replaced or added
        existing->price = p.price;        // Update price to the new one
    }
    else
    {
        stock.push_back(p);
    }
    save();
    std::cout << GREEN << "Product added/updated successfully.\n"
              << RESET;
}

bool StockManager::removeProduct(const std::string &barcode)
{
    auto it = std::remove_if(stock.begin(), stock.end(),
                             [&](const Product &p)
                             { return p.barcode == barcode; });

    if (it != stock.end())
    {
        stock.erase(it, stock.end());
        save();
        std::cout << GREEN << "Product removed successfully.\n"
                  << RESET;
        return true;
    }
    std::cout << RED << "Product not found.\n"
              << RESET;
    return false;
}
