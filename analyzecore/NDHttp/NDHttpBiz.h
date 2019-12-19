#pragma once
#include <mutex>
#include "NDHttp.h"
#include "NDHttpBo.h"

struct _stChunk
{
	UINT nIndex;
	ULONGLONG ullSize;
};

namespace NDHttp
{
	class CNDHttpDownBuilderBiz;
	class CNDHttpUploadBuilderBiz;
	//////////////////////////////////////////////////////////////////////////
	class CHttpRequestData : public CNDHttpBo, public IHttpRequestData
	{
	public:
		CHttpRequestData(CHttpRequestDataModel* pModel);
		~CHttpRequestData();

	public:
		virtual DWORD Excute();
		virtual DWORD GetHttpCode();
		virtual LPCSTR GetHttpHeader();
		virtual LPCSTR GetResult();
		virtual DWORD GetLength()	{ return m_nRecvBufferSize; }
		virtual LPCTSTR GetErrorDescritpion() { return m_strErrorDescription.c_str(); }

		void  SetErrorDescritpion(wstring strError);
		void  Release();
	protected:
		static size_t	GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		static size_t	GetHttpHeaderCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		size_t ProgrossCallBack(void *ptr, size_t size, size_t nmemb, void *userp);

	private:
		char*	m_pBuffer; // recv buffer
		int		m_nBufferSize;
		int		m_nRecvBufferSize;

		DWORD	m_dwHttpCode;
		wstring m_strErrorDescription;
		string  m_strHttpHeader;
	};

	//////////////////////////////////////////////////////////////////////////
	class CHttpRequestFile : public CNDHttpBo, public IHttpRequestFile
	{
	public:
		enum { NORAML, PAUSE, STOP };
	public:
		CHttpRequestFile(CHttpRequestFileModel* pModel);
		~CHttpRequestFile();

	public:
		virtual DWORD Excute();
		virtual void Cancel();
		virtual void Pause();
		virtual void Resume();
		virtual LPCTSTR GetErrorDescription()	{ return m_strErrorDescription.c_str(); }
		virtual ULONGLONG	GetFileSize()		{ return m_ullFileSize; };
		void  Release();

		void	SetLocalFilePath(wstring wstrLocalFilePath)		{ m_wstrLocalFilePath = wstrLocalFilePath; }
		wstring& GetLocalFilePath()			{ return m_wstrLocalFilePath; }

		void	SetStatus(DWORD	dwStatus)	{ m_dwStatus = dwStatus; }
		DWORD	GetStatus()					{ return m_dwStatus; }

		ULONGLONG	GetLastFileSizePos();
		
		void  SetConfPath();
		
		void SetNDHttpBuilderBiz(CNDHttpDownBuilderBiz*	pNDHttpBuilderBiz) { m_pNDHttpBuilderBiz = pNDHttpBuilderBiz; }
		CNDHttpDownBuilderBiz* GetNDHttpBuilderBiz() { return m_pNDHttpBuilderBiz; }

	protected:
		static size_t	GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		static size_t	GetHttpHeaderCallBack(void *ptr, size_t size, size_t nmemb, void *userp);

		size_t StartCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		size_t ProgrossCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		bool   CompleteCallBack(CURLcode code);
		void   ReleaseFile();

		void	SetErrorDescription(wstring strErrorDescription);

	private:
		DWORD		m_dwHttpCode;			//HttpCode
		ULONGLONG	m_ullDownloadTotalSize;	//本次需要下载的文件大小
		ULONGLONG	m_ullFileSize;			//实际真正的文件大小
		ULONGLONG	m_ullCurDownloadSize;	//当前已下载大小
		ULONGLONG	m_ullDownloadTotalSizeInConfig;//配置中记录的总大小，主要用于对比服务器上下载的文件是否有调整

		ULONGLONG	m_ullLastFileSize;		//断点续传起始位置

		HANDLE	m_hNdfFile;				//Config路径
		HANDLE	m_hNdsFile;				//下载文件路径

		DWORD	m_dwStartTime;			//下载开始时间
		DWORD	m_dwLastOnProgressTime; //记录上次回调时间

		wstring	m_strNdfFile;			//Config配置文件句柄
		wstring	m_strNdsFile;			//下载文件句柄

		DWORD	m_dwStatus;				//任务状态 NORAML, PAUSE, STOP
		wstring	m_strErrorDescription;	//失败错误描述

		wstring m_wstrLocalFilePath;	//下载到本地的文件路径

		CNDHttpDownBuilderBiz*	m_pNDHttpBuilderBiz;

		float	m_fSpeed;			//保存最后一次的下载速度

		std::mutex mtx;           // mutex for critical section
	};

	//////////////////////////////////////////////////////////////////////////
#define CHUNKSIZE ( 1024 * 1024 )
	class CHttpUploadFile : public CNDHttpBo, public IHttpUploadFile
	{
	public:
		enum { NORAML, PAUSE, STOP };
	public:
		CHttpUploadFile(CHttpUploadFileModel* pModel);
		~CHttpUploadFile();

	public:
		virtual DWORD Excute();
		virtual void Cancel();
		virtual void Pause();
		virtual void Resume();
		virtual LPCSTR GetResult();

		void  Release();

		void	SetLocalFilePath(wstring wstrLocalFilePath)		{ m_wstrLocalFilePath = wstrLocalFilePath; }
		wstring& GetLocalFilePath()			{ return m_wstrLocalFilePath; }

		void	SetServerFilePath(wstring wstrServerFilePath)	
		{ 
			m_wstrServerFilePath = wstrServerFilePath;
			if (!m_wstrServerFilePath.empty())
			{
				WCHAR wc = m_wstrServerFilePath.back();
				if (wc != _T('/'))
					m_wstrServerFilePath += _T("/");
			}
		}
		wstring& GetServerFilePath()			{ return m_wstrServerFilePath; }

		void	SetFileName(wstring wstrFileName)	{ m_wstrFileName = wstrFileName; }
		wstring& GetFileName()				{ return m_wstrFileName; }

		void	SetStatus(DWORD	dwStatus)	{ m_dwStatus = dwStatus; }
		DWORD	GetStatus()					{ return m_dwStatus; }

        void    SetChunkUpload(bool bChunkUpload)   { m_bChunkUpload = bChunkUpload; }
        DWORD	GetChunkUpload()					{ return m_bChunkUpload; }

		void		SetFileSize(ULONGLONG ullFileSize);
		ULONGLONG	GetFileSize();

		void	SetErrorDescription(wstring strError);
		LPCTSTR GetErrorDescription()	{ return m_strErrorDescription.c_str(); }

		void SetNDHttpBuilderBiz(CNDHttpUploadBuilderBiz*	pNDHttpBuilderBiz) { m_pNDHttpBuilderBiz = pNDHttpBuilderBiz; }
		CNDHttpUploadBuilderBiz* GetNDHttpBuilderBiz() { return m_pNDHttpBuilderBiz; }
	protected:
		static size_t	GetHttpCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		static size_t	UploadCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

		size_t ResponseCallBack(void *ptr, size_t size, size_t nmemb, void *userp);
		size_t ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

		void   ReleaseFile();
	private:
		DWORD	m_dwStatus;				//任务状态 NORAML, PAUSE, STOP

		wstring m_wstrLocalFilePath;	//本地上传文件路径
		wstring m_wstrServerFilePath;	//remote server file save path
		wstring m_wstrFileName;

		char*	m_pBuffer; // recv buffer
		int		m_nBufferSize;
		int		m_nRecvBufferSize;

		HANDLE	m_hFile;				//上传文件句柄

		wstring	m_strErrorDescription;	//失败错误描述

		DWORD	m_dwLastTime;			//记录上次回调时间
		DWORD	m_dwStartTime;			//本次任务开始时间
		ULONGLONG	m_ullFileSize;		//上传文件大小
		ULONGLONG	m_ullUploadFileSize;//
		ULONGLONG	m_ullProgressSize;

		CNDHttpUploadBuilderBiz*	m_pNDHttpBuilderBiz;

		std::mutex mtx;           // mutex for critical section
		UINT m_nChunkIndex;
		UINT m_nChunkCount;
		std::string m_strFileMD5;
        bool m_bChunkUpload = true;
	};
}
