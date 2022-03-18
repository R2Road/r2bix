#pragma once

#include "base/r2base_Action.h"

#include "r2/r2_Timer_Float.h"

namespace r2action
{
	class BlinkAction : public r2base::Action
	{
	public:
		enum class eStep
		{
			Sleep,
			Show,
			Hide,
		};
	private:
		BlinkAction();

	public:
		static std::unique_ptr<BlinkAction> Create();

		//
		//
		//
		void Enter() override;
		bool Update( const float delta_time ) override;

		void SetStartStep( const eStep start_step )
		{
			mStartStep = start_step;
		}
		void SetTimeLimit4Show( const float time_limit )
		{
			mTimer4Show.reset( time_limit );
		}
		void SetTimeLimit4Hide( const float time_limit )
		{
			mTimer4Hide.reset( time_limit );
		}

	private:
		eStep mStartStep;
		eStep mCurrentStep;
		r2::Timer_Float mTimer4Show;
		r2::Timer_Float mTimer4Hide;
	};
}