#pragma once

enum class AnimationLoopTypes
{
	SINGLE,
	LOOP,
	PINGPONG,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord; // 텍스처의 위치 정보 저장

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		: textureId(id) , texCoord(coord)
	{

	}

	const sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	std::string id;
	int fps = 30; // 1초에 몇프레임
	AnimationLoopTypes loopType = AnimationLoopTypes::SINGLE;
	std::vector<AnimationFrame> frames;

	int GetTotalFrame() const
	{
		return frames.size();
	}

	bool loadFromFile(const std::string& filePath);
};

struct AnimaitionEvent
{
	std::string clipId;
	int frame = 0;
	//  <반환형(매개변수)> 기본값 nullptr
	std::function<void()> action;
};

class Animator
{
protected:
	std::unordered_map<std::string, AnimationClip> clips;

	std::queue<std::string> queue;
	std::list<AnimaitionEvent> eventList;
	float speed = 1.f;

	// 현재 재생하고있는 애니메이션 클립
	AnimationClip* currentClip = nullptr; 

	int totalFrame = 0; // 전체 프레임
	int currentFrame = -1; // 전체프레임중 현재 프레임

	float clipDuration = 0.f; // 애니메이션 클립 변경 시간
	float accumTime = 0.f; // 현재 타임시간

	int addFrame = 1;

	sf::Sprite* target;

public:
	Animator();
	~Animator();

	void AddEvent(const std::string& clipId, int frame , std::function<void()> action);
	void ClearEvent();

	bool isPlaying = false;
	void AddClip(const AnimationClip& clip); // 컨테이너에 클립 추가

	const std::string& GetCurrentClipId() 
	{ 
		return currentClip->id; 
	}

	bool IsPlaying() const { return isPlaying; }

	void SetTarget(sf::Sprite* t) { target = t; }// 타겟 설정
	sf::Sprite* GetTarget() { return target; }

	float GetSpeed() const { return speed; }
	void SetSpeed(float s) { speed = s; }

	void Update(float dt);
	void Play(const std::string& clipId , bool clearQueue = true);
	void PlayQueue(const std::string& clipId);
	void Stop();
	void SetFrame(const AnimationFrame& frame);

	void Falling();

	//AnimationClip* GetClip(const std::string& clipId)
	//{
	//	auto it = clips.find(clipId);
	//	if (it != clips.end())
	//	{
	//		return &(it->second);
	//	}
	//	return nullptr;
	//}
};

