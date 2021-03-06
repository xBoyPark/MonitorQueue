// LQueueTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include "LQueue.h"
#pragma comment(lib,"..\\lib\\LQueue")

/*
自定义事件处理方法
*/
typedef int(*FADD)(int, int);
int add(int a, int b)
{
	return a + b;
}
typedef void(*Print)(string);
void print(string str)
{
	printf("%s\n", str.c_str());
}
void _qMonitor(void* p)
{
	xQueue xq = *(xQueue*)p;
	while (1)
	{
		vector<xAnwser> xa = xq.monitor();
		if (xa.size() > 0)
		{
			for (int i = 0; i < xa.size(); i++)
			{
				if (xa[i].xID == 1)
				{
					int a = xa[i].xGetFun<FADD>()(2, 3);
					printf("a=%d\n", a);
				}
				else if (xa[i].xID == 2)
				{
					xa[i].xGetFun<Print>()("hello Boy");
				}
				else if (xa[i].xID == 3)
				{
					xa[i].xGetFun<Print>()("hello Girl");
				}
			}
		}
		Sleep(500);
	}
}
int main()
{
	xAnwser e1;
	e1.xSetFun<FADD>(add);
	e1.xID = 1;
	e1.xTimeCur = 0;
	e1.xTimeOut = 10000;
	xAnwser e2;
	e2.xSetFun<Print>(print);
	e2.xID = 2;
	e2.xTimeCur = 0;
	e2.xTimeOut = 30000;
	xAnwser e3;
	e3.xSetFun<Print>(print);
	e3.xID = 3;
	e3.xTimeCur = 0;
	e3.xTimeOut = 5000;
	xQueue xq;
	xq.Start(_qMonitor);
	xq.push(e1);
	xq.push(e2);
	xq.push(e3);
	xq.push(e1);
	xq.push(e2);
	xq.push(e3);
	xq.push(e1);
	xq.push(e2);
	xq.push(e3);
	xq.push(e1);
	xq.push(e2);
	xq.push(e3);
	xq.push(e1);
	xq.push(e2);
	xq.push(e3);
	
	getchar();
    return 0;
}

