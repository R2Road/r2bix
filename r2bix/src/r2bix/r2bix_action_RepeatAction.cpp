#include "r2bix_action_RepeatAction.h"

#include "r2bix_node_Node.h"

namespace r2bix_action
{
	RepeatAction::RepeatAction() :
		mAction()
	{}

	std::unique_ptr<RepeatAction> RepeatAction::Create()
	{
		std::unique_ptr<RepeatAction> ret( new ( std::nothrow ) RepeatAction() );
		return ret;
	}

	void RepeatAction::Enter()
	{
		if( mAction )
		{
			mAction->SetOwnerNode( mOwnerNode );
			mAction->Enter();
		}
	}
	bool RepeatAction::Update( const float delta_time )
	{
		if( mAction )
		{
			if( !mAction->Update( delta_time ) )
			{
				mAction->Enter();
			}
		}

		return ( nullptr != mAction );
	}
}