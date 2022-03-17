#include "pch.h"
#include "r2action_MoveByAction.h"

#include "base/r2base_Node.h"

namespace r2action
{
	MoveByAction::MoveByAction() : mTargetPoint(), mStartPoint()
	{}

	void MoveByAction::Enter()
	{
		mStartPoint = mOwnerNode->mTransformComponent->GetPosition();
	}
	bool MoveByAction::Update()
	{
		return false;
	}
}