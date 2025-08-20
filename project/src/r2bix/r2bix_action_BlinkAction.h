#pragma once

#include "r2bix_action_iAction.h"

#include "r2_timer_float.hpp"

namespace r2bix_action
{
	class BlinkAction : public r2bix_action::iAction
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

		void SetTimeLimit( const float time_limit )
		{
			mTimer.SetLimitTime( time_limit );
		}

	private:
		bool mbLastVisible;
		r2::TimerFloat mTimer;
	};
}