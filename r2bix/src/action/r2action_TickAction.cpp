#include "pch.h"
#include "r2action_TickAction.h"

#include "base/r2base_Node.h"

namespace r2action
{
	TickAction::TickAction() : mTickLimit( 0u ), mCurrentTick( 0u )
	{}

	void TickAction::Enter()
	{
		mCurrentTick = 0u;
	}
	bool TickAction::Update()
	{
		++mCurrentTick;
		return mCurrentTick > mCurrentTick;
	}
}