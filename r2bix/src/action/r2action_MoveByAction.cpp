#include "pch.h"
#include "r2action_MoveByAction.h"

#include "base/r2base_Node.h"

namespace r2action
{
	MoveByAction::MoveByAction() :
		mTargetPoint()
		, mStartPoint()
		, mEndPoint()
		, mTimer( 1.f )
	{}

	void MoveByAction::Enter()
	{
		mStartPoint = mOwnerNode->mTransformComponent->GetPosition();
		mEndPoint = mStartPoint + mTargetPoint;

		mTimer.reset();
	}
	bool MoveByAction::Update( const float delta_time )
	{
		if( mTimer.update( delta_time ) )
		{
			mOwnerNode->mTransformComponent->SetPosition(
				mStartPoint.GetX() + ( mTargetPoint.GetX() * mTimer.getElapsedTimeRate() )
				, mStartPoint.GetY() + ( mTargetPoint.GetY() * mTimer.getElapsedTimeRate() )
			);
		}
		else
		{
			mOwnerNode->mTransformComponent->SetPosition( mStartPoint + mTargetPoint );
		}

		return mTimer.isAlive();
	}
}