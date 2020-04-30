#pragma once

struct AttributeList_Impl;

class AttributeList
{
public:
	AttributeList();
	AttributeList(const AttributeList& r);

	~AttributeList();

	void AddAttribute(const wstring& sName,
		const wstring& sType,
		const wstring& sValue);

	void Clear();

	sal_Int16 getLength();

	wstring getNameByIndex(sal_Int16 i);

	wstring getTypeByIndex(sal_Int16 i);

	wstring getTypeByName(const wstring& aName);

	wstring getValueByIndex(sal_Int16 i);

	wstring getValueByName(const wstring& aName);

private:
	std::unique_ptr<AttributeList_Impl> m_pImpl;
};