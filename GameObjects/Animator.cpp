#include "pch.h"
#include "Animator.h"
#include "rapidcsv.h"

Animator::Animator()
{

}

Animator::~Animator()
{
	
}

void Animator::AddEvent(const std::string& clipId, int frame , std::function<void()> action)
{
	eventList.push_back({ clipId , frame , action});
}

void Animator::ClearEvent()
{
	eventList.clear();
}

void Animator::AddClip(const AnimationClip& clip)
{
	if (clips.find(clip.id) == clips.end())
	{
		//clips.insert({ clip.id , clip });
		clips[clip.id] = clip;
	}
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::Update(float dt)
{
	if (this == nullptr)
	{
		return;
	}

	// 플레이가 아닌경우에는 return
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt * speed;
	
	if (accumTime < clipDuration)
	{
		return;
	}
	accumTime = 0.f;
	++currentFrame;

	if (currentFrame == totalFrame)
	{
		if (!queue.empty())
		{
			std::string id = queue.front();
			queue.pop();
			Play(id, false);
			return;
		}

		switch (currentClip->loopType)
		{
			case AnimationLoopTypes::SINGLE:
				currentFrame = totalFrame - 1;
				isPlaying = false;
				break;
			case AnimationLoopTypes::LOOP:
				currentFrame = 0;
				break;
		}
	}

	for (auto& event : eventList)
	{
		if (currentClip->id == event.clipId && currentFrame == event.frame)
		{
			if (event.action != nullptr)
			{
				event.action();
			}
		}
	}

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	target->setTexture(frame.GetTexture());

	target->setTextureRect(frame.texCoord);
}

void Animator::Falling()
{
	Play("Player_Falling");
}

void Animator::Play(const std::string& clipId, bool clearQueue)
{
	if (clearQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}

	// clipId가 find할때만 작동
	isPlaying = true;
	accumTime = 0.f;
	currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->GetTotalFrame();
	clipDuration = 1.f / currentClip->fps; // 0.333
	SetFrame(currentClip->frames[0]);
	
}

void Animator::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	//rapidcsv::Document doc(filePath , rapidcsv::LabelParams(0, -1));

	rapidcsv::Document doc(filePath);

	id = doc.GetCell<std::string>(0, 0);
	//id = filePath;
	fps = doc.GetCell<int>(1, 0);

	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	for (int i = 3; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);

		frames.push_back({ row[0] , {std::stoi(row[1]),std::stoi(row[2]),
			std::stoi(row[3]),std::stoi(row[4])} });
	}

	return true;
}
