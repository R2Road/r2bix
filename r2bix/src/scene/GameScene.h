#pragma once

#include "base/r2base_iNode.h"

namespace r2base
{
	class Director;
}

class GameScene : public r2base::iNode
{
public:
	GameScene( r2base::Director& director );

	bool Do() override;
};