#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:
	Point();
	Point(float x, float y);
	// Operações de Point com Point
	// Point operator+ (const Point& p);
	// Point operator- (const Point& p);
	// Point operator* (const Point& p);
	// Point operator/ (const Point& p);
	// // Operações de Point com escalar
	// Point operator+ (const float& e) const;
	// Point operator- (const float& e) const;
	// Point operator* (const float& e) const;
	// Point operator/ (const float& e) const;
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
private:
	float x_;
	float y_;
};

#endif