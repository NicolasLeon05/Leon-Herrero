#pragma once
#include "Frame.h"
#include <vector>

class Animation
{
private:
	float currentTime;
	float lastTime;
	float totalDuration;
	std::vector<Frame> frames;
	int currentFrameIndex;

public:
	Animation();
	~Animation();

	void AddFrame(float frameX, float frameY,
		float frameWidth, float frameHeight,
		float textureWidth, float textureHeight,
		float durationInSecs);

	void AddFrames(float frameX, float frameY,
		float frameWidth, float frameHeight,
		float textureWidth, float textureHeight,
		float durationInSecs, int framesCount);

	void Update();
};