#include "ShoppingSystem.h"
using namespace std;
// 构造函数，初始化管理员账户
ShoppingSystem::ShoppingSystem(std::string adminUname, std::string adminPwd) : admin(adminUname, adminPwd) {}
// 管理员登录函数
bool ShoppingSystem::adminLogin(std::string uname, std::string pwd) {
	return admin.login(uname, pwd);
}
// 顾客登录函数
bool ShoppingSystem::customerLogin(std::string uname, std::string pwd) {
	if (customers.find(uname) != customers.end()) {
		return customers[uname].login(uname, pwd);
	}
	return false;
}
// 顾客注册函数
void ShoppingSystem::registerCustomer(std::string uname, std::string pwd, std::string email) {
	if (customers.find(uname) == customers.end()) {
		customers[uname] = Customer(uname, pwd, email);
		std::cout << "注册成功！\n" << std::endl;
	} else {
		std::cout << "用户名已存在！\n" << std::endl;
	}
}
// 修改顾客密码函数
void ShoppingSystem::changeCustomerPassword(std::string uname, std::string newPwd, std::string email) {
	if (customers.find(uname) != customers.end() && customers.find(email) != customers.end()) {
		customers[uname].changePassword(newPwd);
		std::cout << "密码修改成功！\n" << std::endl;
	} else {
		std::cout << "用户不存在！\n" << std::endl;
	}
}

// 获取顾客对象函数
Customer& ShoppingSystem::getCustomer(string uname) {
	if (customers.find(uname) != customers.end()) {
		return customers[uname];
	} else {
		throw runtime_error("用户不存在！");
	}
}

	// 添加商品函数
void ShoppingSystem::addProduct(string name, double price, string description, int stock) {
	if (products.find(name) == products.end()) {
		products[name] = Product(name, price, description, stock);
		cout << "商品添加成功！" << endl;
	} else {
		cout << "商品已存在！" << endl;
	}
}

// 删除商品函数
void ShoppingSystem::deleteProduct(string name) {
	if (products.find(name) != products.end()) {
		products.erase(name);
		cout << "商品删除成功！" << endl;
	} else {
		cout << "商品不存在！" << endl;
	}
}

// 修改商品信息函数
void ShoppingSystem::modifyProduct(string name, double price, string description, int stock) {
	if (products.find(name) != products.end()) {
		products[name] = Product(name, price, description, stock);
		cout << "商品信息修改成功！" << endl;
	} else {
		cout << "商品不存在！" << endl;
	}
}

//修改商品库存函数
void ShoppingSystem::modifyStockProduct(string name, int modiStock, bool isAdd){
	if (products.find(name) != products.end()) {
		Product p = products[name];
		if(isAdd){
			p.stock+=modiStock;
		}else{
			p.stock-=modiStock;
		}
	} else {
		cout << "商品不存在！" << endl;
	}
};

// 查询商品信息函数
void ShoppingSystem::queryProduct(string name) {
	if (products.find(name) != products.end()) {
		Product p = products[name];
		cout << "商品名称: " << p.name << endl;
		cout << "商品单价: " << p.price << endl;
		cout << "商品描述: " << p.description << endl;
		cout << "商品库存: " << p.stock << endl;
	} else {
		cout << "商品不存在！" << endl;
	}
}

// 根据关键字推荐商品函数
void ShoppingSystem::recommendProduct(string keyword) {
	bool found = false;
	for (auto &p : products) {
		if (p.second.name.find(keyword) != string::npos) {
			cout << "推荐商品: " << p.second.name << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "没有找到相关商品！" << endl;
	}
}
