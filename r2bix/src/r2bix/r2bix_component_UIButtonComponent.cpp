#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UIPannelComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mUIPannelComponent( nullptr )
		, mMyUIControlComponent( nullptr )

		, mCursorState( r2bix_ui::eCursorStatus::None )

		, mCallback4CursorStatusChanged()
		, mCallback4KeyStatusChanged()
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
			//mUIPannelComponent->AddListener( &mUIInputListener );
		}

		//
		//
		//
		mMyUIControlComponent->SetCallback4CursorResponse( [this]( const r2bix_ui::eCursorStatus s )->bool
		{
			return mCallback4CursorStatusChanged( s );
		} );
	}
	void UIButtonComponent::ExitProcess()
	{
		//
		// Unregist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			//mUIPannelComponent->RemoveListener( &mUIInputListener );
		}
	}



	int UIButtonComponent::GetWidth() const
	{
		return mMyUIControlComponent->GetWidth();
	}
	int UIButtonComponent::GetHeight() const
	{
		return mMyUIControlComponent->GetHeight();
	}

	void UIButtonComponent::SetSize( const uint32_t width, const uint32_t height )
	{
		mMyUIControlComponent->SetSize( width, height );
	}



	void UIButtonComponent::SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback )
	{
		mCallback4CursorStatusChanged = callback;
	}
	void UIButtonComponent::SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback )
	{
		mCallback4KeyStatusChanged = callback;
	}

	void UIButtonComponent::AddObservationKey( const r2bix_input::eKeyCode key_code )
	{
		//mUIInputListener->AddObservationKey( key_code );
	}
}