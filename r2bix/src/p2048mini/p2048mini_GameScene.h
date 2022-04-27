#pragma once

#include "node/r2node_SceneNode.h"

#include "input/r2input_KeyboardInputCollector.h"
#include "input/r2input_KeyboardInputListener.h"

#include "p2048mini_Stage.h"

#include "r2/r2_Direction4.h"

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
			GameStop,
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
		void AddNumber( const uint32_t min, const uint32_t max );
		bool MoveNumber( const r2::Direction4::eState move_direction );

	private:
		eStep mStep;
		Stage mStage;
		p2048mini::StageViewComponent* mStageViewComponent;
		p2048mini::StageViewComponent* mStageViewComponent4Debug;

		int mScore;
		r2base::Node* mScoreLabel;
		r2base::Node* mGameOverNode;

		r2input::KeyboardInputCollector mKeyboardInputCollector;
		r2input::KeyboardInputListener mKeyboardInputListener;
	};
}