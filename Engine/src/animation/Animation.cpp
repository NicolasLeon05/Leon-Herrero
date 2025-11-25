#include "Animation.h"
#include "../clock/Clock.h"

#include <iostream>
using namespace std;

Animation::Animation()
{
	currentTime = 0.0f;
	lastTime = 0.0f;
	totalDuration = 0.0f;
	frames = std::vector<Frame>();
	currentFrameIndex = 0;
	lastFrameIndex = 0;
}

Animation::~Animation()
{

}

std::vector<Frame>& Animation::GetFrames()
{
	return frames;
}

int Animation::GetCurrentFrameIndex()
{
	return currentFrameIndex;
}

void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInSecs)
{
	if (!frames.empty())
		frames.clear();

	totalDuration = durationInSecs * 1000.0f;

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

void Animation::AddFrames(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float totalDurationInSecs, int framesCount)
{
	if (!frames.empty())
		frames.clear();

	totalDuration = totalDurationInSecs * 1000.0f;
	int offsetX = 0;
	for (int i = 0; i < framesCount; i++)
	{
		Frame newFrame;
		//Top right
		newFrame.frameCoords[3].u = (frameX + offsetX) / textureWidth;
		newFrame.frameCoords[3].v = (frameY + frameHeight) / textureHeight;
		//Bottom right
		newFrame.frameCoords[2].u = (frameX + offsetX) / textureWidth;
		newFrame.frameCoords[2].v = frameY / textureHeight;
		//Bottom left
		newFrame.frameCoords[1].u = (frameX + offsetX + frameWidth) / textureWidth;
		newFrame.frameCoords[1].v = frameY / textureHeight;
		//Top left
		newFrame.frameCoords[0].u = (frameX + offsetX + frameWidth) / textureWidth;
		newFrame.frameCoords[0].v = (frameY + frameHeight) / textureHeight;
		frames.push_back(newFrame);
		offsetX += frameWidth;
	}
}

void Animation::Update()
{
	currentTime += MyClock::GetDeltaTime();

	cout << endl << "currentTime: " << currentTime << endl;
	cout << "currentFrameIndex: " << currentFrameIndex << endl;

	while (currentTime > totalDuration)
		currentTime -= totalDuration;

	lastFrameIndex = currentFrameIndex;

	float frameDuration = totalDuration / frames.size();
	currentFrameIndex = static_cast<int>(currentTime / frameDuration);
}

void Animation::Reset()
{
	currentTime = 0.0f;
	lastTime = 0.0f;
	currentFrameIndex = 0;
	lastFrameIndex = -1;
}


bool Animation::HasFrameChanged()
{
	return lastFrameIndex != currentFrameIndex;
}