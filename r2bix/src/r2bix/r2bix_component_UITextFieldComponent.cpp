#include "r2bix_component_UITextFieldComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_UIControlComponent.h"

namespace r2bix_component
{
	UITextFieldComponent::UITextFieldComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<UITextFieldComponent>( director, owner_node )
		, mUIControlComponent( nullptr )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
		, mSlot4KeyResponse()
		, mText()
	{
		mSlot4KeyResponse.SetCallback( [this]( const int k, const r2bix_ui::eKeyStatus s )->bool
		{
			if( 0 == k && r2bix_ui::eKeyStatus::Push == s )
			{
				const auto screen_position = (
					  GetOwnerNode().mTransformComponent->GetScreenPosition()
					- r2::PointInt( mUIControlComponent->GetPivotPoint().x * mUIControlComponent->GetWidth(), 0 )
				);

				//
				// Start Input Mode
				//
				SetText( GetDirector().StartTextInputMode(
					  static_cast<short>( screen_position.GetX() )
					, static_cast<short>( screen_position.GetY() )
					, GetLength() ).c_str()
				);
			}

			return true;
		} );
	}



	void UITextFieldComponent::SetUIControlComponent( r2bix_component::UIControlComponent* const ui_control_component )
	{
		if( nullptr == ui_control_component )
		{
			R2ASSERT( nullptr != ui_control_component, "" );
			return;
		}

		mUIControlComponent = ui_control_component;

		mUIControlComponent->ConnectSlot4KeyResponse( &mSlot4KeyResponse );
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
		mText = str;

		mCustomTextureComponent->GetTexture()->FillCharacterAll( ' ' );
		mCustomTextureComponent->GetTexture()->FillString( str );
	}



	void UITextFieldComponent::Set( const int length, const char* str )
	{
		SetLength( length );
		SetText( str );
	}
}