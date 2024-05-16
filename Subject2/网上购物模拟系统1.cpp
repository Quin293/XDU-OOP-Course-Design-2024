#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
  使用C++实现一个简单的网上购物模拟系统
  要求：
  1. 实现登录功能
  管理员必须登录系统之后才能操作后台数据;顾客未登录系统时,可以查询商品信息。
  若要购买商品,必须登录系统。
  管理员和顾客通过账户名和密码登录系统。
  管理员的账户和密码通过提前预设的方式指定。
  顾客在首次登录系统时,需要先进行注册,注册成功后设置账户和密码(注册时需要提
  供的信息由你自行设计)。
  
  2. 管理顾客的信息
  (1)保存顾客注册的信息和账户信息;
  (2)顾客可以修改自己的密码。
 */

// 基类 User，包含用户名和密码
class User {
protected:
	string username;  // 用户名
	string password;  // 密码
public:
	// 构造函数，初始化用户名和密码
	User(string uname, string pwd) : username(uname), password(pwd) {}
	
	// 纯虚函数，子类必须实现，用于登录验证
	virtual bool login(string uname, string pwd) = 0;
	
	// 获取用户名
	string getUsername() { return username; }
};

// 管理员类 Admin，继承自 User
class Admin : public User {
public:

	// 构造函数，初始化用户名和密码
	Admin(string uname, string pwd) : User(uname, pwd) {}
	
	// 实现登录验证函数
	bool login(string uname, string pwd) override {
		return (username == uname && password == pwd);
	}
};

// 顾客类 Customer，继承自 User
class Customer : public User {
private:
	string email;  // 电子邮箱
public:
	//默认构造函数
	Customer() : User("", ""), email("") {}
	// 构造函数，初始化用户名、密码和电子邮箱
	Customer(string uname, string pwd, string mail) : User(uname, pwd), email(mail) {}
	
	// 实现登录验证函数
	bool login(string uname, string pwd) override {
		return (username == uname && password == pwd);
	}
	
	// 修改密码
	void changePassword(string newPwd) {
		password = newPwd;
	}
	
	// 获取电子邮箱
	string getEmail() { return email; }
};

class ShoppingSystem {
private:
	Admin admin;  // 管理员对象
	unordered_map<string, Customer> customers;  // 存储顾客信息的哈希表
public:
	// 构造函数，初始化管理员账户
	ShoppingSystem(string adminUname, string adminPwd) : admin(adminUname, adminPwd) {}
	
	// 管理员登录函数
	bool adminLogin(string uname, string pwd) {
		return admin.login(uname, pwd);
	}
	
	// 顾客登录函数
	bool customerLogin(string uname, string pwd) {
		if (customers.find(uname) != customers.end()) {
			return customers[uname].login(uname, pwd);
		}
		return false;
	}
	
	// 顾客注册函数
	void registerCustomer(string uname, string pwd, string email) {
		if (customers.find(uname) == customers.end()) {
			customers[uname] = Customer(uname, pwd, email);
			cout << "注册成功！" << endl;
		} else {
			cout << "用户名已存在！" << endl;
		}
	}
	
	// 修改顾客密码函数
	void changeCustomerPassword(string uname, string newPwd, string email) {
		if (customers.find(uname) != customers.end() && customers.find(email) != customers.end()) {
			customers[uname].changePassword(newPwd);
			cout << "密码修改成功！" << endl;
		} else {
			cout << "用户不存在！" << endl;
		}
	}
};

int main() {
	// 创建购物系统对象，并初始化管理员账户
	ShoppingSystem system("admin", "123456");
	string usr, pwd, mail;
	int flag = 0;
	bool loggedIn = false; // 添加一个标志来表示是否已登录
	
	while(true){
		
		if(loggedIn){ // 如果已登录，则跳出循环
			break;
		}
		
		cout << "输入0 退出程序\n输入1 管理员登录\n输入2 用户注册\n输入3 用户登录\n输入4 用户修改密码\n" << endl;
		
		cin >> flag;
		
		if(flag == 0){
			cout << "成功退出程序\n" << endl;
			break;
		}
		
		switch (flag) {
		case 1:
			// 管理员登录
			cout << "请输入管理员用户名:\n" << endl;
			cin >> usr;
			cout << "请输入管理员密码:\n" << endl;
			cin >> pwd;
			if (system.adminLogin(usr, pwd)) {
				cout << "管理员登录成功！" << endl;
				loggedIn = true;
			} else {
				cout << "管理员登录失败！请重新登录！" << endl;
			}
			break;
		case 2:
			// 顾客注册
			cout << "请输入用户名:\n" << endl;
			cin >> usr;
			cout << "请输入密码:\n" << endl;
			cin >> pwd;
			cout << "请输入邮箱:\n" << endl;
			cin >> mail;
			
			system.registerCustomer(usr, pwd, mail);
			
			break;
		case 3:
			// 顾客登录
			cout << "请输入用户名:\n" << endl;
			cin >> usr;
			cout << "请输入密码:\n" << endl;
			cin >> pwd;
			
			if (system.customerLogin(usr, pwd)) {
				cout << "顾客登录成功！" << endl;
				loggedIn = true;
			} else {
				cout << "顾客登录失败！请重新登录！" << endl;
			}
			break;
		case 4:
			// 修改顾客密码
			cout << "请输入用户名:\n" << endl;
			cin >> usr;
			cout << "请输入新密码:\n" << endl;
			cin >> pwd;
			cout << "请输入邮箱:\n" << endl;
			cin >> mail;
			
			system.changeCustomerPassword(usr, pwd, mail);
			break;
		default:
			cout << "非法输入！" << endl;
			break;
		}
	}

	return 0;
}
