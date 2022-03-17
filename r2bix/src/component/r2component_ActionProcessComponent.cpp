#include "pch.h"
#include "r2component_ActionProcessComponent.h"

namespace r2component
{
	ActionProcessComponent::ActionProcessComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mActionContainer()
		, mCurrentActionIndicator( mActionContainer.end() )
		, mbStart( false )
	{}

	std::unique_ptr<ActionProcessComponent> ActionProcessComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<ActionProcessComponent> ret( new ( std::nothrow ) ActionProcessComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void ActionProcessComponent::StartAction()
	{
		mbStart = !mActionContainer.empty();

		if( !mbStart )
		{
			return;
		}

		mCurrentActionIndicator = mActionContainer.begin();
		( *mCurrentActionIndicator )->Enter( mOwnerNode );
	}
}