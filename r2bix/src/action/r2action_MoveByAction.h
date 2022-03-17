#pragma once

#include "base/r2base_Action.h"
#include "r2/r2_Point_Int.h"

namespace r2action
{
	class MoveByAction : public r2base::Action
	{
	public:
		MoveByAction();

		//
		//
		//
		void Update() {}

		//
		//
		//
		void SetTargetPoint( const r2::PointInt target_point )
		{
			mTargetPoint = target_point;
		}

	private:
		r2::PointInt mTargetPoint;
	};
}