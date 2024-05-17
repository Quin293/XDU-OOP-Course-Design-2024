#include "Product.h"
Product::Product() : name(""), price(0), description(""), stock(0) {};
// Product 类的构造函数实现
Product::Product(std::string n, double p, std::string d, int s) : name(n), price(p), description(d), stock(s) {}
