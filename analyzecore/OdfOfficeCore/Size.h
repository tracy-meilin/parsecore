#pragma once

namespace awt{
	struct Size
	{
		Size(){};

		Size(const signed long Width_, const signed long Height_)
		{
			Width = Width_;
			Height = Height_;
		}

		signed long Width;
		signed long Height;
	};
}

