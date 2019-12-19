#pragma once

namespace NDHttp
{
	class CNDHttpBo
	{
	public:
		CNDHttpBo() {}
		~CNDHttpBo() {}

	public:
		void	SetHost(string& strHost)		{ m_strHost = strHost;  }
		void	SetUrl(string& strUrl)			{ m_strUrl = strUrl;  }
		void	SetHeader(string& strHeader)	{ m_strHeader = strHeader;  }
		void	SetMethod(string& strMethod)	{ m_strMethod = strMethod;  }
		void	SetPost(string& strPost)			{ m_strPost = strPost;  }
		void	SetPort(int nPort)				{ m_nPort = nPort; }
		void	SetTimeout(UINT nTimeout)				{ m_nTimeout = nTimeout; }
		void	SetDelegate(PVOID pDelegate)	{ m_pDelegate = pDelegate; }
		void	SetUserData(PVOID pUserData)	{ m_pUserData = pUserData; }

		string GetHost()		{ return m_strHost; }
		string GetUrl()			{ return m_strUrl; }
		string GetHeader()		{ return m_strHeader; }
		string GetMethod()		{ return m_strMethod; }
		string	GetPost()		{ return m_strPost; }
		int		GetPort()		{ return m_nPort; }
		UINT	GetTimeout()	{ return m_nTimeout; }
		PVOID	GetDelegate()	{ return m_pDelegate; }
		PVOID	GetUserData()	{ return m_pUserData; }

	protected:
		string	m_strHost;//host
		string	m_strUrl;//url
		string	m_strHeader;//header
		string	m_strMethod; //method
		string  m_strPost;//post content
		int		m_nPort;//port
		UINT	m_nTimeout;//Timeout
		PVOID	m_pDelegate;
		PVOID	m_pUserData;
	};
}