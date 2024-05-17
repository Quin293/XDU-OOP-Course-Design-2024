#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
	std::string username;  // 用户名
	std::string password;  // 密码
	
public:
	User(std::string uname, std::string pwd);// 构造函数，初始化用户名和密码
	virtual bool login(std::string uname, std::string pwd) = 0;// 纯虚函数，子类必须实现，用于登录验证
	std::string getUsername();// 获取用户名
};

#endif
