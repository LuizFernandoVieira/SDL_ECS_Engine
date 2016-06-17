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
	Vec2& operator+= (const Vec2& v);
	Vec2& operator-= (const Vec2& v);
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
	void rotate(float angle);
	// Rotacionar vetor em torno do ponto vec2 enviado
	void rotate(Vec2 vec2, float module, float angle);

	float x() const { return x_; }
	float y() const { return y_; }
	void x(float x) { x_ = x; }
	void y(float y) { y_ = y; }

private:
	float x_;
	float y_;
};

// Distancia entre dois pontos
float Distance(Vec2 v1, Vec2 v2);
// Inclinação da reta formada por dois pontos
float LineInclination(Vec2 v1, Vec2 v2);
// Magnitude de vetor
float Magnitude(const Vec2& p);
// Normalizar vetor (magnitude 1)
Vec2 Normalize(const Vec2& p);
// Produto escalar de vetores
float Dot(const Vec2& a, const Vec2& b);

float ProjectX(float module, float angle);
float ProjectY(float module, float angle);

#endif