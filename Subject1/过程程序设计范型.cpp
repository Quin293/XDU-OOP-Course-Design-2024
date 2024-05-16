#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>


using namespace std;

// 初始化变量存储，包括数学常量pi和e
map<string, double> variables = {{"pi", M_PI}, {"e", M_E}};

// 解析数字，支持变量名和实数
double parseNumber(stringstream& ss);

// 解析并计算表达式的函数
double evaluateExpression(const string& expr) {
	stringstream ss(expr);  // 使用stringstream解析表达式
	char op = '+';          // 默认操作符为加号
	double current, result = 0;
	int flag = 0;  // 辅助标志位，用于处理第一个操作数
	
	try {
		while (ss >> ws && !ss.eof()) {
			current = parseNumber(ss);  // 解析数字
			ss >> ws >> op;  // 读取操作符
			if (ss.fail() && !ss.eof()) {
				throw invalid_argument("无效的操作符");
			}
			// 根据操作符执行相应的数学运算
			switch (op) {
				case '+': 
				result += current; 
				break;
				case '-': 
				if(flag == 0){
					result += current;  // 加载第一个操作数
				}else{
					result -= current;  // 后续操作数为减法
				}
				flag++;
				break;
				case '*': 
				if(flag == 0){
					result ++;  // 令结果为1
				}
				result *= current;
				flag++;
				break;
			case '/':
				if (current == 0) throw runtime_error("除数不能为零");
				if(flag == 0){
					result += current;  // 令结果为1
				}else{
					result /= current;  // 后续操作数为除法
				}
				flag++;
				break;
			default:
				throw invalid_argument("未知的操作符");
			}
		}
	} catch (const exception& e) {
		throw;  // 将异常重新抛出，由调用者处理
	}
	return result;
}

// 解析数字，支持变量名和实数
double parseNumber(stringstream& ss) {
	double number;
	if (ss >> number) {
		return number;
	} else {
		ss.clear();
		string var;
		ss >> var;
		if (variables.find(var) == variables.end()) {
			throw invalid_argument("未定义的变量名");
		}
		return variables[var];
	}
}

int main() {
	string input;
	int errorCount = 0;  // 错误计数器
	
	while (true) {
		cout << "请输入表达式或赋值语句 (输入'exit'退出): ";
		getline(cin, input);
		if (input == "exit") break;  // 检测退出命令
		
		try {
			if (input.find('=') != string::npos) {
				stringstream ss(input);
				string var;
				getline(ss, var, '=');  // 解析变量名
				string expr;
				getline(ss, expr);  // 解析表达式
				variables[var] = evaluateExpression(expr);  // 计算并存储结果
				cout << var << " = " << variables[var] << endl;
			} else {
				cout << evaluateExpression(input) << endl;  // 直接计算并输出结果
			}
		} catch (const exception& e) {
			cout << "错误: " << e.what() << endl;  // 输出错误信息
			errorCount++;  // 错误计数增加
		}
	}
	
	cout << "总错误次数: " << errorCount << endl;  // 输出总错误次数
	return 0;
}

