#pragma once
class Handle
{
public:
	Handle();
	Handle(wstring pos, wstring xRange);
	~Handle();

public:
	wstring position;
	wstring xrange;
	wstring switchHandle;
	wstring yrange;
	wstring polar;
	wstring radiusrange;
};

