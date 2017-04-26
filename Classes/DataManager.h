#pragma once

#include "cocos2d.h"
#include "cocos_custom.h"
#include <string>

namespace gameData
{
	static const char DIFFICULT_KEY[] = "difficult_key";

	const char TEST_LEVEL_NAME[] = "maps/test_map.tmx";
	const char FIRST_LEVEL_NAME[] = "maps/level_1.tmx";
	const char SECOND_LEVEL_NAME[] = "maps/level_2.tmx";
	const char THIRD_LEVEL_NAME[] = "maps/level_3.tmx";
}

enum Difficult
{
	EASY,
	NORMAL,
	HARD,
};

class CDataController
{
public:
	static void SetDifficult(Difficult difficult);
	static Difficult GetDifficult();

};