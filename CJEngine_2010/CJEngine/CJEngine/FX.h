#pragma once

#include "./Resource.h"

class FX : public Resource
{
	unsigned int frag_shader_;
	unsigned int vert_shader_;
	bool frag_;
	bool vert_;
	unsigned int shader_prog_;

public:
	FX(const char * vert_fx, const char * frag_fx);
	~FX(void);

	void Enable();
	void Disable();
};
