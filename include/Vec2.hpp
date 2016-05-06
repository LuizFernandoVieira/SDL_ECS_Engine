#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>

#define PI 3.14159265359

class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);

	// Operações de Point com Point
	Vec2 operator+ (const Vec2& v);
	Vec2 operator- (const Vec2& v);
	// Point operator* (const Point& p);
	// Point operator/ (const Point& p);

	// // Operações de Point com escalar
	// Point operator+ (const float& e) const;
	// Point operator- (const float& e) const;
	Vec2 operator* (const float& e) const;
	// Point operator/ (const float& e) const;

	// Operações Lógicas
	bool operator== (const Vec2& v) const;
	bool operator!= (const Vec2& v) const;

	// Rotacionar vetor em torno da origem
	void Rotate(float angle);
	// Rotacionar vetor em torno do ponto vec2 enviado
	void Rotate(Vec2 vec2, float module, float angle);

	float x() const { return x_; }
	float y() const { return y_; }
	void x(float x) { x_ = x; }
	void y(float y) { y_ = y; }

private:
	float x_;
	float y_;
};


float Distance(Vec2 v1, Vec2 v2);

// Inclinação da reta formada por dois pontos
float LineInclination(Vec2 v1, Vec2 v2);


#endif