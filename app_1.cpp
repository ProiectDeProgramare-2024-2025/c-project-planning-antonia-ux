#include <iostream>
#include <string>
#include "stock_manager.h"
#include "order_manager.h"
#include "utils.h"
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printUsage1();
        return 1;
    }

    std::string cmd = argv[1];
    StockManager stock;
    OrderManager orders;

    try
    {
        stock.load();

        if (cmd == "view_stock_products")
        {
            stock.list();
        }
        else if (cmd == "add_product" && argc == 6)
        {
            std::string barcode = argv[2];
            std::string name = argv[3];
            int quantity = std::stoi(argv[4]);
            double price = std::stod(argv[5]);

            stock.addProduct(Product(barcode, name, quantity, price));
            stock.save();
            std::cout << GREEN << "Product added.\n"
                      << RESET;
        }
        else if (cmd == "delete_product" && argc == 3)
        {
            if (stock.removeProduct(argv[2]))
            {
                stock.save();
                std::cout << GREEN << "Product deleted.\n"
                          << RESET;
            }
            else
            {
                std::cout << RED << "Product not found.\n"
                          << RESET;
            }
        }
        else if (cmd == "modify_product" && argc == 5)
        {
            std::string field = argv[2];
            std::string barcode = argv[3];
            std::string valueStr = argv[4];

            Product *prod = stock.find(barcode);
            if (!prod)
            {
                std::cout << RED << "Product not found.\n"
                          << RESET;
                return 1;
            }

            if (field == "price")
            {
                double newPrice = std::stod(valueStr);
                prod->price = newPrice;
                stock.save();
                std::cout << GREEN << "Price updated.\n"
                          << RESET;
            }
            else if (field == "quantity")
            {
                int newQty = std::stoi(valueStr);
                prod->quantity = newQty;
                stock.save();
                std::cout << GREEN << "Quantity updated.\n"
                          << RESET;
            }
            else
            {
                std::cout << RED << "Invalid field. Use 'price' or 'quantity'.\n"
                          << RESET;
            }
        }
        else if (cmd == "view_orders")
        {
            orders.loadOrders();
            orders.listOrders();
        }
        else
        {
            std::cout << RED << "Invalid command or arguments.\n"
                      << RESET;
            printUsage1();
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << "Error: " << e.what() << RESET << "\n";
        return 1;
    }

    return 0;
}