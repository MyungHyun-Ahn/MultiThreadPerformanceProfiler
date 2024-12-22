#pragma once

#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include <stdbool.h>
#include <tchar.h>
#include <wchar.h>
#include <string>
#include <utility>
#include <map>
#include <ctime>
#include <list>
#include <process.h>

#pragma comment(lib, "winmm.lib")

#define SINGLE(type)		private:										\
								type();										\
								~type();									\
								inline static type *m_instPtr = nullptr;	\
							public:											\
								static type *GetInstance()					\
								{											\
									if (m_instPtr == nullptr)				\
									{										\
										m_instPtr = new type();				\
										atexit(Destory);					\
									}										\
																			\
									return m_instPtr;						\
								}											\
																			\
								static void Destory()						\
								{											\
									delete m_instPtr;						\
									m_instPtr = nullptr;					\
								}