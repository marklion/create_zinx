#include "kernel.h"
#include "stdin_channel.h"

int main()
{
	/*����kernel����*/
	kernel k;
	/*�����׼�������*/
	stdin_channel my_stdin;
	/*kernel��ʼ��---�����ͨ��----������ѭ��*/
	if (true == k.init())
	{
		if (true != k.AddChannel(&my_stdin))
		{
			/*ʧ���򷵻�*/
			return -1;
		}
		k.run();
		k.fini();
	}
}