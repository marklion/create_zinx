#include "kernel.h"
#include "stdin_channel.h"
#include "stdout_channel.h"

int main()
{
	/*�������ͨ������*/
	stdout_channel my_stdout;
	/*�����׼�������*/
	stdin_channel my_stdin;
	my_stdin.m_output_channel = &my_stdout;
	/*kernel��ʼ��---�����ͨ��----������ѭ��*/
	kernel &my_k =  kernel::GetInstance();
	my_k.init();
	my_k.AddChannel(&my_stdin);
	my_k.AddChannel(&my_stdout);
	my_k.run();
}