// NDHttp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "NDHttp.h"
#include "NDHttpBiz.h"
#include "openssl/crypto.h"

#if defined(WIN32)
#define MUTEX_TYPE            HANDLE
#define MUTEX_SETUP(x)        (x) = CreateMutex(NULL, FALSE, NULL)
#define MUTEX_CLEANUP(x)      CloseHandle(x)
#define MUTEX_LOCK(x)         WaitForSingleObject((x), INFINITE)
#define MUTEX_UNLOCK(x)       ReleaseMutex(x)
#define THREAD_ID             GetCurrentThreadId()
#else
#define MUTEX_TYPE            pthread_mutex_t
#define MUTEX_SETUP(x)        pthread_mutex_init(&(x), NULL)
#define MUTEX_CLEANUP(x)      pthread_mutex_destroy(&(x))
#define MUTEX_LOCK(x)         pthread_mutex_lock(&(x))
#define MUTEX_UNLOCK(x)       pthread_mutex_unlock(&(x))
#define THREAD_ID             pthread_self()
#endif
static MUTEX_TYPE *mutex_buf;

static void locking_function(int mode, int n, const char * file, int line)
{
	if (mode & CRYPTO_LOCK)
	{
		MUTEX_LOCK(mutex_buf[n]);
	}
	else
	{
		MUTEX_UNLOCK(mutex_buf[n]);
	}
}

static unsigned long id_function(void)
{
	return ((unsigned long)THREAD_ID);
}

int thread_setup(void)
{
	int i;

	mutex_buf = (HANDLE *)malloc(CRYPTO_num_locks() * sizeof(MUTEX_TYPE));
	if (!mutex_buf)
		return 0;
	for (i = 0; i < CRYPTO_num_locks(); i++)
		MUTEX_SETUP(mutex_buf[i]);
	CRYPTO_set_id_callback(id_function);
	CRYPTO_set_locking_callback(locking_function);
	return 1;
}

int thread_cleanup(void)
{
	int i;
	if (!mutex_buf)
		return 0;
	CRYPTO_set_id_callback(NULL);
	CRYPTO_set_locking_callback(NULL);
	for (i = 0; i < CRYPTO_num_locks(); i++)
		MUTEX_CLEANUP(mutex_buf[i]);
	free(mutex_buf);
	mutex_buf = NULL;
	return 1;
}

using namespace NDHttp;
NDHTTP_EXPORTS_API HttpRequestData * RequestDataInit(CHttpRequestDataModel* pModel)
{
	if (pModel)
		return new CHttpRequestData(pModel);
	else
		return NULL;
}

NDHTTP_EXPORTS_API HttpRequestFile * RequestFileInit(CHttpRequestFileModel* pModel)
{
	if (pModel)
		return new CHttpRequestFile(pModel);
	else
		return NULL;
}

NDHTTP_EXPORTS_API HttpUploadFile * UploadFileInit(CHttpUploadFileModel* pModel)
{
	if (pModel)
		return new CHttpUploadFile(pModel);
	else
		return NULL;
}

NDHTTP_EXPORTS_API void NDHttpInit()
{
	curl_global_init(CURL_GLOBAL_ALL);
	thread_setup();
}

NDHTTP_EXPORTS_API void CleanUpData(HttpRequestData* pRequest)
{
	if (pRequest)
		((CHttpRequestData*)pRequest)->Release();
}

NDHTTP_EXPORTS_API void CleanUpFile(HttpRequestFile* pRequest)
{
	if (pRequest)
		((CHttpRequestFile*)pRequest)->Release();
}

NDHTTP_EXPORTS_API void CleanUpUpload(HttpUploadFile* pRequest)
{
	if (pRequest)
		((CHttpUploadFile*)pRequest)->Release();
}

NDHTTP_EXPORTS_API void RequestFileGetInfo(LPCTSTR pszPath, CHttpRequestFileInfo* pInfo)
{
	if (pInfo && pszPath)
	{
		std::wstring wstrPath = pszPath;
		wstrPath += _T(".nds");
		FILE* fp = NULL;
		errno_t err = _tfopen_s(&fp, wstrPath.c_str(), _T("rb"));
		if (err == 0)
		{
			fread(&pInfo->m_ullLastFileSize, sizeof(ULONGLONG), 1, fp);
			fread(&pInfo->m_ullDownloadTotalSizeInConfig, sizeof(ULONGLONG), 1, fp);
			fclose(fp);
		}
	}
}