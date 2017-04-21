#include "DataManager.h"

USING_NS_CC;
using namespace DataKeys;

void CDataController::SetDifficult(Difficult difficult)
{
	auto memory = UserDefault::getInstance();
	memory->setIntegerForKey(DIFFICULT_KEY, (int)difficult);
}

Difficult CDataController::GetDifficult()
{
	auto memory = UserDefault::getInstance();
	auto difficultNum = memory->getIntegerForKey(DIFFICULT_KEY, (int)Difficult::EASY);
	Difficult difficult = Difficult(difficultNum);

	return difficult;
}