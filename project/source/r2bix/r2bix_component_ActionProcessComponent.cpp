#include "r2bix_component_ActionProcessComponent.h"

namespace r2bix_component
{
	ActionProcessComponent::ActionProcessComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<ActionProcessComponent>( director, owner_node )
		, mAction()
		, mbStart( false )
	{}

	void ActionProcessComponent::StartAction()
	{
		mbStart = ( nullptr != mAction );
		if( mbStart )
		{
			mAction->SetOwnerNode( &mOwnerNode );
			mAction->Enter();
		}
	}

	void ActionProcessComponent::updateProcess( const float delta_time )
	{
		if( !mbStart )
		{
			return;
		}

		mbStart = mAction->Update( delta_time );
	}
}