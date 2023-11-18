#pragma once
#include "object.h"

class Range
{
public:
	Point point0, point1;
	Range();
	Range(double x0, double y0, double x1, double y1);
	Range(const Point& p0, const Point& p1);
	Range(const Range& r);
	Range& operator=(const Range& r);
	Range& operator()(double x0, double y0, double x1, double y1);
	Range& operator()(const Point& p0, const Point& p1);
	Range& operator()(const Range& r);
	Range operator+(const Point& p) const;
	Range& operator+=(const Point& r);
	bool contain(const Point& p);
	bool contain(const Range& r);
};

class Transform
{
public:
	Range range0, range1;
	Transform();
	Transform(const Range& r0, const Range& r1);
	Transform(const Transform& t);
	Transform& operator()(const Range& r0, const Range& r1);
	Point operator()(const Point& p);
	Range operator()(const Range& p);
};