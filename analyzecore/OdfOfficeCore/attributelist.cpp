#include "stdafx.h"
#include "attributelist.h"

struct TagAttribute_Impl
{
	TagAttribute_Impl(const wstring& aName,
		const wstring& aType,
		const wstring& aValue)
	{
		this->sName = aName;
		this->sType = aType;
		this->sValue = aValue;
	}

	wstring sName;
	wstring sType;
	wstring sValue;
};

struct AttributeList_Impl
{
	AttributeList_Impl()
	{
		// performance improvement during adding
		vecAttribute.reserve(20);
	}
	::std::vector<struct TagAttribute_Impl> vecAttribute;
};

AttributeList::AttributeList() 
	: m_pImpl(new AttributeList_Impl) 
{

}

AttributeList::AttributeList(const AttributeList& r)
	: m_pImpl(new AttributeList_Impl)
{
	*m_pImpl = *(r.m_pImpl);
}

AttributeList::~AttributeList()
{

}

void AttributeList::AddAttribute(const wstring& sName, const wstring& sType, const wstring& sValue)
{
	m_pImpl->vecAttribute.push_back(TagAttribute_Impl(sName, sType, sValue));
}

void AttributeList::Clear()
{
	m_pImpl->vecAttribute.clear();
}

sal_Int16 AttributeList::getLength()
{
	return (sal_Int16)(m_pImpl->vecAttribute.size());
}

std::wstring AttributeList::getNameByIndex(sal_Int16 i)
{
	return (i < static_cast < sal_Int16 > (m_pImpl->vecAttribute.size())) ? m_pImpl->vecAttribute[i].sName : wstring();
}

std::wstring AttributeList::getTypeByIndex(sal_Int16 i)
{
	if (i < static_cast <sal_Int16> (m_pImpl->vecAttribute.size())) {
		return m_pImpl->vecAttribute[i].sType;
	}
	return wstring();
}

std::wstring AttributeList::getTypeByName(const wstring& aName)
{
	::std::vector<struct TagAttribute_Impl>::iterator ii = m_pImpl->vecAttribute.begin();

	for (; ii != m_pImpl->vecAttribute.end(); ++ii) {
		if ((*ii).sName == aName) {
			return (*ii).sType;
		}
	}
	return wstring();
}

std::wstring AttributeList::getValueByIndex(sal_Int16 i)
{
	return (i < static_cast < sal_Int16 > (m_pImpl->vecAttribute.size())) ? m_pImpl->vecAttribute[i].sValue : wstring();
}

std::wstring AttributeList::getValueByName(const wstring& aName)
{
	::std::vector<struct TagAttribute_Impl>::iterator ii = m_pImpl->vecAttribute.begin();

	for (; ii != m_pImpl->vecAttribute.end(); ++ii) {
		if ((*ii).sName == aName) {
			return (*ii).sValue;
		}
	}
	return wstring();
}
