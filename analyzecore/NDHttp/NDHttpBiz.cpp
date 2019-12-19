#include "stdafx.h"
#include "NDHttpBiz.h"
#include "util.h"
#include "rapidjson/rapidjson_wrapper.hpp"
#include <algorithm>  

using namespace rapidjson;
using namespace rjwrapper;

namespace NDHttp
{
	//////////////////////////////////////////////////////////////////////////
	CHttpRequestData::CHttpRequestData(CHttpRequestDataModel* pModel)
	{
		SetHost(pModel->strHost);
		SetUrl(pModel->strUrl);
		SetHeader(pModel->strHeader);
		SetMethod(pModel->strMethod);
		SetPost(pModel->strPost);
		SetPort(pModel->nPort);
		SetTimeout(pModel->nTimeout);

		m_nBufferSize = 0x400;
		m_pBuffer = (char*)malloc(m_nBufferSize + 1);
		m_pBuffer[0] = 0x0;
		m_nRecvBufferSize = 0;
	}

	CHttpRequestData::~CHttpRequestData()
	{
		if (m_pBuffer)
		{
			free(m_pBuffer);
			m_pBuffer = NULL;
		}
	}

	DWORD CHttpRequestData::Excute()
	{
		if (GetHost().length() == 0 || GetUrl().length() == 0)
			return -1;

		m_strHttpHeader = "";
		CURL *pCurl = curl_easy_init();

		curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1);

		CURLcode curlRet = CURL_LAST;
		string strUrl;

		if (GetHost().find("https://") != string::npos)
		{
			m_nPort = 443;
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);
		}
		else if (GetHost().find("http://") != string::npos)
		{
			m_nPort = 80;
		}
		else if (m_nPort == 443)
		{
			strUrl = "https://";
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);
		}
		else
		{
			strUrl = "http://";
		}
		strUrl += GetHost();
		strUrl += GetUrl();

		CUtil Util;
		curl_easy_setopt(pCurl, CURLOPT_URL, Util.UrlEncode(strUrl).c_str()); //设置下载的URI
#ifdef _DEBUG
		curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 1);
#endif

		curl_easy_setopt(pCurl, CURLOPT_PORT, m_nPort);
		curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST, GetMethod().c_str());
		if (!m_strPost.empty())
			curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, m_strPost.c_str()); //post参数 

		curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, GetTimeout());
		curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, GetTimeout());
		curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(pCurl, CURLOPT_ACCEPT_ENCODING, "");

		struct curl_slist *headerlist = NULL;
		string header = GetHeader();
		headerlist = curl_slist_append(headerlist, header.c_str());
		headerlist = curl_slist_append(headerlist, "Accept-Encoding: gzip, deflate");
		if (header.find("Accept: ") == header.npos)
			headerlist = curl_slist_append(headerlist, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
		curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &CHttpRequestData::GetHttpCallBack);
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, this);

		curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, &CHttpRequestData::GetHttpHeaderCallBack);
		curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, this);
		//////////////////////////////////////////////////////////////////////////

		curlRet = curl_easy_perform(pCurl);
		curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &m_dwHttpCode);

		if (curlRet != CURLE_OK)
		{
			SetErrorDescritpion(Util.Utf82Str(curl_easy_strerror(curlRet)).c_str());
		}
		else
		{
			if (m_pBuffer)
			{
				m_pBuffer[m_nRecvBufferSize] = 0;
			}
		}
		curl_slist_free_all(headerlist);
		curl_easy_cleanup(pCurl);

		return curlRet;
	}

	size_t CHttpRequestData::GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpRequestData* pTask = (CHttpRequestData*)userp;

		return pTask->ProgrossCallBack(ptr, size, nmemb, userp);
	}

	size_t CHttpRequestData::ProgrossCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		int nSize = m_nRecvBufferSize;
		nSize += size * nmemb;
		if (nSize >= m_nBufferSize)
		{
			m_nBufferSize = m_nBufferSize * 2 > nSize ? m_nBufferSize * 2 : nSize;
			m_pBuffer = (char*)realloc(m_pBuffer, m_nBufferSize + 1);
		}

		memcpy_s(m_pBuffer + m_nRecvBufferSize, m_nBufferSize - m_nRecvBufferSize, ptr, size * nmemb);

		m_nRecvBufferSize += size * nmemb;

		return size* nmemb;
	}

	size_t CHttpRequestData::GetHttpHeaderCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpRequestData* pTask = (CHttpRequestData*)userp;
		pTask->m_strHttpHeader += (char *)ptr;
		return size*nmemb;
	}

	LPCSTR CHttpRequestData::GetResult()
	{
		return m_pBuffer;
	}

	DWORD CHttpRequestData::GetHttpCode()
	{
		return m_dwHttpCode;
	}

	void CHttpRequestData::SetErrorDescritpion(wstring strError)
	{
		m_strErrorDescription = strError;
	}

	void CHttpRequestData::Release()
	{
		delete this;
	}

	LPCSTR CHttpRequestData::GetHttpHeader()
	{
		return m_strHttpHeader.c_str();
	}

	//////////////////////////////////////////////////////////////////////////
	CHttpRequestFile::CHttpRequestFile(CHttpRequestFileModel* pModel)
	{
		SetHost(pModel->strHost);
		SetUrl(pModel->strUrl);
		SetHeader(pModel->strHeader);
		SetMethod(pModel->strMethod);
		SetPost(pModel->strPost);
		SetPort(pModel->nPort);
		SetLocalFilePath(pModel->wstrLocalFilePath);
		SetStatus(CHttpRequestFile::NORAML);
		SetDelegate(pModel->pfnDeletegate);
		SetUserData(pModel->pUserData);

		m_hNdfFile = NULL;
		m_hNdsFile = NULL;
		m_pNDHttpBuilderBiz = NULL;
		m_dwLastOnProgressTime = 0;
		m_fSpeed = 0;
	}

	CHttpRequestFile::~CHttpRequestFile()
	{
	
	}

	DWORD CHttpRequestFile::Excute()
	{
		CURL *pCurl = curl_easy_init();
		CURLM *multi_handle = curl_multi_init();

		curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1);

		CURLcode curlRet = CURL_LAST;
		string strUrl;

		strUrl = "http://";
		strUrl += GetHost();
		strUrl += GetUrl();

		CUtil Util;
		curl_easy_setopt(pCurl, CURLOPT_FAILONERROR, true);
		curl_easy_setopt(pCurl, CURLOPT_URL, Util.UrlEncode(strUrl).c_str()); //设置下载的URI
#ifdef _DEBUG
		curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 1);
#endif

		curl_easy_setopt(pCurl, CURLOPT_PORT, m_nPort);
		curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST, GetMethod().c_str());

		if (!m_strPost.empty())
			curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, m_strPost.c_str()); //post参数 

		curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1L);

		SetConfPath();
		ULONGLONG ulFileSize = GetLastFileSizePos();
		curl_easy_setopt(pCurl, CURLOPT_RESUME_FROM, ulFileSize);

		struct curl_slist *headerlist = NULL;
		string header = GetHeader();
		headerlist = curl_slist_append(headerlist, header.c_str());
		if (header.find("Accept: ") == header.npos)
			headerlist = curl_slist_append(headerlist, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");

		curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &CHttpRequestFile::GetHttpCallBack);
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, this);

		curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, &CHttpRequestFile::GetHttpHeaderCallBack);
		curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, this);

		//////////////////////////////////////////////////////////////////////////
		curl_multi_add_handle(multi_handle, pCurl);
		BOOL bDownload;
		curl_multi_perform(multi_handle, &bDownload);

		int nReTry = 0;
		do {
			struct timeval timeout;
			int rc; /* select() return code */
			CURLMcode mc; /* curl_multi_fdset() return code */

			fd_set fdread;
			fd_set fdwrite;
			fd_set fdexcep;
			int maxfd = -1;

			long curl_timeo = -1;

			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdexcep);

			/* set a suitable timeout to play around with */
			timeout.tv_sec = 1;
			timeout.tv_usec = 0;

			curl_multi_timeout(multi_handle, &curl_timeo);
			if (curl_timeo >= 0) {
				timeout.tv_sec = curl_timeo / 1000;
				if (timeout.tv_sec > 1)
					timeout.tv_sec = 1;
				else
					timeout.tv_usec = (curl_timeo % 1000) * 1000;
			}

			/* get file descriptors from the transfers */
			mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

			if (mc != CURLM_OK)
			{
				//fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
				break;
			}
			/* On success the value of maxfd is guaranteed to be >= -1. We call
			select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
			no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
			to sleep 100ms, which is the minimum suggested value in the
			curl_multi_fdset() doc. */

			if (maxfd == -1) {
#ifdef _WIN32
				Sleep(100);
				rc = 0;
#else
				/* Portable sleep for platforms other than Windows. */
				struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
				rc = select(0, NULL, NULL, NULL, &wait);
#endif
			}
			else {
				/* Note that on some platforms 'timeout' may be modified by select().
				If you need access to the original value save a copy beforehand. */
				rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
			}

			switch (rc) {
			case SOCKET_ERROR:
				/* select error */
				break;
			case 0:
				/* timeout 60s*/
			{
					  curl_multi_perform(multi_handle, &bDownload);
					  nReTry++;
			}
				break;
			default:
				/* readable/writable sockets */
			{
					   nReTry = 0;
					   curl_multi_perform(multi_handle, &bDownload);
			}
				break;
			}

			if (nReTry >= 60)
			{
				SetErrorDescription(_T("请求超时"));
				break;
			}
		} while (bDownload && (GetStatus() != CHttpRequestFile::PAUSE && GetStatus() != CHttpRequestFile::STOP));

		int msgq = 0;
		struct CURLMsg *m = curl_multi_info_read(multi_handle, &msgq);
		if (m && (m->msg == CURLMSG_DONE)) {
			curlRet = m->data.result;
		}

		if (!CompleteCallBack(curlRet))
			curlRet = CURLE_WRITE_ERROR;

		THttpNotify CompleteNotify;
		CompleteNotify.dwErrorCode = curlRet;
		CompleteNotify.ullTotalSize = m_ullFileSize;
		switch (GetStatus())
		{
		case  CHttpRequestFile::PAUSE:
			CompleteNotify.bType = NDHttpPause;
			break;
		case  CHttpRequestFile::STOP:
			CompleteNotify.bType = NDHttpCancel;
			break;
		default:
			CompleteNotify.bType = NDHttpComplete;
			break;
		}
		
		CompleteNotify.wstrFilePath = GetLocalFilePath().c_str();
		CompleteNotify.pUserData = GetUserData();
		CompleteNotify.nSpeed = (int)m_fSpeed;
		if (curlRet != CURLE_OK)
		{
			if (m_strErrorDescription.empty())
			{
				SetErrorDescription(Util.Utf82Str(curl_easy_strerror(curlRet)));
			}

			CompleteNotify.wstrErrorDescription = m_strErrorDescription;
		}

		if (GetDelegate())
			((pfnDeletegate)GetDelegate())(&CompleteNotify);

		curl_multi_cleanup(multi_handle);

		/* always cleanup */
		curl_easy_cleanup(pCurl);

		/* free slist */
		curl_slist_free_all(headerlist);

		return curlRet;
	}

	void CHttpRequestFile::Cancel()
	{
		std::unique_lock<std::mutex> lck(mtx);
		SetStatus(CHttpRequestFile::STOP);
		ReleaseFile();
	}

	void CHttpRequestFile::Pause()
	{
		std::unique_lock<std::mutex> lck(mtx);
		SetStatus(CHttpRequestFile::PAUSE);
		ReleaseFile();
	}

	void CHttpRequestFile::Resume()
	{
		SetStatus(CHttpRequestFile::NORAML);
	}

	size_t CHttpRequestFile::GetHttpHeaderCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpRequestFile* pTask = (CHttpRequestFile*)userp;
		return pTask->StartCallBack(ptr, size, nmemb, userp);
	}

	size_t CHttpRequestFile::StartCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpRequestFile* pTask = (CHttpRequestFile*)userp;

		int		nPos = 0;
		ULONGLONG	ullFileSize = 0;
		DWORD	dwErrorCode = 0;

		nPos = sscanf_s((const char *)ptr, "Content-Length: %I64d\n", &ullFileSize);
		if (nPos)
		{
			do
			{
				std::unique_lock<std::mutex> lck(mtx);
				if (m_dwHttpCode == 301 || m_dwHttpCode == 302) //Moved Permanently or Found
					return size* nmemb;

				if (m_dwHttpCode == 416) // Requested Range Not Satisfiable
				{
					SetErrorDescription(_T("HttpCode 416:Requested Range Not Satisfiable"));
					DeleteFile(m_strNdfFile.c_str());
					DeleteFile(m_strNdsFile.c_str());
					return 0;
				}

				m_ullDownloadTotalSize = ullFileSize;
				m_ullFileSize = m_ullLastFileSize + ullFileSize;

				//判断服务端文件是否修改
				if (m_ullDownloadTotalSizeInConfig != 0 && m_ullDownloadTotalSizeInConfig != m_ullFileSize)
				{
					SetErrorDescription(_T("服务器文件大小修改，重新下载完整文件"));
					DeleteFile(m_strNdfFile.c_str());
					DeleteFile(m_strNdsFile.c_str());
					return 0;
				}
				//

				if (m_strNdfFile.length() > MAX_PATH)
				{
					SetErrorDescription(_T("文件路径过长"));
					return 0;
				}
				//Do Start
				m_hNdfFile = CreateFile(m_strNdfFile.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (m_hNdfFile == INVALID_HANDLE_VALUE)
				{
					SetErrorDescription(_T("文件创建失败"));
					return 0;
				}
				//

				m_hNdsFile = CreateFile(m_strNdsFile.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (m_hNdsFile == INVALID_HANDLE_VALUE)
				{
					SetErrorDescription(_T("文件创建失败"));
					CloseHandle(m_hNdfFile);
					return 0;
				}

				//设置文件总大小
				DWORD dwBytesWritten = 0;
				SetFilePointer(m_hNdsFile, 0, 0, FILE_BEGIN);
				SetFilePointer(m_hNdsFile, sizeof(ULONGLONG), 0, FILE_CURRENT);
				WriteFile(m_hNdsFile, &m_ullFileSize, sizeof(ULONGLONG), &dwBytesWritten, NULL);

				LARGE_INTEGER  liCurrentPosition;
				liCurrentPosition.QuadPart = m_ullLastFileSize;
				SetFilePointerEx(m_hNdfFile, liCurrentPosition, 0, FILE_BEGIN);

				THttpNotify StartNotify;
				StartNotify.bType = NDHttpStart;
				StartNotify.pUserData = GetUserData();
				StartNotify.ullTotalSize = m_ullFileSize;
				if (GetDelegate())
				{
					if (!((pfnDeletegate)GetDelegate())(&StartNotify))
					{
						SetErrorDescription(_T("请求停止"));
						return 0;
					}
				}

			} while (false);

			m_dwStartTime = GetTickCount();
		//	m_dwLastOnProgressTime = m_dwStartTime;
		}

		DWORD dwMajorVersion, dwMinorVersion, dwHttpCode;;
		nPos = sscanf_s((const char *)ptr, "HTTP/%d.%d %d", &dwMajorVersion, &dwMinorVersion, &dwHttpCode);
		if (nPos)
		{
			m_dwHttpCode = dwHttpCode;
		}

		return size* nmemb;
	}

	size_t CHttpRequestFile::GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpRequestFile* pTask = (CHttpRequestFile*)userp;

		if (pTask->GetStatus() == CHttpRequestFile::PAUSE)
		{
			pTask->SetErrorDescription(_T("请求暂停"));
			return 0;
		}

		if (pTask->GetStatus() == CHttpRequestFile::STOP)
		{
			pTask->SetErrorDescription(_T("请求停止"));
			return 0;
		}

		return pTask->ProgrossCallBack(ptr, size, nmemb, userp);
	}

	size_t CHttpRequestFile::ProgrossCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpRequestFile* pTask = (CHttpRequestFile*)userp;
		//Do Progress
		if (m_hNdfFile && m_hNdfFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				std::unique_lock<std::mutex> lck(mtx);
				DWORD dwBytesWritten = 0;
				WriteFile(m_hNdfFile, ptr, size * nmemb, &dwBytesWritten, NULL);
				if (dwBytesWritten != size * nmemb)
				{
					SetErrorDescription(_T("文件写入异常"));
					return 0;
				}
				//
				m_ullCurDownloadSize += size * nmemb;

				if (m_hNdsFile != NULL)
				{
					SetFilePointer(m_hNdsFile, 0, 0, FILE_BEGIN);
					WriteFile(m_hNdsFile, &m_ullCurDownloadSize, sizeof(ULONGLONG), &dwBytesWritten, NULL);
				}
			} while (false);


			if (m_dwLastOnProgressTime == 0 || GetTickCount() - m_dwLastOnProgressTime >= 1000)
			{
				THttpNotify ProgressNotify;
				ProgressNotify.dwErrorCode = CURLE_OK;
				ProgressNotify.ullTotalSize = m_ullFileSize;
				ProgressNotify.fPercent = (float)m_ullCurDownloadSize / (float)m_ullFileSize;
				ProgressNotify.wstrFilePath = GetLocalFilePath().c_str();

				DWORD dwElapseTime = GetTickCount() - m_dwStartTime + 1;
				float fSpeed = ((float)(m_ullCurDownloadSize - m_ullLastFileSize) / 1024.0f) / ((float)dwElapseTime / 1000.0f);

				if (fSpeed < 0)
					fSpeed = 0;
				ProgressNotify.nSpeed = (int)fSpeed;
				ProgressNotify.nElapseTime = dwElapseTime / 1000;

				ULONGLONG ullRemainSizeInK = (m_ullFileSize - m_ullCurDownloadSize) / 1024;
				if (ProgressNotify.nSpeed)
					ProgressNotify.nRemainTime = (int)(ullRemainSizeInK / ProgressNotify.nSpeed);

				m_fSpeed = fSpeed;//保存最后一次的下载速度

				ProgressNotify.bType = NDHttpProgress;
				ProgressNotify.pUserData = GetUserData();
				if (GetDelegate())
				{
					if (!((pfnDeletegate)GetDelegate())(&ProgressNotify))
					{
						SetErrorDescription(_T("请求停止"));
						return 0;
					}
				}
				
				m_dwLastOnProgressTime = GetTickCount();
			}

		}

		return size* nmemb;
	}

	bool CHttpRequestFile::CompleteCallBack(CURLcode code)
	{
		bool bRet = true;

		std::unique_lock<std::mutex> lck(mtx);
		ReleaseFile();

		// check file size
		if (m_ullCurDownloadSize != 0 && m_ullCurDownloadSize == m_ullFileSize && code == CURLE_OK)
		{
			// rename *.ndf
			if (!MoveFileEx(m_strNdfFile.c_str(), GetLocalFilePath().c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING))
			{
				SetErrorDescription(_T("文件保存失败"));
				bRet = false;
			}
            else
            {
                // remove *.nds
                DeleteFile(m_strNdsFile.c_str());
            }
			
		}

		if (code == CURLE_RANGE_ERROR)
		{
			DeleteFile(m_strNdfFile.c_str());

			// remove *.nds
			DeleteFile(m_strNdsFile.c_str());
		}

		return bRet;
	}

	ULONGLONG CHttpRequestFile::GetLastFileSizePos()
	{
		m_ullLastFileSize = 0;
		m_ullDownloadTotalSizeInConfig = 0;

		FILE* fp = NULL;
		errno_t err = _tfopen_s(&fp, m_strNdsFile.c_str(), _T("rb"));
		if (err == 0)
		{
			fread(&m_ullLastFileSize, sizeof(ULONGLONG), 1, fp);
			fread(&m_ullDownloadTotalSizeInConfig, sizeof(ULONGLONG), 1, fp);
			fclose(fp);
		}

		if (m_ullLastFileSize == m_ullDownloadTotalSizeInConfig && m_ullDownloadTotalSizeInConfig != 0)
		{
			m_ullLastFileSize = 0;
			m_ullDownloadTotalSizeInConfig = 0;
		}

		m_ullCurDownloadSize = m_ullLastFileSize;
		return m_ullLastFileSize;
	}

	void CHttpRequestFile::SetConfPath()
	{
		CUtil Util;
		Util.DirectoryMake(GetLocalFilePath());
		m_strNdfFile = GetLocalFilePath();
		m_strNdsFile = m_strNdfFile;
		m_strNdfFile += _T(".ndf");
		m_strNdsFile += _T(".nds");
	}

	void CHttpRequestFile::ReleaseFile()
	{
		if (m_hNdfFile && m_hNdfFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hNdfFile);
			m_hNdfFile = NULL;
		}

		if (m_hNdsFile && m_hNdsFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hNdsFile);
			m_hNdsFile = NULL;
		}
	}

	void CHttpRequestFile::SetErrorDescription(wstring strErrorDescription)
	{
		m_strErrorDescription = strErrorDescription;
	}

	void CHttpRequestFile::Release()
	{
		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	CHttpUploadFile::CHttpUploadFile(CHttpUploadFileModel* pModel)
	{
		SetHost(pModel->strHost);
		SetUrl(pModel->strUrl);
		SetHeader(pModel->strHeader);
		SetMethod(pModel->strMethod);
		SetPost(pModel->strPost);
		SetPort(pModel->nPort);
		SetFileName(pModel->wstrFileName);
		SetLocalFilePath(pModel->wstrLocalFilePath);
		SetServerFilePath(pModel->wstrServerFilePath);
		SetStatus(CHttpUploadFile::NORAML);
        SetChunkUpload(pModel->bChunkUpload);
		SetDelegate(pModel->pfnDeletegate);
		SetUserData(pModel->pUserData);

		m_nBufferSize = 0x400;
		m_pBuffer = (char*)malloc(m_nBufferSize + 1);
		m_pBuffer[0] = 0x0;
		m_nRecvBufferSize = 0;

		m_dwStartTime = GetTickCount();
		m_dwLastTime = m_dwStartTime;
		m_ullUploadFileSize = 0;
		m_ullProgressSize = 0;
		m_nChunkIndex = 0;

		m_hFile = NULL;
	}

	CHttpUploadFile::~CHttpUploadFile()
	{
		if (m_pBuffer)
		{
			free(m_pBuffer);
			m_pBuffer = NULL;
		}
	}

	bool MySort(const _stChunk &v1, const _stChunk &v2)
	{
		return v1.nIndex < v2.nIndex;//升序排列  
	}

	DWORD CHttpUploadFile::Excute()
	{
		CURL *pCurl = NULL;
		CURLcode nRet = CURL_LAST;

		wstring wstrFileName, strFilePath;
		char * pData = NULL;

		CUtil Util;
		strFilePath = GetLocalFilePath();
		string strFileMD5 = Util.CalcFileMD5(strFilePath);
		m_hFile = CreateFile(strFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (m_hFile == INVALID_HANDLE_VALUE)
		{
			SetErrorDescription(_T("文件打开失败"));
			goto _Out;
		}

		LARGE_INTEGER  liCurrentPosition;
		GetFileSizeEx(m_hFile, &liCurrentPosition);
		ULONGLONG ullFileSize = liCurrentPosition.QuadPart;
		SetFileSize(ullFileSize);
		//get file name
		TCHAR szDrive[8] = { 0 };
		TCHAR szDir[MAX_PATH * 2] = { 0 };
		TCHAR szFile[MAX_PATH * 2] = { 0 };
		TCHAR szExt[MAX_PATH * 2] = { 0 };
		if (_tsplitpath_s(strFilePath.c_str(), szDrive, szDir, szFile, szExt))
		{
			SetErrorDescription(_T("路径解析错误"));
			goto _Out;
		}

		if (GetFileName().empty())//时间戳命名
		{
			wstrFileName = Util.Utf82Str(strFileMD5);
			wstrFileName += szExt;
		}
		else
			wstrFileName = GetFileName();

		//分块上传，默认每块5M
        if (GetChunkUpload())
        {
            m_nChunkCount = (int)(ullFileSize / CHUNKSIZE) + 1;
        }
        else
            m_nChunkCount = 1;
		char szBodySize[1024] = { 0 };
		char szChunkCount[1024] = { 0 };
		char szChunk[1024] = { 0 };
		char szChunkSize[1024] = { 0 };
		CURLM *multi_handle;
		
		multi_handle = curl_multi_init();
		if (!m_strFileMD5.empty() && strFileMD5 != m_strFileMD5)
		{
			SetErrorDescription(_T("文件已修改"));
			goto _Out;
		}
		m_strFileMD5 = strFileMD5;
		for (; m_nChunkIndex < m_nChunkCount; m_nChunkIndex++)
		{
			m_nRecvBufferSize = 0;
			m_ullProgressSize = 0;
			pCurl = curl_easy_init();
			
			curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1);
			curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, 0);
			//设置进度回调函数  
			curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, &CHttpUploadFile::UploadCallback);
			curl_easy_setopt(pCurl, CURLOPT_PROGRESSDATA, this);

			curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &CHttpUploadFile::GetHttpCallBack);
			curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, this);

			string strUrl = "http://";
			strUrl += GetHost();
			strUrl += GetUrl();
			curl_easy_setopt(pCurl, CURLOPT_URL, strUrl.c_str()); //设置下载的URI

			curl_easy_setopt(pCurl, CURLOPT_PORT, m_nPort);
			string strMethod = "POST";
			curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST, strMethod.c_str());

			struct curl_httppost *formpost = 0;
			struct curl_httppost *lastptr = 0;

			curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "name", CURLFORM_COPYCONTENTS, Util.Str2Utf8(wstrFileName).c_str(), CURLFORM_END);

			if (GetMethod() == "PUT")//替换文件
				curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "FilePath", CURLFORM_COPYCONTENTS, Util.Str2Utf8((GetServerFilePath() + wstrFileName)).c_str(), CURLFORM_END);
			else//上传新文件
				curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "Path", CURLFORM_COPYCONTENTS, Util.Str2Utf8(GetServerFilePath()).c_str(), CURLFORM_END);

			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "scope", CURLFORM_PTRCONTENTS, "1", CURLFORM_END);

			sprintf_s(szBodySize, "%I64d", ullFileSize);
			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "size", CURLFORM_PTRCONTENTS, szBodySize, CURLFORM_END);

			sprintf_s(szChunkCount, "%d", m_nChunkCount);
			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "chunks", CURLFORM_PTRCONTENTS, szChunkCount, CURLFORM_END);

			sprintf_s(szChunk, "%d", m_nChunkIndex);
			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "chunk", CURLFORM_PTRCONTENTS, szChunk, CURLFORM_END);

			ULONG ulSize = (ULONG)(ullFileSize >= CHUNKSIZE * (m_nChunkIndex + 1) ? CHUNKSIZE : ullFileSize - CHUNKSIZE * m_nChunkIndex);

			sprintf_s(szChunkSize, "%d", ulSize);
			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "chunkSize", CURLFORM_PTRCONTENTS, szChunkSize, CURLFORM_END);

			//pos
			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "pos", CURLFORM_PTRCONTENTS, "0", CURLFORM_END);

			//md5
			curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "md5", CURLFORM_PTRCONTENTS, strFileMD5.c_str(), CURLFORM_END);

			if (pData == NULL)
				pData = new char[ulSize];
			if (pData == NULL)
			{
				break;
			}

			{
				std::unique_lock<std::mutex> lck(mtx);
				if (m_hFile && m_hFile != INVALID_HANDLE_VALUE)
				{
					DWORD  dwBytesRead = 0;
					LARGE_INTEGER  liCurrentPosition;
					liCurrentPosition.QuadPart = m_nChunkIndex * CHUNKSIZE;
					SetFilePointerEx(m_hFile, liCurrentPosition, 0, FILE_BEGIN);
					ReadFile(m_hFile, pData, ulSize, &dwBytesRead, NULL);
					if (dwBytesRead <= 0)
					{
						break;
					}
				}
			}


			curl_formadd(&formpost,
				&lastptr,
				CURLFORM_COPYNAME, "file",
				CURLFORM_BUFFER, Util.Str2Utf8(wstrFileName).c_str(),//filename
				CURLFORM_BUFFERPTR, pData,//the uploaded data
				CURLFORM_BUFFERLENGTH, ulSize,//the length of uploaded data
				CURLFORM_END);

			curl_easy_setopt(pCurl, CURLOPT_HTTPPOST, formpost);

			curl_multi_add_handle(multi_handle, pCurl);

			BOOL bUpload;
			curl_multi_perform(multi_handle, &bUpload);

			int nRetry = 0;
			do {
				struct timeval timeout;
				int rc; /* select() return code */
				CURLMcode mc; /* curl_multi_fdset() return code */

				fd_set fdread;
				fd_set fdwrite;
				fd_set fdexcep;
				int maxfd = -1;

				long curl_timeo = -1;

				FD_ZERO(&fdread);
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdexcep);

				/* set a suitable timeout to play around with */
				timeout.tv_sec = 1;
				timeout.tv_usec = 0;

				curl_multi_timeout(multi_handle, &curl_timeo);
				if (curl_timeo >= 0) {
					timeout.tv_sec = curl_timeo / 1000;
					if (timeout.tv_sec > 1)
						timeout.tv_sec = 1;
					else
						timeout.tv_usec = (curl_timeo % 1000) * 1000;
				}

				/* get file descriptors from the transfers */
				mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

				if (mc != CURLM_OK)
				{
					//fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
					break;
				}

				/* On success the value of maxfd is guaranteed to be >= -1. We call
				select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
				no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
				to sleep 100ms, which is the minimum suggested value in the
				curl_multi_fdset() doc. */

				if (maxfd == -1) {
#ifdef _WIN32
					Sleep(100);
					rc = 0;
#else
					/* Portable sleep for platforms other than Windows. */
					struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
					rc = select(0, NULL, NULL, NULL, &wait);
#endif
				}
				else {
					/* Note that on some platforms 'timeout' may be modified by select().
					If you need access to the original value save a copy beforehand. */
					rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
				}

				switch (rc) {
				case -1:
					/* select error */
					break;
				case 0:/* timeout */
				{
						   curl_multi_perform(multi_handle, &bUpload);
						   nRetry++;
				}
					break;
				default:
					/* readable/writable sockets */
				{
						   nRetry = 0;
						   curl_multi_perform(multi_handle, &bUpload);
				}
					break;
				}
				if (nRetry > 60)
				{
					SetErrorDescription(_T("上传超时"));
					break;
				}
			} while ((GetStatus() != CHttpUploadFile::PAUSE) && (GetStatus() != CHttpUploadFile::STOP) && bUpload);

			int msgs_left;
			CURLMsg* pCurlMsg = curl_multi_info_read(multi_handle, &msgs_left);
			if (pCurlMsg && (pCurlMsg->msg == CURLMSG_DONE)) {
				nRet = pCurlMsg->data.result;
			}

			curl_multi_remove_handle(multi_handle, pCurl);

			/* always cleanup */
			curl_easy_cleanup(pCurl);

			/* then cleanup the formpost chain */
			curl_formfree(formpost);

			if ((GetStatus() == CHttpUploadFile::PAUSE) || (GetStatus() == CHttpUploadFile::STOP) || nRet != CURLE_OK)
				break;

			//增加解析
			if (m_pBuffer)
			{
				m_pBuffer[m_nRecvBufferSize] = 0;
			}

			Document document;
			if (document.Parse(m_pBuffer).HasParseError())
			{
				SetErrorDescription(_T("json解析失败"));
				break;
			}

			string strCode = GetStringByKey(document, "code");
			if (!strCode.empty())
			{
				CUtil Util;
				std::wstring wstrErrorDescription = Util.Utf82Str(GetStringByKey(document, "message"));
				SetErrorDescription(wstrErrorDescription);
				break;
			}

			std::string strDentryId = GetStringByKey(document, "dentry_id");
			if (!strDentryId.empty())
			{
				m_nChunkIndex = m_nChunkCount;
			}
			else
			{
				_stChunk stChunk;
				std::string strName;
				UINT nIndex = 0;
				vector<_stChunk> vecSizes;
				for (auto iter = document.MemberBegin(); iter != document.MemberEnd(); ++iter)
				{
					stChunk.nIndex = atoi(GetString(iter->name).c_str());
					stChunk.ullSize = GetUint64ByKey(iter->value, "size");
					vecSizes.push_back(stChunk);
				}

				std::sort(vecSizes.begin(), vecSizes.end(), MySort);
				for (UINT i = 0; i < m_nChunkCount; i++)
				{
					if (i >= vecSizes.size())
						break;
					if (vecSizes[i].nIndex != i)
						break;
					nIndex++;
				}
				m_nChunkIndex = --nIndex;

				m_ullUploadFileSize = 0;
				for (UINT i = 0; i < m_nChunkIndex && i < vecSizes.size(); i++)
				{
					m_ullUploadFileSize += vecSizes[i].ullSize;
				}
			}

			//
			m_ullUploadFileSize = m_ullUploadFileSize + ulSize;
		}

		curl_multi_cleanup(multi_handle);
	_Out:
		if (pData)
		{
			delete pData;
			pData = NULL;
		}

		if (m_hFile && m_hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hFile);
			m_hFile = NULL;
		}

// 		if (m_pBuffer)
// 		{
// 			m_pBuffer[m_nRecvBufferSize] = 0;
// 		}

		THttpNotify CompleteNotify;
		if (nRet != CURLE_OK)
		{
			if (m_strErrorDescription.empty())
				SetErrorDescription(_T("#Server_Connect_Failed"));

			CompleteNotify.wstrErrorDescription = m_strErrorDescription;
			
		}

		CompleteNotify.dwErrorCode = nRet;
		switch (GetStatus())
		{
		case  CHttpRequestFile::PAUSE:
			CompleteNotify.bType = NDHttpPause;
			break;
		case  CHttpRequestFile::STOP:
			CompleteNotify.bType = NDHttpCancel;
			break;
		default:
			CompleteNotify.bType = NDHttpComplete;
			break;
		}
		CompleteNotify.szData = m_pBuffer;
		CompleteNotify.nDataSize = m_nRecvBufferSize;
		CompleteNotify.pUserData = GetUserData();

		if (GetDelegate())
			((pfnDeletegate)GetDelegate())(&CompleteNotify);

		return nRet;
	}

	void CHttpUploadFile::Cancel()
	{
		std::unique_lock<std::mutex> lck(mtx);
		SetStatus(CHttpRequestFile::STOP);
		ReleaseFile();
	}

	void CHttpUploadFile::Pause()
	{
		std::unique_lock<std::mutex> lck(mtx);
		SetStatus(CHttpRequestFile::PAUSE);
		ReleaseFile();
	}

	void CHttpUploadFile::Resume()
	{
		SetStatus(CHttpRequestFile::NORAML);
	}

	LPCSTR CHttpUploadFile::GetResult()
	{
		return m_pBuffer;
	}


	size_t CHttpUploadFile::GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		CHttpUploadFile* pTask = (CHttpUploadFile*)userp;

		return pTask->ResponseCallBack(ptr, size, nmemb, userp);
	}

	size_t CHttpUploadFile::UploadCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
	{
		CHttpUploadFile* pTask = (CHttpUploadFile*)clientp;

		return pTask->ProgressCallback(clientp, dltotal, dlnow, ultotal, ulnow);
	}

	size_t CHttpUploadFile::ResponseCallBack(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		int nSize = m_nRecvBufferSize;
		nSize += size * nmemb;
		if (nSize >= m_nBufferSize)
		{
			m_nBufferSize = m_nBufferSize * 2 > nSize ? m_nBufferSize * 2 : nSize;
			m_pBuffer = (char*)realloc(m_pBuffer, m_nBufferSize + 1);
		}

		memcpy_s(m_pBuffer + m_nRecvBufferSize, m_nBufferSize - m_nRecvBufferSize, ptr, size * nmemb);

		m_nRecvBufferSize += size * nmemb;
		
		return size* nmemb;
	}

	size_t CHttpUploadFile::ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
	{
		CHttpRequestFile* pTask = (CHttpRequestFile*)clientp;

		if (GetTickCount() - m_dwLastTime >= 1000)
		{
			ULONGLONG ullUploadFileSize = (ULONGLONG)(m_ullUploadFileSize + ulnow);

			THttpNotify ProgressNotify;
			ProgressNotify.ullTotalSize = GetFileSize();
			ProgressNotify.fPercent = (float)((double)ullUploadFileSize / (double)GetFileSize());

			// calculate speed
			DWORD dwElapseTime = GetTickCount() - m_dwLastTime;
			float fSpeed = (float)(ulnow - m_ullProgressSize) / 1024.0f / ((float)dwElapseTime / 1000.0f);

			m_ullProgressSize = (ULONGLONG)ulnow;
			m_dwLastTime = GetTickCount();

			ProgressNotify.nSpeed = (int)fSpeed;
			if (ProgressNotify.nSpeed < 0)
				ProgressNotify.nSpeed = 0;

			ProgressNotify.nElapseTime = (GetTickCount() - m_dwStartTime) / 1000;

			// calculate remain time
			ULONGLONG nRemainSizeInK = (m_ullFileSize - ullUploadFileSize) / 1024;

			if (ProgressNotify.nSpeed)
				ProgressNotify.nRemainTime = (int)(nRemainSizeInK / ProgressNotify.nSpeed);

			ProgressNotify.bType = NDHttpProgress;
			ProgressNotify.pUserData = GetUserData();
			if (GetDelegate())
				((pfnDeletegate)GetDelegate())(&ProgressNotify);
		}
		return 0;
	}

	void CHttpUploadFile::SetFileSize(ULONGLONG ullFileSize)
	{
		m_ullFileSize = ullFileSize;
	}

	ULONGLONG CHttpUploadFile::GetFileSize()
	{
		return m_ullFileSize;
	}

	void CHttpUploadFile::ReleaseFile()
	{
		if (m_hFile)
		{
			CloseHandle(m_hFile);
			m_hFile = NULL;
		}
	}

	void CHttpUploadFile::SetErrorDescription(wstring strError)
	{
		m_strErrorDescription = strError;
	}

	void CHttpUploadFile::Release()
	{
		delete this;
	}

}