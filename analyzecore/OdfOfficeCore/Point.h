#pragma once

namespace awt{
	struct Point{
		Point(){}

		Point(const signed long X_, const signed long Y_)
		{
			X = X_;
			Y = Y_;
		}

		signed long X;
		signed long Y;
	};
}