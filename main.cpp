#include "kernel.h"
#include "stdin_channel.h"
#include "stdout_channel.h"

int main()
{
	/*构造输出通道对象*/
	stdout_channel my_stdout;
	/*构造标准输入对象*/
	stdin_channel my_stdin;
	my_stdin.m_output_channel = &my_stdout;
	/*kernel初始化---》添加通道----》进入循环*/
	kernel &my_k =  kernel::GetInstance();
	my_k.init();
	my_k.AddChannel(&my_stdin);
	my_k.AddChannel(&my_stdout);
	my_k.run();
}