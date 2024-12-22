#include "pch.h"
#include "CProfileManager.h"

int test()
{
	PROFILE_BEGIN(1, "Test1");
	Sleep(0);
	return  1;
}

int test2()
{
	PROFILE_BEGIN(1, "Test2");
	Sleep(0);
	return 1;
}

unsigned ThreadProc(void *pParam)
{
	for (int i = 0; i < 50000; ++i)
	// while (1)
	{
		PROFILE_BEGIN(1, "Test3");
		// Sleep(1);
		test();
		test();
		test();
		test();
		test();
		test();
		test2();
		test2();
	}
	return 0;
}

unsigned ThreadProc1(void *pParam)
{
	for (int i = 0; i < 50000; ++i)
	// while (1)
	{
		PROFILE_BEGIN(1, "Test4");
		test();
		test();
		test();
		test();
		test();
		test();
		test2();
		test2();
	}
	return 1;
}

int main()
{
	g_ProfileMgr = CProfileManager::GetInstance();
	HANDLE hThreadArr[3];
	for (int i = 0; i < 3; ++i)
	{
		hThreadArr[i] = (HANDLE)_beginthreadex(nullptr, 0, ThreadProc, nullptr, CREATE_SUSPENDED, nullptr);
		if (i == 2)
		{
			hThreadArr[i] = (HANDLE)_beginthreadex(nullptr, 0, ThreadProc1, nullptr, CREATE_SUSPENDED, nullptr);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		ResumeThread(hThreadArr[i]);
	}

	// while (1)
	// {
	// 	Sleep(1000);
	// 	if (GetAsyncKeyState(VK_RETURN) & 0x01)
	// 	{
	// 		PROFILER::Reset();
	// 	}
	// 
	// 	if (GetAsyncKeyState(VK_BACK) & 0x01)
	// 	{
	// 		PROFILER::ProfileDataOutText("Profile.txt");
	// 	}
	// }

	WaitForMultipleObjects(3, hThreadArr, TRUE, INFINITE);
	// PROFILER::ProfileDataOutText("profile.txt");
}