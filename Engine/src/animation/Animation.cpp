#include "Animation.h"
#include "../clock/Clock.h"

Animation::Animation()
{
	currentTime = 0.0f;
	lastTime = 0.0f;
	totalDuration = 0.0f;
	frames = std::vector<Frame>();
	currentFrameIndex = 0;
}

Animation::~Animation()
{
}

void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInSecs)
{
	totalDuration += durationInSecs * 1000.0f;

	Frame newFrame;
	newFrame.frameCoords[0].u = frameX / textureWidth;
	newFrame.frameCoords[0].v = (frameY + frameHeight) / textureHeight;

	newFrame.frameCoords[1].u = (frameX + frameWidth) / textureWidth;
	newFrame.frameCoords[1].v = (frameY + frameHeight) / textureHeight;

	newFrame.frameCoords[2].u = frameX / textureWidth;
	newFrame.frameCoords[2].v = frameY / textureHeight;

	newFrame.frameCoords[3].u = (frameX + frameWidth) / textureWidth;
	newFrame.frameCoords[3].v = frameY / textureHeight;

	frames.push_back(newFrame);
}

void Animation::AddFrames(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInSecs, int framesCount)
{
	totalDuration += durationInSecs * 1000.0f;
	int offsetX = 0;
	for (int i = 0; i < framesCount; i++)
	{
		Frame newFrame;
		newFrame.frameCoords[0].u = frameX + offsetX / textureWidth;
		newFrame.frameCoords[0].v = (frameY + frameHeight) / textureHeight;

		newFrame.frameCoords[1].u = (frameX + offsetX + frameWidth) / textureWidth;
		newFrame.frameCoords[1].v = (frameY + frameHeight) / textureHeight;

		newFrame.frameCoords[2].u = frameX + offsetX / textureWidth;
		newFrame.frameCoords[2].v = frameY / textureHeight;

		newFrame.frameCoords[3].u = (frameX + offsetX + frameWidth) / textureWidth;
		newFrame.frameCoords[3].v = frameY / textureHeight;

		frames.push_back(newFrame);
		offsetX += frameWidth;
	}
}

void Animation::Update()
{
	currentTime += MyClock::GetDeltaTime();

	while (currentTime > totalDuration)
		currentTime -= totalDuration;

	float frameDuration = totalDuration / frames.size();
	currentFrameIndex = static_cast<int>(currentTime / frameDuration);
}
