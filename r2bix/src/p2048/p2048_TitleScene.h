#pragma once

#include <memory>

#include "r2bix_node_SceneNode.h"

namespace p2048
{
	class TitleScene : public r2bix_node::SceneNode
	{
	private:
		TitleScene( r2bix::Director& director );

	public:
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;

	private:
		r2bix_node::Node* mLabelNode;
		r2bix_node::Node* mSpriteNode;
	};
}