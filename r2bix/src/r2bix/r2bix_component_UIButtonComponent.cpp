#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIPannelComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mSize()
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



	void UIButtonComponent::SetSize( const uint32_t width, const uint32_t height )
	{
		mSize.Set( width, height );
	}



	void UIButtonComponent::SetCallback4CursorResponse( const CursorResponseCallbackT& callback )
	{
		mUIInputListener.SetCallback4CursorResponse( callback );
	}
	void UIButtonComponent::SetCallback4KeyResponse( const r2bix_input::eKeyCode key_code, const Callback4KeyResponseT& callback )
	{
		mUIInputListener.SetCallback4KeyResponse( key_code, callback );
	}
}