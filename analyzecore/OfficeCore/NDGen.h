#pragma once

// Pair

class Pair
{
public:
	Pair() : nA(0), nB(0) {}
	Pair(long _nA, long _nB) : nA(_nA), nB(_nB) {}

	long                A() const { return nA; }
	long                B() const { return nB; }

	long&               A() { return nA; }
	long&               B() { return nB; }

	bool                operator == (const Pair& rPair) const;
	bool                operator != (const Pair& rPair) const;

protected:
	long                nA;
	long                nB;
};

inline bool Pair::operator == (const Pair& rPair) const
{
	return ((nA == rPair.nA) && (nB == rPair.nB));
}

inline bool Pair::operator != (const Pair& rPair) const
{
	return ((nA != rPair.nA) || (nB != rPair.nB));
}

// Point

class Point : public Pair
{
public:
	Point() {}
	Point(long nX, long nY) : Pair(nX, nY) {}

	long                X() const { return nA; }
	long                Y() const { return nB; }

	long&               X() { return nA; }
	long&               Y() { return nB; }

	void                Move(long nHorzMove, long nVertMove);

	void                RotateAround(long& rX, long& rY, short nOrientation) const;


	Point&              operator += (const Point& rPoint);
	Point&              operator -= (const Point& rPoint);
	Point&              operator *= (const long nVal);
	Point&              operator /= (const long nVal);

	friend inline Point operator+(const Point &rVal1, const Point &rVal2);
	friend inline Point operator-(const Point &rVal1, const Point &rVal2);
	friend inline Point operator*(const Point &rVal1, const long nVal2);
	friend inline Point operator/(const Point &rVal1, const long nVal2);

	long                getX() const { return X(); }
	long                getY() const { return Y(); }
	void                setX(long nX)  { X() = nX; }
	void                setY(long nY)  { Y() = nY; }
};

inline void Point::Move(long nHorzMove, long nVertMove)
{
	nA += nHorzMove;
	nB += nVertMove;
}

inline Point& Point::operator += (const Point& rPoint)
{
	nA += rPoint.nA;
	nB += rPoint.nB;
	return *this;
}

inline Point& Point::operator -= (const Point& rPoint)
{
	nA -= rPoint.nA;
	nB -= rPoint.nB;
	return *this;
}

inline Point& Point::operator *= (const long nVal)
{
	nA *= nVal;
	nB *= nVal;
	return *this;
}

inline Point& Point::operator /= (const long nVal)
{
	nA /= nVal;
	nB /= nVal;
	return *this;
}

inline Point operator+(const Point &rVal1, const Point &rVal2)
{
	return Point(rVal1.nA + rVal2.nA, rVal1.nB + rVal2.nB);
}

inline Point operator-(const Point &rVal1, const Point &rVal2)
{
	return Point(rVal1.nA - rVal2.nA, rVal1.nB - rVal2.nB);
}

inline Point operator*(const Point &rVal1, const long nVal2)
{
	return Point(rVal1.nA*nVal2, rVal1.nB*nVal2);
}

inline Point operator/(const Point &rVal1, const long nVal2)
{
	return Point(rVal1.nA / nVal2, rVal1.nB / nVal2);
}

// Size

class Size : public Pair
{
public:
	Size() {}
	Size(long nWidth, long nHeight) : Pair(nWidth, nHeight) {}

	long            Width() const  { return nA; }
	long            Height() const { return nB; }

	long&           Width()  { return nA; }
	long&           Height() { return nB; }

	long            getWidth() const { return Width(); }
	long            getHeight() const { return Height(); }
	void            setWidth(long nWidth)  { Width() = nWidth; }
	void            setHeight(long nHeight)  { Height() = nHeight; }
};

// Rectangle

class Rectangle
{
public:
	Rectangle();
	Rectangle(const Point& rLT, const Point& rRB);
	Rectangle(long nLeft, long nTop,
		long nRight, long nBottom);

	long Left() const { return nLeft; }
	long Right() const { return nRight; }
	long Top() const { return nTop; }
	long Bottom() const{ return nBottom; }

	long& Left() { return nLeft; }
	long& Right() { return nRight; }
	long& Top() { return nTop; }
	long& Bottom() { return nBottom; }

private:
	long nLeft;
	long nTop;
	long nRight;
	long nBottom;
};

inline Rectangle::Rectangle(const Point& rLT, const Point& rRB)
{
	nLeft = rLT.X();
	nTop = rLT.Y();
	nRight = rRB.X();
	nBottom = rRB.Y();
}

inline Rectangle::Rectangle(long _nLeft, long _nTop,
	long _nRight, long _nBottom)
{
	nLeft = _nLeft;
	nTop = _nTop;
	nRight = _nRight;
	nBottom = _nBottom;
}