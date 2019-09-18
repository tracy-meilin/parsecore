// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <memory>
#include <vector>

#include <string>
#include <tchar.h>


using namespace std;

// stl 导出编译警告
#pragma warning(disable:4251) 


// TODO:  在此处引用程序需要的其他头文件
#include "OfficeCore.h"
#include "../SimpleStream/SimpleStreamHeaders.h"
#include "../PptFileFormat/PptFileFormat.h"
#include "../PptFileFormat/PptFileFormatHeaders.h"



#ifdef _DEBUG
#pragma comment(lib, "PptFileFormat_ud.lib")
#else
#pragma comment(lib, "PptFileFormat_u.lib")
#endif