#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
	Admin(std::string uname, std::string pwd);// 构造函数，初始化用户名和密码
	bool login(std::string uname, std::string pwd) override;// 实现登录验证函数
};

#endif
