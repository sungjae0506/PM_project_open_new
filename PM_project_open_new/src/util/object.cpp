#include "object.h"

// /////////////////////////////////////////////////////////////////////////////////////

Point::Point()
{
	x = y = 0.0;
}
Point::Point(double _x, double _y)
{
	x = _x, y = _y;
}
Point::Point(const Point& p)
{
	x = p.x, y = p.y;
}
Point& Point::operator()(double _x, double _y)
{
	x = _x, y = _y;
	return *this;
}
Point& Point::operator=(const Point& p)
{
	x = p.x, y = p.y;
	return *this;
}
Point Point::operator+(const Point& p) const
{
	return Point(x + p.x, y + p.y);
}
Point Point::operator-(const Point& p) const
{
	return Point(x - p.x, y - p.y);
}
Point Point::operator-() const
{
	return Point(-x, -y);
}
Point Point::operator*(double c) const
{
	return Point(c * x, c * y);
}
double Point::operator*(const Point& p) const
{
	return (x * p.x + y * p.y);
}
Point Point::operator/(double c) const
{
	return Point(x / c, y / c);
}
Point& Point::operator+=(const Point& p)
{
	return (*this) = (*this) + p;
}
Point& Point::operator-=(const Point& p)
{
	return (*this) = (*this) - p;
}
Point& Point::operator*=(double c)
{
	return (*this) = (*this) * c;
}
Point& Point::operator/=(double c)
{
	return (*this) = (*this) / c;
}
Point operator*(double c, const Point &p)
{
	return p * c;
}
double abs(const Point &p)
{
	return sqrt((p.x * p.x) + (p.y * p.y));
}

// /////////////////////////////////////////////////////////////////////////////////////

Circle::Circle()
{
}
Circle::Circle(const Point& c, double r)
{
	center = c;
	radius = r;
}
Circle::Circle(const Circle& c)
{
	center = c.center;
	radius = c.radius;
}
Circle& Circle::operator=(const Circle& c)
{
	center = c.center;
	radius = c.radius;
	return *this;
}
Circle Circle::operator+(const Point& p) const
{
	return Circle(center + p, radius);
}
Circle& Circle::operator+=(const Point& p)
{
	return (*this) = (*this) + p;
}
CollisionType Circle::collisionDetection(const Circle& c) const
{
	if (abs(center - c.center) > radius + c.radius + COLLISION_EPSILON)
		return None;
	if (abs(abs(center - c.center) > radius + c.radius - COLLISION_EPSILON))
		return Sliding;
	if (abs(center - c.center) > abs(radius - c.radius) - COLLISION_EPSILON)
		return Crossing;
	return In;
}
void Circle::print(void) const
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; ++i)
		glVertex2f(radius * cos(i / 180.0 * PI) + center.x, radius * sin(i / 180.0 * PI) + center.y);
	glEnd();
}

// /////////////////////////////////////////////////////////////////////////////////////

Line::Line()
{
}
Line::Line(const Point& p0, const Point& p1, const Point& n)
{
	point0 = p0;
	point1 = p1;
	norm = n;
	para = (p1 - p0) / abs(p1 - p0);
}
Line::Line(const Line& l)
{
	point0 = l.point0;
	point1 = l.point1;
	norm = l.norm;
	para = l.para;
}
Line& Line::operator=(const Line& l)
{
	point0 = l.point0;
	point1 = l.point1;
	norm = l.norm;
	para = l.para;
	return *this;
}
Line Line::operator+(const Point& p) const
{
	return Line(point0 + p, point1 + p, norm);
}
Line& Line::operator+=(const Point& p)
{
	return (*this) = (*this) + p;
}
CollisionType Line::collisionDetection(const Circle& c) const
{
	if (norm * (point0 - c.center) > EPSILON)
		return None;
	if (abs((norm * (c.center - point0) - c.radius)) < COLLISION_EPSILON)
	{
		if (((c.center - point0) * para > COLLISION_EPSILON && (c.center - point1) * para < -COLLISION_EPSILON))
			return Sliding;
		return None;
	}
	else if (norm * (c.center - point0) < c.radius - COLLISION_EPSILON)
	{
		if (((c.center - point0) * para) * ((c.center - point1) * para) < 0.0 || min(abs(c.center - point0), abs(c.center - point1)) < c.radius - COLLISION_EPSILON)
		{
			if (max(abs(c.center - point0), abs(c.center - point1)) < c.radius - COLLISION_EPSILON)
				return In;
			return Crossing;
		}
		return None;
	}
	return None;
}
CollisionType Line::collisionDetection(const Line& l) const
{
	if (norm * l.norm > EPSILON)
		return None;
	//if (((l.point0 - point0) * para < COLLISION_EPSILON && (l.point1 - point0) * para < COLLISION_EPSILON) || ((l.point0 - point1) * para > -COLLISION_EPSILON && (l.point1 - point1) * para > -COLLISION_EPSILON))
	//	return None;
	if (((l.point0 - point0) * para < COLLISION_EPSILON * 0.1 && (l.point1 - point0) * para < COLLISION_EPSILON * 0.1) || ((l.point0 - point1) * para > -COLLISION_EPSILON * 0.1 && (l.point1 - point1) * para > -COLLISION_EPSILON * 0.1))
		return None;
	if (abs((l.point0 - point0) * norm) < COLLISION_EPSILON && abs((l.point1 - point0) * norm) < COLLISION_EPSILON) // ?? l.point0°¡ 2°³
		return Sliding;
	//if (((l.point0 - point0) * norm) * ((l.point1 - point0) * norm) < 0.0)
	//if ((((l.point0 - point0) * norm) < -COLLISION_EPSILON && ((l.point1 - point0) * norm) > COLLISION_EPSILON) || (((l.point0 - point0) * norm) > COLLISION_EPSILON && ((l.point1 - point0) * norm) < -COLLISION_EPSILON))
	//	return Crossing;
	
	if ((((l.point0 - point0) * norm) < -COLLISION_EPSILON && ((l.point1 - point0) * norm) >= 0.0) || (((l.point0 - point0) * norm) >= 0.0 && ((l.point1 - point0) * norm) < -COLLISION_EPSILON))
	{
		float a, b, p, q, s;
		a = abs((l.point0 - point0) * norm);
		b = abs((l.point1 - point0) * norm);
		p = (l.point0 - point0) * para;
		q = (l.point1 - point0) * para;
		s = (a * p + b * q) / (a + b);
		if (COLLISION_EPSILON <= s && s <= abs(point1 - point0) - COLLISION_EPSILON)
			return Crossing;
	}
	if (((l.point0 - point0) * norm) < 0.0 && ((l.point1 - point0) * norm) < 0.0 && ((((l.point0 - point0) * norm) >= -COLLISION_EPSILON) || (((l.point1 - point0) * norm) >= -COLLISION_EPSILON)))
		return In;
	return None;
}

void Line::print(void) const
{
	if (norm.y > 0)
		glColor3f(1.0, 0.0, 0.0);
	if (norm.y < 0)
		glColor3f(0.0, 0.0, 1.0);
	if (norm.x < 0)
		glColor3f(0.0, 1.0, 0.0);
	if (norm.x > 0)
		glColor3f(1.0, 1.0, 0.0);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(point0.x, point0.y);
	glVertex2f(point1.x, point1.y);
	glEnd();
	//printf("%lf %lf %lf %lf\n", point0.x, point0.y, point1.x, point1.y);
}

// /////////////////////////////////////////////////////////////////////////////////////

Lines::Lines()
{
}
Lines::Lines(const Lines& ls)
{
	line.resize(ls.line.size());
	copy(ls.line.begin(), ls.line.end(), line.begin());
}
Lines& Lines::operator=(const Lines& ls)
{
	line.resize(ls.line.size());
	copy(ls.line.begin(), ls.line.end(), line.begin());
	return *this;
}
Lines Lines::operator+(const Point& p) const
{
	Lines ls(*this);
	for (auto& i : ls.line)
		i += p;
	return ls;
}
Lines& Lines::operator+=(const Point& p)
{
	return (*this) = (*this) + p;
}
void Lines::addLine(const Line& l)
{
	line.push_back(l);
}
vector<CollisionType> Lines::collisionDetection(const Circle& c) const
{
	vector<CollisionType> col(line.size());
	for (int i = 0; i < line.size(); ++i)
		col[i] = line[i].collisionDetection(c);
	return col;
}
vector<CollisionType> Lines::collisionDetection(const Line& l) const
{
	vector<CollisionType> col(line.size());
	for (int i = 0; i < line.size(); ++i)
		col[i] = line[i].collisionDetection(l);
	return col;
}
vector<vector<pair<CollisionType, Line>>> Lines::collisionDetection(const Lines& ls) const
{
	vector<vector<pair<CollisionType, Line>>> col(line.size());
	for (int i = 0; i < line.size(); ++i)
	{
		for (int j = 0; j < ls.line.size(); ++j)
		{
			auto r = line[i].collisionDetection(ls.line[j]);
			if (r != None)
				col[i].push_back({r, ls.line[j]});
		}
	}
	return col;
}
void Lines::print(void) const
{
	for (auto &l : line)
		l.print();
}

double dist(const Point& p0, const Point& p1)
{
	return abs(p1 - p0);
}
double dist(const Circle& c, const Point& p)
{
	return max(abs(p - c.center) - c.radius, 0.0);
}

double dist(const Line& l, const Point& p)
{
	return max((p - l.point0) * l.norm, 0.0);
}