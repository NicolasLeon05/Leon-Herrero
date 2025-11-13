#pragma once
#include "Frame.h"
#include <vector>

#include "../EngineAPI.h"

class Animation
{
private:
	float currentTime;
	float lastTime;
	float totalDuration;
	std::vector<Frame> frames;
	int currentFrameIndex;
	int lastFrameIndex;

public:
	ENGINE_API Animation();
	ENGINE_API ~Animation();

	std::vector<Frame> GetFrames();

	int GetCurrentFrameIndex();

	ENGINE_API void AddFrame(float frameX, float frameY,
		float frameWidth, float frameHeight,
		float textureWidth, float textureHeight,
		float durationInSecs);

	ENGINE_API void AddFrames(float frameX, float frameY,
		float frameWidth, float frameHeight,
		float textureWidth, float textureHeight,
		float durationInSecs, int framesCount);

	ENGINE_API void Update();

	bool HasFrameChanged();
};