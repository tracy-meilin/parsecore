#pragma once

class OfficeCore_API CNDPPDrawing
{
public:
	CNDPPDrawing(shared_ptr<PPDrawing>& spPPDrawing);
	~CNDPPDrawing();

	vector<shared_ptr<CNDDrawingContainer>>& GetDrawingConatiners();

private:
	shared_ptr<PPDrawing> m_spPPDrawing = nullptr;
	vector<shared_ptr<CNDDrawingContainer>> m_vecDrawingContainers;
};

