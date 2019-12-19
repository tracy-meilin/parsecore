#pragma once

enum{
	NDHttpStart,
	NDHttpProgress,
	NDHttpComplete,
	NDHttpPause,
	NDHttpCancel
};

typedef bool(__cdecl *pfnDeletegate)(void* pNotify);

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef NDHTTP_EXPORTS
#define NDHTTP_EXPORTS_API __declspec(dllexport)
#else
#define NDHTTP_EXPORTS_API __declspec(dllimport) 
#endif // NDHTTP_EXPORTS


class THttpNotify
{
public:
	THttpNotify() : bType(-1), szData(NULL), nDataSize(0), dwErrorCode(0), ullTotalSize(0), nSpeed(0),
		nElapseTime(0), nRemainTime(0), fPercent(0), pUserData(NULL){}
public:
	BYTE		bType;
	char*		szData;
	int			nDataSize;
	DWORD		dwErrorCode;	// success: 0
	wstring		wstrErrorDescription;
	ULONGLONG	ullTotalSize;
	int			nSpeed;			// in KB
	int			nElapseTime;	// in second
	int			nRemainTime;	// in second
	float		fPercent;
	wstring		wstrFilePath;
	PVOID		pUserData;		// passed parameter
};


class CHttpRequestDataModel
{
public:
	CHttpRequestDataModel() : nPort(80), nTimeout(60), pUserData(NULL){}
public:
	string strHost;//host
	string strUrl;//url
	string strHeader;//header
	string strMethod; //method
	string  strPost;//post content
	int nPort;//port
	UINT nTimeout;//timeout
	PVOID pUserData;//passed parameter
};

class CHttpRequestFileModel
{
public:
	CHttpRequestFileModel() : nPort(80), pfnDeletegate(NULL), pUserData(NULL){}
public:

	string strHost;
	string strUrl;
	string strHeader;
	string strMethod;
	string  strPost;
	wstring wstrLocalFilePath;//local file save path
	int nPort;
	PVOID pfnDeletegate;
	PVOID pUserData;
};

//Interface
//////////////////////////////////////////////////////////////////////////
class IHttpRequestData
{
public:
	virtual DWORD Excute() = 0;
	virtual LPCSTR GetResult() = 0;
	virtual DWORD GetLength() = 0;
	virtual DWORD GetHttpCode() = 0;
	virtual LPCSTR GetHttpHeader() = 0;
	virtual LPCTSTR GetErrorDescritpion() = 0;
};

class IHttpRequestFile
{
public:
	virtual DWORD Excute() = 0;
	virtual void Cancel() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual ULONGLONG GetFileSize() = 0;
	virtual LPCTSTR GetErrorDescription() = 0;
};

class IHttpUploadFile
{
public:
	virtual DWORD Excute() = 0;
	virtual void Cancel() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual LPCSTR GetResult() = 0;
	virtual LPCTSTR GetErrorDescription() = 0;
};

class CHttpRequestFileInfo
{
public:
	CHttpRequestFileInfo() : m_ullLastFileSize(0), m_ullDownloadTotalSizeInConfig(0){}
public:
	ULONGLONG	m_ullLastFileSize;
	ULONGLONG	m_ullDownloadTotalSizeInConfig;
};

class CHttpUploadFileModel
{
public:
	CHttpUploadFileModel() : nPort(80), pfnDeletegate(NULL), pUserData(NULL){}
public:
	string	strHost;
	string	strUrl;
	string	strHeader;
	string	strMethod;
	string  strPost;
	wstring wstrLocalFilePath;
	wstring wstrServerFilePath;//remote server file save path
	wstring wstrFileName;
	int nPort;
    bool    bChunkUpload = true;//д╛хо╥ж©И
	PVOID pfnDeletegate;
	PVOID pUserData;
};

//////////////////////////////////////////////////////////////////////////
typedef class IHttpRequestData	HttpRequestData;
typedef class IHttpRequestFile	HttpRequestFile;
typedef class IHttpUploadFile	HttpUploadFile;

NDHTTP_EXPORTS_API HttpRequestData *RequestDataInit(CHttpRequestDataModel*);
NDHTTP_EXPORTS_API HttpRequestFile *RequestFileInit(CHttpRequestFileModel*);
NDHTTP_EXPORTS_API HttpUploadFile *UploadFileInit(CHttpUploadFileModel*);

NDHTTP_EXPORTS_API void RequestFileGetInfo(LPCTSTR pszPath, CHttpRequestFileInfo*);

NDHTTP_EXPORTS_API void CleanUpData(HttpRequestData*);
NDHTTP_EXPORTS_API void CleanUpFile(HttpRequestFile*);
NDHTTP_EXPORTS_API void CleanUpUpload(HttpUploadFile*);
NDHTTP_EXPORTS_API void NDHttpInit();

#ifdef  __cplusplus
}
#endif