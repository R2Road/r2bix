#pragma once

#include <memory>

#include "game/r2game_Scene.h"

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace p2048
{
	class CompanyScene : public r2game::Scene
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static r2base::NodeUp Create( r2base::Director& director );

		bool Do() override;
	};
}