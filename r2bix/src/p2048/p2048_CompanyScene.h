#pragma once

#include <memory>

#include "node/r2node_SceneNode.h"

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

namespace r2node
{
	class LabelNode;
	class SpriteNode;

	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

namespace r2render
{
	class Camera;
}

namespace p2048
{
	class CompanyScene : public r2node::SceneNode
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static const char* const GetTitle() { return "Game : 2048( In Progress )"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update() override;

	private:
		r2node::LabelNode* mLabelNode;
		r2node::SpriteNode* mSpriteNode;
	};
}