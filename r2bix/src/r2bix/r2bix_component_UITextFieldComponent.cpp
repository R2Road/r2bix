#include "r2bix_component_UITextFieldComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"

namespace r2bix_component
{
	UITextFieldComponent::UITextFieldComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UITextFieldComponent>( owner_node )
		, mUIControlComponent( nullptr )
		, mCustomTextureComponent( nullptr )
	{}



	void UITextFieldComponent::SetUIControlComponent( r2bix_component::UIControlComponent* const ui_control_component )
	{
		if( nullptr == ui_control_component )
		{
			R2ASSERT( nullptr != ui_control_component, "" );
			return;
		}

		mUIControlComponent = ui_control_component;
	}

	void UITextFieldComponent::SetCustomTextureComponent( r2bix_component::CustomTextureComponent* const custom_texture_component )
	{
		if( nullptr == mCustomTextureComponent )
		{
			R2ASSERT( nullptr != mCustomTextureComponent, "" );
			return;
		}

		mCustomTextureComponent = custom_texture_component;
	}



	int UITextFieldComponent::GetLength() const
	{
		return mUIControlComponent->GetWidth();
	}
	void UITextFieldComponent::SetLength( const int length )
	{
		mUIControlComponent->SetSize( length, 1 );
	}
}