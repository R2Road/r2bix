#pragma once

#include "r2bix_node_SceneNode.h"

#include "r2_TimerFloat.h"

namespace p2048
{
	class CompanyScene : public r2bix_node::SceneNode
	{
	private:
		CompanyScene( r2bix::Director& director );

	public:
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;

	private:
		r2::TimerFloat mChangeSceneTimer;
	};
}