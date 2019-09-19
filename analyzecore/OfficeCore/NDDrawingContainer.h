#pragma once

class OfficeCore_API CNDDrawingContainer
{
public:
	CNDDrawingContainer(shared_ptr<DrawingContainer>& spDrawingContainer);
	~CNDDrawingContainer();

	shared_ptr<CNDGroupContainer> GetGroupContainer();

private:
	shared_ptr<DrawingContainer> m_spDrawingContainer;
	shared_ptr<CNDGroupContainer> m_spNDGroupContaioner = nullptr;
};

