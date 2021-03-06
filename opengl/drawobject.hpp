#pragma once

#include "opengl/vertarray.hpp"

class linevertarray : public vertarray {
    public:
	linevertarray(uint32_t size, uint32_t isize = 0, uint32_t* ilist = nullptr)
	    : vertarray(size, isize, ilist)
	{
	}
	linevertarray()
	    : vertarray()
	{
	}
	void draw() const;
};

class linestripvertarray : public vertarray {
    public:
	linestripvertarray(uint32_t size, uint32_t isize = 0, uint32_t* ilist = nullptr)
	    : vertarray(size, isize, ilist)
	{
	}
	linestripvertarray()
	    : vertarray()
	{
	}
	void draw() const;
};

class pointvertarray : public vertarray {
    public:
	pointvertarray(uint32_t size, uint32_t isize = 0, uint32_t* ilist = nullptr)
	    : vertarray(size, isize, ilist)
	{
	}
	pointvertarray()
	    : vertarray()
	{
	}
	void draw() const;
};

class trianglevertarray : public vertarray {
    public:
	trianglevertarray(uint32_t size, uint32_t isize = 0, uint32_t* ilist = nullptr)
	    : vertarray(size, isize, ilist)
	{
	}
	trianglevertarray()
	    : vertarray()
	{
	}
	void draw() const;
};

//class spherevertarray : public vertarray {
//	const uint32_t N, M;
//	float cx, cy, cz, radi;
//
//    public:
//	spherevertarray(const float& cx, const float& cy, const float& cz, const float& radi, const uint32_t& N,
//	    const uint32_t& M);
//	void draw() const;
//	void setcenter(const float& x, const float& y, const float& z);
//	void setradi(const float& r);
//	void update();
//};
