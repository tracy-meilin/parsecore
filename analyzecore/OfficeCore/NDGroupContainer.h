#pragma once

class OfficeCore_API CNDGroupContainer
{
public:
	CNDGroupContainer(shared_ptr<GroupContainer>& spGroupContainer);
	~CNDGroupContainer();

	shared_ptr<CNDShape> GetNDFirstNvShape();

	vector<shared_ptr<CNDShape>> GetNDShapes();

private:
	void Init();

private:
	vector<shared_ptr<CNDShape>> m_vecNDShapes;
	shared_ptr<CNDShape> m_spNDHeaderGrpShape = nullptr;

	shared_ptr<GroupContainer> m_spGroupContainer = nullptr;

	bool bInit = false;
};

