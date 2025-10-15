#pragma once

struct TexCoords
{
	float u;
	float v;
};

class Frame
{
public:
	TexCoords frameCoords[4];
	Frame();
	~Frame();
};

