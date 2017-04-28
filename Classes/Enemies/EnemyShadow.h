#pragma once

#include "cocos_custom.h"
#include "Puppet.h"
#include "Enemies/Enemy.h"

class CEnemyShadow : public CEnemy
{
public:

protected:
	bool InitTactics() override;
	bool InitBody() override;

	void UpdateWorldInfo(float delta) override;
	void ChooseTactic() override;
	void DoTactic(float delta) override;

};