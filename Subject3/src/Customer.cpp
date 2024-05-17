#include "Customer.h"
//默认构造函数
Customer::Customer() : User("", ""), email("") {}
// 构造函数，初始化用户名、密码和电子邮箱
Customer::Customer(std::string uname, std::string pwd, std::string mail) : User(uname, pwd), email(mail) {}
// 实现登录验证函数
bool Customer::login(std::string uname, std::string pwd) {
	return (username == uname && password == pwd);
}
// 修改密码
void Customer::changePassword(std::string newPwd) {
	password = newPwd;
}
// 获取电子邮箱
std::string Customer::getEmail() {
	return email;
}
//获取购物车
ShoppingCart& Customer::getCart() {
	return cart;
}
