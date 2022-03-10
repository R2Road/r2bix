#pragma once

#include <memory>

#include "node/r2node_SceneNode.h"

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
		void Update() override;

	private:
		r2base::Node* mLabelNode;
		r2base::Node* mSpriteNode;
	};
}