#include "pch.h"
#include "Utils.h"
#include <string>
#include <Windows.h>

float Utils::Clamp(float v, float min, float max)
{
	if (v < min)
		return min;
	if (v > max)
		return max;
	return v;
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& v, const sf::FloatRect& rect)
{
	return sf::Vector2f(Clamp(v.x, rect.left, rect.left + rect.width), Clamp(v.y, rect.top, rect.top + rect.height));
}

sf::FloatRect Utils::ResizeRect(const sf::FloatRect& rect, const sf::Vector2f& delta)
{
	sf::FloatRect newRect = rect;
	newRect.width += delta.x;
	newRect.height += delta.y;

	newRect.left -= delta.x * 0.5f;
	newRect.top -= delta.y * 0.5f;

	return newRect;
}

float Utils::RandomValue()
{
	return (float)rand() / RAND_MAX;
}

float Utils::RandomRange(float min, float max)
{
	float value = RandomValue();
	value *= max - min;
	value += min;
	return value;
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	sf::Transform rotation;
	rotation.rotate(RandomRange(0.f, 360.f));
	return rotation * sf::Vector2f(1.f, 0.f);
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

int Utils::RandomRange(int min, int maxExclude)
{
	int range = maxExclude - min;
	int rand = std::rand() % range;
	rand += min;
	return rand;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect Width, Height
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f Utils::GetNormalize(const sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return { 0, 0 };
	return vec / mag;
}

void Utils::Normalize(sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag != 0.f)
	{
		vec /= mag;
	}
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::DistancePointAndLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2)
{
	float a = -(lineP1 - lineP2).y / (lineP1 - lineP2).x;

	return abs(a * p1.x + p1.y) / sqrt(a * a + 1.f);
}

float Utils::DistancePointAndLineSegmentMin(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2)
{

	std::initializer_list<float> values = { Distance(lineP1,p1), Distance(lineP2,p1),
		DistancePointAndLineSegment(p1,lineP1,lineP2) };

	return std::min(values);
}

float Utils::RadianToDegree(float radian)
{
	return radian / M_PI * 180.f;
}

float Utils::DegreeToRadian(float degree)
{
	return degree / 180 * M_PI;
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(atan2f(vec.y, vec.x));
}

float Utils::Angle(const sf::Vector2f& origin, const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
	return Angle(pos1 - origin, pos2 - origin);
}

float Utils::Angle(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return RadianToDegree(acosf((vec1.x * vec2.x + vec1.y * vec2.y) / (Magnitude(vec1) * Magnitude(vec2))));
}

void Utils::Rotate(sf::Vector2f& vec, float degree)
{
	vec = GetNormalize(sf::Transform().rotate(degree) * vec);
}

//t는 0.f ~ 1.f
float Utils::Lerp(float min, float max, float t)
{

	float v = min + (max - min) * Clamp(t, 0.f, 1.f);

	return v;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t)
{
	sf::Vector2f v = min + (max - min) * Clamp(t, 0.f, 1.f);

	return v;
}

std::list<sf::Vector2f> Utils::DressInRow(const sf::Vector2f& pos, const sf::Vector2f& direction, int count, float interval)
{
	std::list<sf::Vector2f> list;
	if (count == 0) { return list; }

	sf::Vector2f left = Utils::GetNormalize(direction);
	sf::Vector2f right = Utils::GetNormalize(direction);
	left = { -left.y,left.x };
	right = { right.y,-right.x };

	sf::Vector2f vecL = pos;
	sf::Vector2f vecR = pos;

	if (count % 2 == 1)
	{
		list.push_back(pos);
		for (int i = 0; i < count / 2; i++)
		{
			vecL += left * interval;
			vecR += right * interval;
			list.push_front(vecL);
			list.push_back(vecR);
		}
	}
	else
	{
		vecL += left * (0.5f * interval);
		vecR += right * (0.5f * interval);
		list.push_front(vecL);
		list.push_back(vecR);
		for (int i = 0; i < count / 2 - 1; i++)
		{
			vecL += left * interval;
			vecR += right * interval;
			list.push_front(vecL);
			list.push_back(vecR);
		}
	}
	return list;

}

std::list<sf::Vector2f> Utils::FanSpread(const sf::Vector2f& direction, int count, float angle)
{
	std::list<sf::Vector2f> list;
	sf::Vector2f normalDirec = Utils::GetNormalize(direction);
	if (count == 0) { return list; }
	if (0.f == fmodf(angle, 90))
	{
		sf::Vector2f left = normalDirec;
		sf::Vector2f right = normalDirec;

		if (count % 2 == 1)
		{
			list.push_back(normalDirec);
			for (int i = 0; i < count / 2; i++)
			{
				left = { -left.y,left.x };
				right = { right.y,-right.x };;
				list.push_front(left);
				list.push_back(right);
			}
		}
		else
		{
			left = sf::Transform().rotate(45) * left;
			right = sf::Transform().rotate(-45) * right;
			list.push_front(left);
			list.push_back(right);
			for (int i = 0; i < count / 2 - 1; i++)
			{
				left = { -left.y,left.x };
				right = { right.y,-right.x };;
				list.push_front(left);
				list.push_back(right);
			}
		}
	}
	else {
		sf::Vector2f left = normalDirec;
		sf::Vector2f right = normalDirec;

		if (count % 2 == 1)
		{
			list.push_back(normalDirec);
			for (int i = 0; i < count / 2; i++)
			{
				left = sf::Transform().rotate(angle) * left;
				right = sf::Transform().rotate(-angle) * right;
				list.push_front(left);
				list.push_back(right);
			}
		}
		else
		{
			left = sf::Transform().rotate(angle * 0.5) * left;
			right = sf::Transform().rotate(-angle * 0.5) * right;
			list.push_front(left);
			list.push_back(right);
			for (int i = 0; i < count / 2 - 1; i++)
			{
				left = sf::Transform().rotate(angle) * left;
				right = sf::Transform().rotate(-angle) * right;
				list.push_front(left);
				list.push_back(right);
			}
		}
	}
	return list;
}

void Utils::ElasticCollision(float& coord, float border, float cor)
{
	coord = border - (coord - border) * cor;
}

float Utils::GetElasticCollision(float coord, float border, float cor)
{
	return border - (coord - border) * cor;
}

bool Utils::IsCollideWithLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2, float radius)
{
	//두 점과의 거리 검사
	if (Magnitude(lineP1 - p1) <= radius || Magnitude(lineP2 - p1) <= radius)
	{
		return true;
	}

	//좌표계 원점 변환, 기준점 설정
	sf::Vector2f point1 = lineP1 - p1;
	sf::Vector2f point2 = lineP2 - p1;

	float angle1 = acosf(point1.x / Utils::Magnitude(point1));
	float angle2 = acosf(point2.x / Utils::Magnitude(point2));

	if (point1.y < 0)
		angle1 = 2.f * M_PI - angle1;
	if (point2.y < 0)
		angle2 = 2.f * M_PI - angle2;
	if (angle2 > angle1)
	{
		float temp = angle1;
		angle1 = angle2;
		angle2 = temp;

		sf::Vector2f temp2 = point1;
		point1 = point2;
		point2 = temp2;
	}

	//선분과 닿을 수 있는 각도인지 검사 후 거리 검사
	if (angle1 - angle2 >= M_PI)
	{
		sf::Vector2f inverseSlopePoint = { (point2 - point1).y, -(point2 - point1).x };
		float inverseSlopeAngle = acosf(inverseSlopePoint.x / Utils::Magnitude(inverseSlopePoint));
		if (inverseSlopePoint.y < 0)
			inverseSlopeAngle = 2.f * M_PI - inverseSlopeAngle;

		if (inverseSlopeAngle >= angle1 || inverseSlopeAngle <= angle2)
		{
			return (Utils::Magnitude(point2) * cosf(angle2 - inverseSlopeAngle + (inverseSlopeAngle <= angle2 ? 0.f : 2.f * M_PI))) <= radius;
		}
	}
	else
	{
		sf::Vector2f inverseSlopePoint = { (point1 - point2).y, -(point1 - point2).x };
		float inverseSlopeAngle = acosf(inverseSlopePoint.x / Utils::Magnitude(inverseSlopePoint));

		if (inverseSlopePoint.y < 0)
			inverseSlopeAngle = 2.f * M_PI - inverseSlopeAngle;

		if (inverseSlopeAngle <= angle1 && inverseSlopeAngle >= angle2)
		{
			return (Utils::Magnitude(point1) * cosf(angle1 - inverseSlopeAngle)) <= radius;
		}
	}
	return false;
}
std::wstring Utils::CP949ToWString(const std::string& str)
{
	if (str.empty()) return L"";
	// CP949 코드 페이지를 사용하여 변환
	int sizeNeeded = MultiByteToWideChar(949, 0, str.c_str(), (int)str.size(), NULL, 0);
	std::wstring wstrTo(sizeNeeded, 0);
	MultiByteToWideChar(949, 0, str.c_str(), (int)str.size(), &wstrTo[0], sizeNeeded);
	return wstrTo;
}

std::string Utils::WSTRINGToString(const std::wstring& var)
{
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(var);
}

std::string Utils::ConvertToRelativePath(const std::string& absolutePathW)
{
	//백슬래시를 슬래시로 변환
	std::string absolutePath = absolutePathW;

	std::replace(absolutePath.begin(), absolutePath.end(), '\\', '/');

	auto pos = absolutePath.find("tileset/");

	if (pos != std::string::npos)
	{
		// 'tileset'을 포함한 경로의 나머지 부분을 반환
		return absolutePath.substr(pos);
	}

	return absolutePathW; // 'tileset'이 없는 경우 원본 경로 반환
}

std::wstring Utils::OpenSaveFileDialog()
{
	OPENFILENAME ofn; // OPENFILENAME 구조체
	wchar_t szFileName[MAX_PATH] = L""; // 파일 이름을 저장할 배열
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"JSON Files (*.json)\0*.json\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"json";

	if (GetSaveFileName(&ofn)) // 파일 저장 대화 상자를 표시
		return ofn.lpstrFile; // 사용자가 지정한 파일 경로를 반환

	return L""; // 사용자가 취소하면 빈 문자열을 반환
}

