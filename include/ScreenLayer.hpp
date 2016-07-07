#ifndef	SCREENLAYER_HPP
#define	SCREENLAYER_HPP

#include <stdio.h>
#include "Vec2.hpp"

class ScreenLayer{
public:
	ScreenLayer(){
		SetParallax(0, 0);
		SetOffset(0, 0);
		SetScale(1, 1);
	};

	virtual void Render(){};

	Vec2 GetParallax() 	{ return Vec2(parallax_x, parallax_y);}
	Vec2 GetScale() 	{ return Vec2(scale_x, scale_y);}

	void SetScale(float x, float y){
		scale_x = x;
		scale_y = y;
	}

	void SetParallax(float x, float y){
		parallax_x = x;
		parallax_y = y;
	}

	void SetOffset(float x, float y){
		offset_x = x;
		offset_y = y;
	}

protected:
	float parallax_x;
	float parallax_y;

	float scale_x;
	float scale_y;

	float offset_x;
	float offset_y;
};

#endif