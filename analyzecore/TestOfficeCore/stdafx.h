// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <memory>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

#pragma warning(disable:4251) 


// TODO:  在此处引用程序需要的其他头文件

#include "../SimpleStream/SimpleStreamHeaders.h"
#include "../PptFileFormat/PptFileFormat.h"
#include "../PptFileFormat/PptFileFormatHeaders.h"
#include "../OfficeCore/OfficeCoreHeaders.h"
#include "../PPTXOfficeCore/PPTXOfficeCoreHeaders.h"

#ifdef _DEBUG
#pragma comment(lib, "OfficeCore_ud.lib")
#pragma comment(lib, "PPTXOfficeCore_ud.lib")
#pragma comment(lib, "libxml2.lib")
#else
#pragma comment(lib, "OfficeCore_u.lib")
#pragma comment(lib, "PPTXOfficeCore_u.lib")
#pragma comment(lib, "libxml2.lib")
#endif