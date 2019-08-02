#include "kernel.h"
#include "stdin_channel.h"
#include "stdout_channel.h"
#include "FuncProcess.h"
#include "AZinxHandler.h"
#include <iostream>
#include <algorithm>

using namespace std;

/*字符串消息类*/
class my_msg :public message {
public:
	std::string data;
};
/*环节3：输出字符串*/
class h3 :public AZinxHandler {
	// 通过 AZinxHandler 继承
	virtual message * internelHandle(message & _input) override
	{
		auto str = dynamic_cast<my_msg&>(_input).data;
		cout << str << endl;
		/*没有下一个环节---》没有需要下一个环节处理的数据*/
		return nullptr;
	}
	virtual AZinxHandler * GetNext(message & _next) override
	{
		return nullptr;
	}
};
h3 g_h3;
/*环节2：转大写*/
class h2 :public AZinxHandler
{
	// 通过 AZinxHandler 继承
	virtual message * internelHandle(message & _input) override
	{
		auto str = dynamic_cast<my_msg&>(_input).data;
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		/*构造传递给下一个环节的消息*/
		auto ret = new my_msg();
		ret->data = str;
		return ret;
	}
	virtual AZinxHandler * GetNext(message & _next) override
	{
		return &g_h3;
	}
};
h2 g_h2;
/*环节1：输出字符串的长度*/
class h1 :public AZinxHandler {
	// 通过 AZinxHandler 继承
	virtual message * internelHandle(message & _input) override
	{
		cout << dynamic_cast<my_msg&>(_input).data.size() << endl;

		/*拷贝输入的消息返回掉*/
		return new my_msg(dynamic_cast<my_msg&>(_input));
	}
	virtual AZinxHandler * GetNext(message & _next) override
	{
		/*返回环节2对象指针*/
		return &g_h2;
	}
};

h1 g_h1;

int main()
{
	my_msg m;
	m.data = "abc";
	g_h1.Handle(m);

	/*构造输出通道对象*/
	stdout_channel my_stdout;
	/*构造标准输入对象*/
	stdin_channel my_stdin;

	/*构造功能处理对象*/
	FuncProcess my_func;

	my_stdin.m_process = &my_func;
	my_func.m_output_channel = &my_stdout;
	/*kernel初始化---》添加通道----》进入循环*/
	kernel &my_k =  kernel::GetInstance();
	my_k.init();
	my_k.AddChannel(&my_stdin);
	my_k.AddChannel(&my_stdout);
	my_k.run();
}