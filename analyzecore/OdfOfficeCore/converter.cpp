#include "stdafx.h"
#include "converter.h"

namespace sax{

	converter::converter()
	{
	}


	converter::~converter()
	{
	}

	bool sax::converter::convertMeasure(sal_Int32& rValue, 
		const wstring& rString, 
		sal_Int16 nTargetUnit /*= MeasureUnit::MM_100TH*/, 
		sal_Int32 nMin /*= SAL_MIN_INT32*/, 
		sal_Int32 nMax /*= SAL_MAX_INT32*/)
	{
		bool bNeg = false;
		double nVal = 0;

		sal_Int32 nPos = 0;
		sal_Int32 const nLen = rString.size();

		// skip white space
		while ((nPos < nLen) && (rString[nPos] <= ' '))
			nPos++;

		if (nPos < nLen && '-' == rString[nPos])
		{
			bNeg = true;
			nPos++;
		}

		// get number
		while (nPos < nLen &&
			'0' <= rString[nPos] &&
			'9' >= rString[nPos])
		{
			// TODO: check overflow!
			nVal *= 10;
			nVal += (rString[nPos] - '0');
			nPos++;
		}
		if (nPos < nLen && '.' == rString[nPos])
		{
			nPos++;
			double nDiv = 1.;

			while (nPos < nLen &&
				'0' <= rString[nPos] &&
				'9' >= rString[nPos])
			{
				// TODO: check overflow!
				nDiv *= 10;
				nVal += (((double)(rString[nPos] - '0')) / nDiv);
				nPos++;
			}
		}

		// skip white space
		while ((nPos < nLen) && (rString[nPos] <= ' '))
			nPos++;

		if (nPos < nLen)
		{

			if (MeasureUnit::PERCENT == nTargetUnit)
			{
				if ('%' != rString[nPos])
					return false;
			}
			else if (MeasureUnit::PIXEL == nTargetUnit)
			{
				if (nPos + 1 >= nLen ||
					('p' != rString[nPos] &&
					'P' != rString[nPos]) ||
					('x' != rString[nPos + 1] &&
					'X' != rString[nPos + 1]))
					return false;
			}
			else
			{
				const sal_Char *aCmpsL[3] = { nullptr, nullptr, nullptr };
				const sal_Char *aCmpsU[3] = { nullptr, nullptr, nullptr };
				double aScales[3] = { 1., 1., 1. };

				if (MeasureUnit::TWIP == nTargetUnit)
				{
					switch (rString[nPos])
					{
					case sal_Unicode('c'):
					case sal_Unicode('C'):
						aCmpsL[0] = "cm";
						aCmpsU[0] = "CM";
						aScales[0] = (72.*20.) / 2.54; // twip
						break;
					case sal_Unicode('i'):
					case sal_Unicode('I'):
						aCmpsL[0] = "in";
						aCmpsU[0] = "IN";
						aScales[0] = 72.*20.; // twip
						break;
					case sal_Unicode('m'):
					case sal_Unicode('M'):
						aCmpsL[0] = "mm";
						aCmpsU[0] = "MM";
						aScales[0] = (72.*20.) / 25.4; // twip
						break;
					case sal_Unicode('p'):
					case sal_Unicode('P'):
						aCmpsL[0] = "pt";
						aCmpsU[0] = "PT";
						aScales[0] = 20.; // twip

						aCmpsL[1] = "pc";
						aCmpsU[1] = "PC";
						aScales[1] = 12.*20.; // twip
						break;
					}
				}
				else if (MeasureUnit::MM_100TH == nTargetUnit || MeasureUnit::MM_10TH == nTargetUnit)
				{
					double nScaleFactor = (MeasureUnit::MM_100TH == nTargetUnit) ? 100.0 : 10.0;
					switch (rString[nPos])
					{
					case sal_Unicode('c'):
					case sal_Unicode('C'):
						aCmpsL[0] = "cm";
						aCmpsU[0] = "CM";
						aScales[0] = 10.0 * nScaleFactor; // mm/100
						break;
					case sal_Unicode('i'):
					case sal_Unicode('I'):
						aCmpsL[0] = "in";
						aCmpsU[0] = "IN";
						aScales[0] = 1000.*2.54; // mm/100
						break;
					case sal_Unicode('m'):
					case sal_Unicode('M'):
						aCmpsL[0] = "mm";
						aCmpsU[0] = "MM";
						aScales[0] = 1.0 * nScaleFactor; // mm/100
						break;
					case sal_Unicode('p'):
					case sal_Unicode('P'):
						aCmpsL[0] = "pt";
						aCmpsU[0] = "PT";
						aScales[0] = (10.0 * nScaleFactor*2.54) / 72.; // mm/100

						aCmpsL[1] = "pc";
						aCmpsU[1] = "PC";
						aScales[1] = (10.0 * nScaleFactor*2.54) / 12.; // mm/100

						aCmpsL[2] = "px";
						aCmpsU[2] = "PX";
						aScales[2] = 0.28 * nScaleFactor; // mm/100
						break;
					}
				}
				else if (MeasureUnit::POINT == nTargetUnit)
				{
					if (rString[nPos] == 'p' || rString[nPos] == 'P')
					{
						aCmpsL[0] = "pt";
						aCmpsU[0] = "PT";
						aScales[0] = 1;
					}
				}

				if (aCmpsL[0] == nullptr)
					return false;

				double nScale = 0.;
				for (sal_uInt16 i = 0; i < 3; i++)
				{
					sal_Int32 nTmp = nPos; // come back to the initial position before each iteration
					const sal_Char *pL = aCmpsL[i];
					if (pL)
					{
						const sal_Char *pU = aCmpsU[i];
						while (nTmp < nLen && *pL)
						{
							sal_Unicode c = rString[nTmp];
							if (c != *pL && c != *pU)
								break;
							pL++;
							pU++;
							nTmp++;
						}
						if (!*pL && (nTmp == nLen || ' ' == rString[nTmp]))
						{
							nScale = aScales[i];
							break;
						}
					}
				}

				if (0. == nScale)
					return false;

				// TODO: check overflow
				if (nScale != 1.)
					nVal *= nScale;
			}
		}

		nVal += .5;
		if (bNeg)
			nVal = -nVal;

		if (nVal <= (double)nMin)
			rValue = nMin;
		else if (nVal >= (double)nMax)
			rValue = nMax;
		else
			rValue = (sal_Int32)nVal;

		return true;
	}

}