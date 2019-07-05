#include <iostream>
#include "zinxkernel.h"
#include "stdin_channel.h"
#include "FIFO_channel.h"
#include "ProcessFunc.h"
#include "ZinxHandler.h"
#include <algorithm>

using namespace std;

class testMsg :public ZinxMsg
{
public:
	string data;
};

class output_next_letter :public ZinxHandler
{
	// ͨ�� ZinxHandler �̳�
	virtual ZinxMsg * internel_handle(ZinxMsg * _inputMsg) override
	{
		auto pmsg = dynamic_cast<testMsg *>(_inputMsg);
		printf("%c\n", pmsg->data[0] + 1);
		return nullptr;
	}
	virtual ZinxHandler * GetNext(ZinxMsg * _next_input) override
	{
		return nullptr;
	}
} step3;

class output_ascii :public ZinxHandler
{
	// ͨ�� ZinxHandler �̳�
	virtual ZinxMsg * internel_handle(ZinxMsg * _inputMsg) override
	{
		auto pmsg = dynamic_cast<testMsg *>(_inputMsg);
		printf("%d\n", pmsg->data[0]);

		//ԭ��������һ������
		testMsg *pret = new testMsg();
		pret->data = pmsg->data;
		return pret;
	}
	virtual ZinxHandler * GetNext(ZinxMsg * _next_input) override
	{
		return &step3;
	}
} step2;

class trancUpper :public ZinxHandler
{
	// ͨ�� ZinxHandler �̳�
	virtual ZinxMsg * internel_handle(ZinxMsg * _inputMsg) override
	{
		auto pmsg = dynamic_cast<testMsg *>(_inputMsg);
		string output("a");
		transform(pmsg->data.begin(), pmsg->data.end(), output.begin(), ::toupper);
		cout << output << endl;

		//new �µ���Ϣ���󷵻�
		testMsg *pret = new testMsg();
		pret->data = output;
		return pret;
	}
	virtual ZinxHandler * GetNext(ZinxMsg * _next_input) override
	{
		return &step2;
	}
} step1;





void test_chain()
{
	string tmp;
	cin >> tmp;
	testMsg init_msg;
	init_msg.data = tmp;
	step1.handle(&init_msg);
}


int main()
{
 test_chain();

	stdin_channel in_channel;
	stdou_channel out_channel;
	ProcessFunc pf;

	pf.m_out = &out_channel;
	in_channel.m_proc = &pf;

	zinxkernel &kernel = zinxkernel::GetInstance();
	kernel.AddChannel(&in_channel);
	kernel.AddChannel(&out_channel);

	FIFO_channel fifo_input("input", true);
	FIFO_channel fifo_output("output", false);
	fifo_input.m_out = &fifo_output;
	kernel.AddChannel(&fifo_input);
	kernel.AddChannel(&fifo_output);

	kernel.run();
}