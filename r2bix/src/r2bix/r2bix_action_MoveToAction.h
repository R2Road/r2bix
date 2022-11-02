#pragma once

#include "r2bix_action_iAction.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_TimerFloat.h"

namespace r2bix_action
{
	class MoveToAction : public r2bix_action::iAction
	{
	private:
		MoveToAction();

	public:
		static std::unique_ptr<MoveToAction> Create();

		//
		//
		//
		void Enter() override;
		bool Update( const float delta_time ) override;

		//
		//
		//
		void SetEndPoint( const r2::PointInt end_point )
		{
			mEndPoint = end_point;
		}
		void SetTimeLimit( const float time_limit )
		{
			mTimer.SetLimitTime( time_limit );
		}

	private:
		r2::PointInt mMoveAmount;

		r2::PointInt mStartPoint;
		r2::PointInt mEndPoint;
		r2::TimerFloat mTimer;
	};
}