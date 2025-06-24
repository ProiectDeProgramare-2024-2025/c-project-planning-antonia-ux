#include "utils.h"
#include <iostream>


void printUsage2()
{
    std::cout << BOLDWHITE << "Usage:\n"
              << RESET
              << CYAN << "  app_2 view_cart\n"
              << "  app_2 add_to_cart <barcode> <quantity>\n"
              << "  app_2 remove_from_cart <barcode>\n"
              << "  app_2 purchase\n"
              << RESET;
}

void printUsage1()
{
    std::cout << BOLDWHITE << "Usage:\n"
              << RESET
              << CYAN
              << "  ./app_1.exe view_stock_products\n"
              << "  ./app_1.exe add_product <barcode> <name> <quantity> <price>\n"
              << "  ./app_1.exe delete_product <barcode>\n"
              << "  ./app_1.exe modify_product <price|quantity> <barcode> <new_value>\n"
              << "  ./app_1.exe view_orders\n"
              << RESET;
}
