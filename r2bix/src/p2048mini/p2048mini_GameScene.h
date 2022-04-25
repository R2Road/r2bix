#pragma once

#include "node/r2node_SceneNode.h"

#include "p2048mini/p2048mini_Stage.h"

namespace p2048mini
{
	class StageViewComponent;

	class GameScene : public r2node::SceneNode
	{
	private:
		GameScene( r2base::Director& director );

	public:
		static const char* const GetTitle() { return "Game : 2048mini( In Progress )"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;

	private:
		Stage mStage;
		p2048mini::StageViewComponent* mStageViewComponent;
	};
}