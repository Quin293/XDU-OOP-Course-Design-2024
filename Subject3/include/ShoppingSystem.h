#ifndef SHOPPINGSYSTEM_H
#define SHOPPINGSYSTEM_H
using namespace std;
#include "Admin.h"
#include "Customer.h"
#include "Product.h"
#include <unordered_map>
#include <iostream>

class ShoppingSystem {
private:
	Admin admin;  // 管理员对象
	std::unordered_map<std::string, Customer> customers;  // 存储顾客信息的哈希表
	unordered_map<string, Product> products;    // 存储商品信息的哈希表
	
public:
	ShoppingSystem(std::string adminUname, std::string adminPwd);// 构造函数，初始化管理员账户
	bool adminLogin(std::string uname, std::string pwd);// 管理员登录函数
	bool customerLogin(std::string uname, std::string pwd);// 顾客登录函数
	Customer& getCustomer(string uname);
	void registerCustomer(std::string uname, std::string pwd, std::string email);// 顾客注册函数
	void changeCustomerPassword(std::string uname, std::string newPwd, std::string email);// 修改顾客密码函数
	void addProduct(string name, double price, string description, int stock);// 添加商品函数
	void deleteProduct(string name);// 删除商品函数
	void modifyProduct(string name, double price, string description, int stock);// 修改商品信息函数
	void modifyStockProduct(string name, int modiStock, bool isAdd);// 修改商品库存函数
	void queryProduct(string name);// 查询商品信息函数
	void recommendProduct(string keyword);// 根据关键字推荐商品函数
};

#endif
