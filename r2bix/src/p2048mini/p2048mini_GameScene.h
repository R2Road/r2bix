#pragma once

#include "node/r2node_SceneNode.h"

#include "input/r2input_KeyboardInputCollector.h"
#include "input/r2input_KeyboardInputListener.h"
#include "p2048mini/p2048mini_Stage.h"

namespace p2048mini
{
	class StageViewComponent;

	class GameScene : public r2node::SceneNode
	{
	private:
		enum class eStep
		{
			GameReady,
			GameStart,
			GameUpdate,
			GameEnd,
		};

		GameScene( r2base::Director& director );

	public:
		static const char* const GetTitle() { return "Game : 2048mini( In Progress )"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;

	private:
		eStep mStep;
		Stage mStage;
		p2048mini::StageViewComponent* mStageViewComponent;

		r2input::KeyboardInputCollector mKeyboardInputCollector;
		r2input::KeyboardInputListener mKeyboardInputListener;
	};
}