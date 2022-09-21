#pragma once

#include <memory>

#include "r2bix/r2node_SceneNode.h"

namespace p2048
{
	class TitleScene : public r2node::SceneNode
	{
	private:
		TitleScene( r2bix::Director& director );

	public:
		static r2node::SceneNodeUp Create( r2bix::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;

	private:
		r2base::Node* mLabelNode;
		r2base::Node* mSpriteNode;
	};
}