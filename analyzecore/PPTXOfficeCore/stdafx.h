// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <codecvt>

using namespace std;

// stl 导出编译警告
#pragma warning(disable:4251) 



// TODO:  在此处引用程序需要的其他头文件
#include "libzippp/libzippp.h"
#include "PPTXOfficeCore.h"

using namespace libzippp;

#pragma comment(lib, "libzippp.lib")
#pragma comment(lib, "zip.lib")
#pragma comment(lib, "zlib.lib")