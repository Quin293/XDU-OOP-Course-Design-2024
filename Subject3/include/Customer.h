#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "ShoppingCart.h"
#include <string>

class Customer : public User {
private:
	std::string email;  // 电子邮箱
	ShoppingCart cart;  //购物车
public:
	Customer();//默认构造函数
	Customer(std::string uname, std::string pwd, std::string mail);// 构造函数，初始化用户名、密码和电子邮箱
	bool login(std::string uname, std::string pwd) override;// 实现登录验证函数
	void changePassword(std::string newPwd);// 修改密码
	std::string getEmail();// 获取电子邮箱
	ShoppingCart& getCart();//获取购物车
};

#endif
