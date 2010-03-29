#pragma once

#include <map>

template <class T>
class Handle
{
		

	T * t_;
	unsigned int ref_;

public:
	Handle()
	{
		ref_ = 1;
		t_ = new T();
	}

	Handle(const T * t)
	{
		ref_ = 1;
		t_ = t;
	}

	Handle(const Handle & h)
	{
		h.ref_++;
		ref_ = h.ref_;
		t_ = h.t_;
	}

	T * GetPtr()
	{
		return t_;
	}

	
};