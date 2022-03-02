#pragma once

#include <memory>

#include "node/r2node_SceneNode.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

namespace r2node
{
	class LabelNode;
	class SpriteNode;
}

namespace r2render
{
	class Camera;
}

namespace p2048
{
	class CompanyScene : public r2node::Scene
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static r2base::NodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update() override;

	private:
		r2render::Camera mCamera;
		r2render::Texture mRenderTarget;

		r2node::LabelNode* mLabelNode;
		r2node::SpriteNode* mSpriteNode;
	};
}