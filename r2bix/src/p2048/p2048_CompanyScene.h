#pragma once

#include "r2bix/r2node_SceneNode.h"

#include "r2/r2_Timer_Float.h"

namespace p2048
{
	class CompanyScene : public r2node::SceneNode
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;

	private:
		r2::Timer_Float mChangeSceneTimer;
	};
}