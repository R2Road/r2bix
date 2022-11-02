#pragma once

#include "r2bix_action_iAction.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_TimerFloat.h"

namespace r2bix_action
{
	class MoveByAction : public r2bix_action::iAction
	{
	private:
		MoveByAction();

	public:
		static std::unique_ptr<MoveByAction> Create();

		//
		//
		//
		void Enter() override;
		bool Update( const float delta_time ) override;

		//
		//
		//
		void SetMoveAmount( const r2::PointInt move_amount )
		{
			mMoveAmount = move_amount;
		}
		void SetTimeLimit( const float time_limit )
		{
			mTimer.SetLimitTime( time_limit );
		}

	private:
		r2::PointInt mMoveAmount;

		r2::PointInt mStartPoint;
		r2::TimerFloat mTimer;
	};
}