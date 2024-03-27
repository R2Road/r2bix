#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIPannelComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mUIPannelComponent( nullptr )
		, mUIInputListener()
	{}



	void UIButtonComponent::EnterProcess()
	{
		r2bix_node::Node* parent_node = GetOwnerNode().GetParentNode();

		//
		// Find UIPannelComponent
		//
		while( parent_node )
		{
			mUIPannelComponent = parent_node->GetComponent<UIPannelComponent>();
			if( mUIPannelComponent )
			{
				break;
			}

			parent_node = parent_node->GetParentNode();
		}

		//
		// Regist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->AddListener( &mUIInputListener );
		}
	}
	void UIButtonComponent::ExitProcess()
	{
		//
		// Unregist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->RemoveListener( &mUIInputListener );
		}
	}



	void UIButtonComponent::SetCallback4CursorResponse( const Callback4CursorResponseT& callback )
	{
		mUIInputListener.SetCallback4CursorResponse( callback );
	}
	void UIButtonComponent::SetCallback4KeyResponse( const Callback4KeyResponseT& callback )
	{
		mUIInputListener.SetCallback4KeyResponse( callback );
	}

	void UIButtonComponent::AddObservationKey( const r2bix_input::eKeyCode key_code )
	{
		mUIInputListener.AddObservationKey( key_code );
	}
}