#include "kernel.h"
#include "stdin_channel.h"
#include "stdout_channel.h"
#include "FuncProcess.h"
#include "AZinxHandler.h"
#include <iostream>
#include <algorithm>

using namespace std;

/*�ַ�����Ϣ��*/
class my_msg :public message {
public:
	std::string data;
};
/*����3������ַ���*/
class h3 :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual message * internelHandle(message & _input) override
	{
		auto str = dynamic_cast<my_msg&>(_input).data;
		cout << str << endl;
		/*û����һ������---��û����Ҫ��һ�����ڴ��������*/
		return nullptr;
	}
	virtual AZinxHandler * GetNext(message & _next) override
	{
		return nullptr;
	}
};
h3 g_h3;
/*����2��ת��д*/
class h2 :public AZinxHandler
{
	// ͨ�� AZinxHandler �̳�
	virtual message * internelHandle(message & _input) override
	{
		auto str = dynamic_cast<my_msg&>(_input).data;
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		/*���촫�ݸ���һ�����ڵ���Ϣ*/
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
/*����1������ַ����ĳ���*/
class h1 :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual message * internelHandle(message & _input) override
	{
		cout << dynamic_cast<my_msg&>(_input).data.size() << endl;

		/*�����������Ϣ���ص�*/
		return new my_msg(dynamic_cast<my_msg&>(_input));
	}
	virtual AZinxHandler * GetNext(message & _next) override
	{
		/*���ػ���2����ָ��*/
		return &g_h2;
	}
};

h1 g_h1;

int main()
{
	my_msg m;
	m.data = "abc";
	g_h1.Handle(m);

	/*�������ͨ������*/
	stdout_channel my_stdout;
	/*�����׼�������*/
	stdin_channel my_stdin;

	/*���칦�ܴ������*/
	FuncProcess my_func;

	my_stdin.m_process = &my_func;
	my_func.m_output_channel = &my_stdout;
	/*kernel��ʼ��---�����ͨ��----������ѭ��*/
	kernel &my_k =  kernel::GetInstance();
	my_k.init();
	my_k.AddChannel(&my_stdin);
	my_k.AddChannel(&my_stdout);
	my_k.run();
}