#pragma once
class  CHttpRequestDataModel;
namespace NDhttp_Wrapper
{
	inline DWORD Excute(CHttpRequestDataModel* pModel, std::string& strData)
	{
		HttpRequestData* pRequest = RequestDataInit(pModel);
		DWORD dwRet = pRequest->Excute();
		if (dwRet == 0)
		{
			strData = pRequest->GetResult();
		}
		CleanUpData(pRequest);
		return dwRet;
	}

	inline DWORD Excute(CHttpRequestDataModel* pModel, LPSTR* pszData, DWORD& dwLength)
	{
		HttpRequestData* pRequest = RequestDataInit(pModel);
		DWORD dwRet = pRequest->Excute();
		if (dwRet == 0)
		{
			LPCSTR pszTemp = pRequest->GetResult();
			dwLength = pRequest->GetLength();
			*pszData = new char[dwLength];
			memcpy_s(*pszData, dwLength, pszTemp, dwLength);
		}
		CleanUpData(pRequest);
		return dwRet;
	}
}
