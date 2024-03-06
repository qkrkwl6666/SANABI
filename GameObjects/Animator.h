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
	sf::IntRect texCoord; // �ؽ�ó�� ��ġ ���� ����

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
	int fps = 30; // 1�ʿ� ��������
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
	//  <��ȯ��(�Ű�����)> �⺻�� nullptr
	std::function<void()> action;
};

class Animator
{
protected:
	std::unordered_map<std::string, AnimationClip> clips;

	std::queue<std::string> queue;
	std::list<AnimaitionEvent> eventList;
	float speed = 1.f;

	// ���� ����ϰ��ִ� �ִϸ��̼� Ŭ��
	AnimationClip* currentClip = nullptr; 

	int totalFrame = 0; // ��ü ������
	int currentFrame = -1; // ��ü�������� ���� ������

	float clipDuration = 0.f; // �ִϸ��̼� Ŭ�� ���� �ð�
	float accumTime = 0.f; // ���� Ÿ�ӽð�

	int addFrame = 1;

	sf::Sprite* target;

public:
	Animator();
	~Animator();

	void AddEvent(const std::string& clipId, int frame , std::function<void()> action);
	void ClearEvent();

	bool isPlaying = false;
	void AddClip(const AnimationClip& clip); // �����̳ʿ� Ŭ�� �߰�

	const std::string& GetCurrentClipId() 
	{ 
		return currentClip->id; 
	}

	bool IsPlaying() const { return isPlaying; }

	void SetTarget(sf::Sprite* t) { target = t; }// Ÿ�� ����
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

