#include "Frame.h"

Frame::Frame()
{
	frameCoords[0].u = 0.0f;
	frameCoords[0].v = 1.0f;

	frameCoords[1].u = 1.0f;
	frameCoords[1].v = 1.0f;

	frameCoords[2].u = 0.0f;
	frameCoords[2].v = 0.0f;

	frameCoords[3].u = 1.0f;
	frameCoords[3].v = 0.0f;
}

Frame::~Frame()
{
}