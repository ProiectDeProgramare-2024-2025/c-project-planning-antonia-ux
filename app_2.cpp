#include "cart_manager.h"
#include "stock_manager.h"
#include "purchase.h"
#include "utils.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printUsage2();
        return 1;
    }

    StockManager stock;
    CartManager cart;
    std::string cmd = argv[1];

    try
    {
        if (cmd == "view_cart")
        {
            cart.view(stock);
        }
        else if (cmd == "add_to_cart" && argc == 4)
        {
            // Convert quantity argument safely
            int quantity = std::stoi(argv[3]);
            if (quantity <= 0)
            {
                std::cout << RED << "Quantity must be positive.\n"
                          << RESET;
                printUsage2();
                return 1;
            }
            cart.add(argv[2], quantity, stock);
        }
        else if (cmd == "remove_from_cart" && argc == 3)
        {
            cart.remove(argv[2]);
        }
        else if (cmd == "purchase")
        {
            purchase(stock, cart);
        }
        else
        {
            std::cout << RED << "Invalid command.\n"
                      << RESET;
            printUsage2();
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << RED << "Invalid number format for quantity.\n"
                  << RESET;
        printUsage2();
    }
    catch (const std::exception &e)
    {
        std::cout << RED << "Error: " << e.what() << "\n"
                  << RESET;
        printUsage2();
    }
    catch (...)
    {
        std::cout << RED << "Unknown error occurred.\n"
                  << RESET;
        printUsage2();
    }

    return 0;
}
