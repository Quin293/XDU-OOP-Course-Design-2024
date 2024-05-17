#include <iostream>
#include "ShoppingSystem.h" // 包含购物系统的头文件
using namespace std;

int main() {
	// 创建购物系统对象，并初始化管理员账户
	ShoppingSystem system("admin", "123456");
	string usr, pwd, mail;
	int flag = 0;
	bool loggedInCustomer = false; // 添加一个标志来表示是否已登录
	bool loggedInAdmin = false;
	
	string productName, productDescrption;
	double productPrice;
	int productStock, productQuantity;
	
	
	while(true){
		
		cout << "=================登录界面=================" << endl;
		cout << "输入0 退出购物系统\n输入1 管理员登录\n输入2 用户注册\n输入3 用户登录\n输入4 用户修改密码\n" << endl;
		
		cin >> flag;
		
		if(flag == 0){
			cout << "成功退出购物系统！" << endl;
			break;
		}
		
		switch (flag) {
		case 1:
			// 管理员登录
			cout << "请输入管理员用户名:" << endl;
			cin >> usr;
			cout << "请输入管理员密码:" << endl;
			cin >> pwd;
			if (system.adminLogin(usr, pwd)) {
				cout << "管理员登录成功！\n" << endl;
				loggedInAdmin = true;
			} else {
				cout << "管理员登录失败！请重新登录！\n" << endl;
			}
			break;
		case 2:
			// 顾客注册
			cout << "请输入用户名:" << endl;
			cin >> usr;
			cout << "请输入密码:" << endl;
			cin >> pwd;
			cout << "请输入邮箱:" << endl;
			cin >> mail;
			
			system.registerCustomer(usr, pwd, mail);
			
			break;
		case 3:
			// 顾客登录
			cout << "请输入用户名:" << endl;
			cin >> usr;
			cout << "请输入密码:" << endl;
			cin >> pwd;
			
			if (system.customerLogin(usr, pwd)) {
				cout << "顾客登录成功！\n" << endl;
				loggedInCustomer = true;
			} else {
				cout << "顾客登录失败！请重新登录！\n" << endl;
			}
			break;
		case 4:
			// 修改顾客密码
			cout << "请输入用户名:" << endl;
			cin >> usr;
			cout << "请输入新密码:" << endl;
			cin >> pwd;
			cout << "请输入邮箱:" << endl;
			cin >> mail;
			
			system.changeCustomerPassword(usr, pwd, mail);
			break;
		default:
			cout << "非法输入！\n" << endl;
			break;
		}
		
		if(loggedInAdmin){
			cout << "=================管理员界面=================" << endl;
			while(true){
				cout << "输入0 登出管理员界面\n输入1 添加新的商品\n输入2 删除指定商品\n输入3 修改指定商品\n" << endl;
				cin >> flag;
				
				if(flag == 0){
					cout << "成功登出管理员界面！\n" << endl;
					loggedInAdmin = false;
					break;
				}
				
				switch (flag) {
				case 1:
					cout << "请输入要添加的商品名:" << endl;
					cin >> productName;
					cout << "请输入商品单价:" << endl;
					cin >> productPrice;
					cout << "请输入商品描述:" << endl;
					cin >> productDescrption;
					cout << "请输入商品库存:" << endl;
					cin >> productStock;
					system.addProduct(productName, productPrice, productDescrption, productStock);
					break;
				case 2:
					cout << "请输入要删除的商品名:" << endl;
					cin >> productName;
					system.deleteProduct(productName);
					break;
				case 3:
					cout << "请输入要修改的商品名:" << endl;
					cin >> productName;
					cout << "请输入商品单价:" << endl;
					cin >> productPrice;
					cout << "请输入商品描述:" << endl;
					cin >> productDescrption;
					cout << "请输入商品库存:" << endl;
					cin >> productStock;
					system.modifyProduct(productName, productPrice, productDescrption, productStock);
					break;
				default:
					cout << "非法输入！" << endl;
					break;
				}
			}
			
		}else if(loggedInCustomer){
			cout << "=================用户界面=================" << endl;
			Customer& customer = system.getCustomer(usr);//获取用户对象
			while(true){
				cout << "输入0 登出用户界面\n输入1 查看购物车\n输入2 添加商品到购物车\n输入3 查询商品信息\n输入4 删除购物车商品\n输入5 修改购物车指定商品数量" << endl;
				cin >> flag;
				
				if(flag == 0){
					cout << "成功登出用户界面！\n" << endl;
					loggedInCustomer = false;
					break;
				}
				
				switch (flag) {
				case 1:
					customer.getCart().viewCart();
					break;
				case 2:
					cout << "请输入要添加到购物车的商品名:" << endl;
					cin >> productName;
					cout << "请输入商品数量:" << endl;
					cin >> productQuantity;
					customer.getCart().addProduct("Apple", productQuantity);
					break;
				case 3:
					cout << "请输入要查询的商品名:" << endl;
					cin >> productName;
					system.queryProduct(productName);
					break;
				case 4:
					cout << "请输入要删除的商品名:" << endl;
					cin >> productName;
					customer.getCart().removeProduct(productName);
					break;
				case 5:
					cout << "请输入要修改的商品名:" << endl;
					cin >> productName;
					cout << "请输入要修改的商品数量:" << endl;
					cin >> productQuantity;
					customer.getCart().modifyProductQuantity(productName, productQuantity);
					break;
				default:
					cout << "非法输入！" << endl;
					break;
				}
			}
		}
		
	}
	

	
	return 0;
}
