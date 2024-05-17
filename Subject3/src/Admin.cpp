#include "Admin.h"
// 构造函数，初始化用户名和密码
Admin::Admin(std::string uname, std::string pwd) : User(uname, pwd) {}
// 实现登录验证函数
bool Admin::login(std::string uname, std::string pwd) {
	return (username == uname && password == pwd);
}
