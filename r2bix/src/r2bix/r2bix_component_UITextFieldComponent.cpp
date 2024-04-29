#include "r2bix_component_UITextFieldComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
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
		if( nullptr == custom_texture_component )
		{
			R2ASSERT( nullptr != custom_texture_component, "" );
			return;
		}

		mCustomTextureComponent = custom_texture_component;
	}

	void UITextFieldComponent::SetTextureRenderComponent( r2bix_component::TextureRenderComponent* const texture_render_component )
	{
		if( nullptr == texture_render_component )
		{
			R2ASSERT( nullptr != texture_render_component, "" );
			return;
		}

		mTextureRenderComponent = texture_render_component;
	}



	int UITextFieldComponent::GetLength() const
	{
		return mUIControlComponent->GetWidth();
	}
	void UITextFieldComponent::SetLength( const int length )
	{
		mUIControlComponent->SetSize( length, 1 );
		mCustomTextureComponent->GetTexture()->Reset( length, 1 );
		mTextureRenderComponent->ResetVisibleRect();
	}



	void UITextFieldComponent::SetText( const char* str )
	{
		mCustomTextureComponent->GetTexture()->FillString( str );
	}
}