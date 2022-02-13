#pragma once

#include <memory>

#include "scene/GameScene.h"

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2game
{
	class RootScene : public GameScene
	{
	private:
		RootScene( r2base::Director& director );

	public:
		static r2base::NodeUp Create( r2base::Director& director );

		bool Do() override;
	};
}