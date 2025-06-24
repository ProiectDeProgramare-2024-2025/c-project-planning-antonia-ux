#include "comun.h"

// Static method to get current date
Date Date::today()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return Date(ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);
}

// Overload output operator for Date
std::ostream &operator<<(std::ostream &os, const Date &dt)
{
    os << dt.day << "/" << dt.month << "/" << dt.year;
    return os;
}

// Print Product details
void Product::print() const
{
    std::cout << barcode << " " << name
              << " Quantity: " << quantity
              << " Price: $" << std::fixed << std::setprecision(2) << price << "\n";
}
