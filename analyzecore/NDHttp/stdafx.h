// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>


#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment(lib, "libcurld.lib")
#pragma comment(lib, "zdll_d.lib")
#else
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "zdll.lib")
#endif // DEBUG

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")

#include <tchar.h>
#include <string>
#include <mutex>          // std::mutex, std::unique_lock
#include <vector>
using namespace std;

#ifdef UNICODE
typedef wstring	tstring;
#else
typedef string	tstring;
#endif
// TODO: 在此处引用程序需要的其他头文件
