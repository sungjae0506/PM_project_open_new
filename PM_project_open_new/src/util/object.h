#pragma once
#include <GL/freeglut.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

const double EPSILON = 1e-4;
const double COLLISION_EPSILON = 1.5;
const double PI = 3.14159265358979;

enum CollisionType { None, Sliding, Crossing, In };

class Point
{
public:
	double x, y;
	Point();
	Point(double _x, double _y);
	Point(const Point& p);
	Point& operator()(double _x, double _y);
	Point& operator=(const Point& p);
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator-() const;
	Point operator*(double c) const;
	double operator*(const Point& p) const;
	Point operator/(double c) const;
	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(double c);
	Point& operator/=(double c);
};

Point operator*(double c, const Point& p);
double abs(const Point& p);

class Circle
{
public:
	Point center;
	double radius;

	Circle();
	Circle(const Point& c, double r);
	Circle(const Circle& c);
	Circle& operator=(const Circle& c);
	Circle operator+(const Point& p) const;
	Circle& operator+=(const Point& p);

	CollisionType collisionDetection(const Circle& c) const;

	void print(void) const;
};

class Line
{
public:
	Point point0, point1;
	Point norm, para;

	Line();
	Line(const Point& p0, const Point& p1, const Point& n);
	Line(const Line& l);
	Line& operator=(const Line& l);
	Line operator+(const Point& p) const;
	Line& operator+=(const Point& p);

	CollisionType collisionDetection(const Circle& c) const;
	CollisionType collisionDetection(const Line& l) const;

	void print(void) const;
};

class Lines
{
public:
	vector<Line> line;

	Lines();
	Lines(const Lines& ls);
	Lines& operator=(const Lines& ls);
	Lines operator+(const Point& p) const;
	Lines& operator+=(const Point& p);

	void addLine(const Line& l);

	vector<CollisionType> collisionDetection(const Circle& c) const;
	vector<CollisionType> collisionDetection(const Line& l) const;
	vector<vector<pair<CollisionType, Line>>> collisionDetection(const Lines& ls) const;

	void print(void) const;
};