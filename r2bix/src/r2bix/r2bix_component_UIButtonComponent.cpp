#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mMyUIControlComponent( nullptr )
		, mSlot4CursorStatusChanged()
		, mSlot4KeyStatusChanged()
	{}



	void UIButtonComponent::enterProcess()
	{
		//
		// 
		//
		mMyUIControlComponent->ConnectSlot4CursorResponse( &mSlot4CursorStatusChanged );
		mMyUIControlComponent->ConnectSlot4KeyResponse( &mSlot4KeyStatusChanged );
	}



	void UIButtonComponent::SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback )
	{
		mSlot4CursorStatusChanged.SetCallback( callback );
	}
	void UIButtonComponent::SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback )
	{
		mSlot4KeyStatusChanged.SetCallback( callback );
	}
}