#pragma once

#include "cocos2d.h"
#include "cocos_custom.h"
#include <string>

namespace DataKeys
{
	const char DIFFICULT_KEY[] = "difficult_key";
}

enum struct Difficult
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