#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

// 存储数学常量的map
map<string, double> variables = {{"pi", M_PI}, {"e", M_E}};

// 计算器类
class Calculator {
public:
	// 计算表达式的方法
	double evaluateExpression(const string& expr) {
		stringstream ss(expr);  // 使用stringstream解析表达式
		char op = '+';          // 默认操作符为加号
		double current, result = 0;
		int flag = 0;  // 辅助标志位，用于处理第一个操作数
		try {
			// 循环解析表达式中的每个操作数和操作符
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
						result += current;  // 第一个操作数为负数时，相当于减法
					}else{
						result -= current;  // 后续操作数为减法
					}
					flag++;
					break;
					case '*': 
					if(flag == 0){
						result ++;  // 第一个操作数为1时，相当于乘法
					}
					result *= current;
					flag++;
					break;
				case '/':
					if (current == 0) throw runtime_error("除数不能为零");
					if(flag == 0){
						result += current;  // 第一个操作数为被除数时，相当于除法
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
	
private:
	// 解析数字，支持变量名和实数
	double parseNumber(stringstream& ss) {
		double number;
		// 尝试解析实数
		if (ss >> number) {
			return number;
		} else { // 如果解析失败，尝试解析变量名
			ss.clear();
			string var;
			ss >> var;
			// 检查变量名是否存在
			if (variables.find(var) == variables.end()) {
				throw invalid_argument("未定义的变量名");
			}
			return variables[var];
		}
	}
};

int main() {
	Calculator calc;  // 创建计算器对象
	string input;  // 存储用户输入的表达式或赋值语句
	int errorCount = 0;  // 错误计数器
	
	// 循环接收用户输入，直到输入退出命令为止
	while (true) {
		cout << "请输入表达式或赋值语句 (输入'exit'退出): ";
		getline(cin, input);  // 获取用户输入
		if (input == "exit") break;  // 检测退出命令
		
		try {
			// 判断用户输入的是表达式还是赋值语句
			if (input.find('=') != string::npos) {
				stringstream ss(input);
				string var;
				getline(ss, var, '=');  // 解析变量名
				string expr;
				getline(ss, expr);  // 解析表达式
				// 计算并存储结果
				variables[var] = calc.evaluateExpression(expr);
				// 输出变量名和结果
				cout << var << " = " << variables[var] << endl;
			} else {
				// 直接计算并输出表达式结果
				cout << calc.evaluateExpression(input) << endl;
			}
		} catch (const exception& e) {
			// 输出错误信息
			cout << "错误: " << e.what() << endl;
			errorCount++;  // 错误计数增加
		}
	}
	
	// 输出总错误次数
	cout << "总错误次数: " << errorCount << endl;
	return 0;
}

