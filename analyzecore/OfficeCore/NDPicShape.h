#pragma once

class OfficeCore_API CNDPicShape 
	: public CNDShape
{
public:
	CNDPicShape(shared_ptr<ShapeContainer>& spShapeContainer);
	~CNDPicShape();

	virtual NDShapeType GetShapeType() override;

	shared_ptr<NDBlipFill> GetBlipFill();

	shared_ptr<NDNVPicProperties> GetNvPicPr();

private:
	shared_ptr<NDNVPicProperties> m_spNvPicPr = nullptr;

	shared_ptr<NDBlipFill> m_spBlipFill = nullptr;
};

