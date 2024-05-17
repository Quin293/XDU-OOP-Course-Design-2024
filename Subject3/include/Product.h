#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
	std::string name;       // 商品名称
	double price;           // 商品单价
	std::string description; // 商品描述
	int stock;              // 商品库存
	Product();
	// 构造函数
	Product(std::string n, double p, std::string d, int s);
	
};

#endif
