#include "ShoppingCart.h"

void ShoppingCart::addProduct(std::string name, int quantity) {
	if (cart.find(name) != cart.end()) {
		cart[name] += quantity;
	} else {
		cart[name] = quantity;
	}
	std::cout << "商品添加到购物车成功！" << std::endl;
}

void ShoppingCart::viewCart() {
	if (cart.empty()) {
		std::cout << "购物车为空！" << std::endl;
	} else {
		for (auto &item : cart) {
			std::cout << "商品名称: " << item.first << " 数量: " << item.second << std::endl;
		}
	}
}

void ShoppingCart::removeProduct(std::string name) {
	if (cart.find(name) != cart.end()) {
		cart.erase(name);
		std::cout << "商品从购物车中删除成功！" << std::endl;
	} else {
		std::cout << "购物车中没有该商品！" << std::endl;
	}
}

void ShoppingCart::modifyProductQuantity(std::string name, int quantity) {
	if (cart.find(name) != cart.end()) {
		cart[name] = quantity;
		std::cout << "商品数量修改成功！" << std::endl;
	} else {
		std::cout << "购物车中没有该商品！" << std::endl;
	}
}
