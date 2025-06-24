#ifndef COMUN_H
#define COMUN_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>

class Date
{
private:
    int day, month, year;

public:
    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    static Date today();

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    friend std::ostream &operator<<(std::ostream &os, const Date &dt);
};

class Product
{
public:
    std::string barcode;
    std::string name;
    int quantity;
    double price;

    Product() : barcode(""), name(""), quantity(0), price(0.0) {}
    Product(const std::string &b, const std::string &n, int q, double p)
        : barcode(b), name(n), quantity(q), price(p) {}

    void print() const;
};

#endif // COMUN_H
