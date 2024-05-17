#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H


#include <iostream>
#include <unordered_map>
#include <string>


class ShoppingCart {
private:
	std::unordered_map<std::string, int> cart;  // 购物车，存储商品名称和购买数量
	
public:
	void addProduct(std::string name, int quantity);
	void viewCart();
	void removeProduct(std::string name);
	void modifyProductQuantity(std::string name, int quantity);
};

#endif
