#include "r2bix_component_UIButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"

namespace r2bix_component
{
	UIButtonComponent::UIButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIButtonComponent>( owner_node )
		, mMyUIControlComponent( nullptr )
		, mCallback4CursorStatusChanged()
		, mCallback4KeyStatusChanged()
	{}



	void UIButtonComponent::EnterProcess()
	{
		//
		//
		//
		mMyUIControlComponent->SetCallback4CursorResponse( [this]( const r2bix_ui::eCursorStatus s )->bool
		{
			return mCallback4CursorStatusChanged( s );
		} );
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
}