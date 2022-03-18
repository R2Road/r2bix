#include "pch.h"
#include "r2action_MoveByAction.h"

#include "base/r2base_Node.h"

namespace r2action
{
	MoveByAction::MoveByAction() :
		mMoveAmount()
		, mStartPoint()
		, mTimer( 1.f )
	{}

	void MoveByAction::Enter()
	{
		mStartPoint = mOwnerNode->mTransformComponent->GetPosition();
		mTimer.reset();
	}
	bool MoveByAction::Update( const float delta_time )
	{
		if( mTimer.update( delta_time ) )
		{
			mOwnerNode->mTransformComponent->SetPosition(
				mStartPoint.GetX() + ( mMoveAmount.GetX() * mTimer.getElapsedTimeRate() )
				, mStartPoint.GetY() + ( mMoveAmount.GetY() * mTimer.getElapsedTimeRate() )
			);
		}
		else
		{
			mOwnerNode->mTransformComponent->SetPosition( mStartPoint + mMoveAmount );
		}

		return mTimer.isAlive();
	}
}