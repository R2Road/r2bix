#pragma once

#include "r2bix_action_iAction.h"

#include "r2/r2_TimerFloat.h"

namespace r2bix_action
{
	class DelayAction : public r2bix_action::iAction
	{
	private:
		DelayAction();

	public:
		static std::unique_ptr<DelayAction> Create();

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
		r2::TimerFloat mTimer;
	};
}