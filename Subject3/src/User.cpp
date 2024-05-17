#include "User.h"
// 构造函数，初始化用户名和密码
User::User(std::string uname, std::string pwd) : username(uname), password(pwd) {}
// 获取用户名
std::string User::getUsername() {
	return username;
}
