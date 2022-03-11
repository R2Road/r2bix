#pragma once

#include <memory>

#include "node/r2node_SceneNode.h"

namespace pmr
{
	class CompanyScene : public r2node::SceneNode
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static const char* const GetTitle() { return "Game : Mini Rogue( To do )"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;
	};
}