#include "kernel.h"
#include "stdin_channel.h"

int main()
{
	/*构造kernel对象*/
	kernel k;
	/*构造标准输入对象*/
	stdin_channel my_stdin;
	/*kernel初始化---》添加通道----》进入循环*/
	if (true == k.init())
	{
		if (true != k.AddChannel(&my_stdin))
		{
			/*失败则返回*/
			return -1;
		}
		k.run();
		k.fini();
	}
}