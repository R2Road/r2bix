#pragma once

#include <memory>

#include "r2bix/r2node_SceneNode.h"

namespace psnake
{
	class CompanyScene : public r2node::SceneNode
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static const char* const GetTitle() { return "Game : Snake( In Progress )"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;
	};
}