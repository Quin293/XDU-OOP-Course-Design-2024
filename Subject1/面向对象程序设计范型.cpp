#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

// 初始化变量存储，包括数学常量pi和e
map<string, double> variables = {{"pi", M_PI}, {"e", M_E}};

// 表达式求值器的抽象基类
class ExpressionEvaluator {
public:
	// 纯虚函数，用于求值表达式
	virtual double evaluate(const string& expr) = 0;
};

// 简单求值器，继承自表达式求值器
class SimpleEvaluator : public ExpressionEvaluator {
public:
	// 实现求值函数
	double evaluate(const string& expr) override {
		stringstream ss(expr);  // 使用stringstream解析表达式
		char op = '+';          // 默认操作符为加号
		double current, result = 0;
		int flag = 0; // 标志用于处理第一个数和第一个运算符
		try {
			while (ss >> ws && !ss.eof()) { // 从输入流中读取数据直到流末尾
				current = parseNumber(ss);  // 解析数字
				ss >> ws >> op;  // 读取操作符
				if (ss.fail() && !ss.eof()) { // 检查读取操作符是否成功
					throw invalid_argument("无效的操作符"); // 抛出无效操作符异常
				}
				// 根据操作符执行相应的数学运算
				switch (op) {
					case '+': 
					result += current; 
					break;
					case '-': 
					if(flag == 0){
						result += current;
					}else{
						result -= current;
					}
					flag++;
					break;
					case '*': 
					if(flag == 0){
						result ++;
					}
					result *= current;
					flag++;
					break;
				case '/':
					if (current == 0) throw runtime_error("除数不能为零"); // 检查除数是否为零
					if(flag == 0){
						result += current;
					}else{
						result /= current;
					}
					flag++;
					break;
				default:
					throw invalid_argument("未知的操作符"); // 抛出未知操作符异常
				}
			}
		} catch (const exception& e) {
			throw;  // 将异常重新抛出，由调用者处理
		}
		return result; // 返回计算结果
	}
	
private:
	// 解析数字，支持变量名和实数
	double parseNumber(stringstream& ss) {
		double number;
		if (ss >> number) { // 尝试从流中读取一个数字
			return number; // 返回读取的数字
		} else {
			ss.clear(); // 清除流状态
			string var;
			ss >> var; // 从流中读取一个字符串
			if (variables.find(var) == variables.end()) { // 检查变量是否存在
				throw invalid_argument("未定义的变量名"); // 抛出未定义变量异常
			}
			return variables[var]; // 返回变量的值
		}
	}
};

int main() {
	SimpleEvaluator evaluator; // 创建简单求值器对象
	string input; // 用于存储用户输入的表达式或赋值语句
	int errorCount = 0;  // 错误计数器
	
	while (true) { // 无限循环，直到用户输入"exit"
		cout << "请输入表达式或赋值语句 (输入'exit'退出): ";
		getline(cin, input); // 从标准输入读取一行数据
		if (input == "exit") break;  // 检测退出命令
		
		try {
			if (input.find('=') != string::npos) { // 检查输入是否为赋值语句
				stringstream ss(input); // 创建字符串流对象
				string var;
				getline(ss, var, '=');  // 解析变量名
				string expr;
				getline(ss, expr);  // 解析表达式
				variables[var] = evaluator.evaluate(expr);  // 计算并存储结果
				cout << var << " = " << variables[var] << endl; // 输出赋值结果
			} else {
				cout << evaluator.evaluate(input) << endl;  // 直接计算并输出结果
			}
		} catch (const exception& e) {
			cout << "错误: " << e.what() << endl;  // 输出错误信息
			errorCount++;  // 错误计数增加
		}
	}
	
	cout << "总错误次数: " << errorCount << endl;  // 输出总错误次数
	return 0; // 返回程序执行结果
}

