#pragma once

namespace MeasureUnit{
	static const ::sal_Int16 APPFONT = (sal_Int16)17;
	static const ::sal_Int16 CM = (sal_Int16)3;
	static const ::sal_Int16 FOOT = (sal_Int16)13;
	static const ::sal_Int16 INCH = (sal_Int16)7;
	static const ::sal_Int16 INCH_1000TH = (sal_Int16)4;
	static const ::sal_Int16 INCH_100TH = (sal_Int16)5;
	static const ::sal_Int16 INCH_10TH = (sal_Int16)6;
	static const ::sal_Int16 KM = (sal_Int16)11;
	static const ::sal_Int16 M = (sal_Int16)10;
	static const ::sal_Int16 MILE = (sal_Int16)14;
	static const ::sal_Int16 MM = (sal_Int16)2;
	static const ::sal_Int16 MM_100TH = (sal_Int16)0;
	static const ::sal_Int16 MM_10TH = (sal_Int16)1;
	static const ::sal_Int16 PERCENT = (sal_Int16)15;
	static const ::sal_Int16 PICA = (sal_Int16)12;
	static const ::sal_Int16 PIXEL = (sal_Int16)16;
	static const ::sal_Int16 POINT = (sal_Int16)8;
	static const ::sal_Int16 SYSFONT = (sal_Int16)18;
	static const ::sal_Int16 TWIP = (sal_Int16)9;
}

namespace sax{

	class converter
	{
	public:
		converter();
		~converter();

		/** convert string to measure using optional min and max values*/
		static bool convertMeasure(sal_Int32& rValue,
			const wstring& rString,
			sal_Int16 nTargetUnit = MeasureUnit::MM_100TH,
			sal_Int32 nMin = SAL_MIN_INT32,
			sal_Int32 nMax = SAL_MAX_INT32);
	};

}