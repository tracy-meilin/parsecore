#pragma once

struct AttributeList_Impl;

class AttributeList
{
public:
	AttributeList();
	AttributeList(const AttributeList& r);
	AttributeList(const shared_ptr<AttributeList>& r);

	~AttributeList();

	void AddAttribute(const wstring& sName,
		const wstring& sType,
		const wstring& sValue);

	void AppendAttributeList(const shared_ptr<AttributeList>& r);

	void Clear();

	sal_Int16 getLength() const;

	wstring getNameByIndex(sal_Int16 i) const;

	wstring getTypeByIndex(sal_Int16 i);

	wstring getTypeByName(const wstring& aName);

	wstring getValueByIndex(sal_Int16 i) const;

	wstring getValueByName(const wstring& aName);

private:
	std::unique_ptr<AttributeList_Impl> m_pImpl;
};