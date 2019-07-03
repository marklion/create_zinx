#include <iostream>
#include "zinxkernel.h"
#include "stdin_channel.h"

using namespace std;

int main()
{
	stdin_channel in_channel;
	stdou_channel out_channel;
	in_channel.m_out = &out_channel;

	zinxkernel &kernel = zinxkernel::GetInstance();
	kernel.AddChannel(&in_channel);
	kernel.AddChannel(&out_channel);
	kernel.run();
}