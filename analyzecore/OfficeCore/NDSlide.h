#pragma once
class OfficeCore_API CNDSlide
{
public:
	CNDSlide(shared_ptr<Slide>& spSlide);
	~CNDSlide();

	vector<shared_ptr<CNDShape>> GetShapes();

private:
	shared_ptr<Slide> m_spSlide = nullptr;
	shared_ptr<CNDPPDrawing> m_spNDPPDrawing = nullptr;
};

