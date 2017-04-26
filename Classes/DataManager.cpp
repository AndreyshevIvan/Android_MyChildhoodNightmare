#include "DataManager.h"

USING_NS_CC;
using namespace gameData;

void CDataController::SetDifficult(Difficult difficult)
{
	auto memory = UserDefault::getInstance();
	memory->setIntegerForKey(DIFFICULT_KEY, (int)difficult);
}

Difficult CDataController::GetDifficult()
{
	auto memory = UserDefault::getInstance();
	auto difficultNum = memory->getIntegerForKey(DIFFICULT_KEY, Difficult::EASY);
	Difficult difficult = Difficult(difficultNum);

	return difficult;
}