#include "r2bix_component_UISimpleButtonComponent.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_UIControlComponent.h"

namespace r2bix_component
{
	UISimpleButtonComponent::UISimpleButtonComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UISimpleButtonComponent>( owner_node )
		, mMyUIControlComponent( nullptr )
		, mMyCustomTextureComponent( nullptr )
		, mMyTextureRenderComponent( nullptr )

		, mSlot4CursorStatusChanged_ViewProcess()
		, mSlot4KeyStatusChanged_ViewProcess()

		, mSlot4CursorStatusChanged()
		, mSlot4KeyStatusChanged()
	{
		mSlot4CursorStatusChanged_ViewProcess.SetCallback( [this]( r2bix_ui::eCursorStatus s ){
			switch( s )
			{
			case r2bix_ui::eCursorStatus::CursorOver:
				mMyCustomTextureComponent->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
				break;
			case r2bix_ui::eCursorStatus::CursorMove:
				mMyCustomTextureComponent->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
				break;
			case r2bix_ui::eCursorStatus::CursorLeave:
				mMyCustomTextureComponent->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
				break;
			}
		} );

		mSlot4KeyStatusChanged_ViewProcess.SetCallback( [this]( int, r2bix_ui::eKeyStatus s )->bool
		{
			switch( s )
			{
			case r2bix_ui::eKeyStatus::Push:
				mMyCustomTextureComponent->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightAqua );
				break;
			case r2bix_ui::eKeyStatus::Pressed:
				mMyCustomTextureComponent->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightYellow );
				break;
			case r2bix_ui::eKeyStatus::Release:
				mMyCustomTextureComponent->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightPurple );
				break;
			}

			return false;
		} );
	}



	void UISimpleButtonComponent::enterProcess()
	{
		mMyUIControlComponent->ConnectSlot4CursorResponse( &mSlot4CursorStatusChanged_ViewProcess );
		mMyUIControlComponent->ConnectSlot4KeyResponse( &mSlot4KeyStatusChanged_ViewProcess );

		mMyUIControlComponent->ConnectSlot4CursorResponse( &mSlot4CursorStatusChanged );
		mMyUIControlComponent->ConnectSlot4KeyResponse( &mSlot4KeyStatusChanged );
	}



	void UISimpleButtonComponent::SetCallback4CursorResponse( const Callback4CursorStatusChangedT& callback )
	{
		mSlot4CursorStatusChanged.SetCallback( callback );
	}
	void UISimpleButtonComponent::SetCallback4KeyResponse( const Callback4KeyStatusChangedT& callback )
	{
		mSlot4KeyStatusChanged.SetCallback( callback );
	}



	void UISimpleButtonComponent::SetSize( const int width, const int height, const char c )
	{
		mMyUIControlComponent->SetSize( width, height );
		mMyCustomTextureComponent->GetTexture()->Reset( width, height, c );
		mMyTextureRenderComponent->ResetVisibleRect();
	}
	void UISimpleButtonComponent::SetPivotPoint( const float x, const float y )
	{
		mMyUIControlComponent->SetPivotPoint( x, y );
		mMyTextureRenderComponent->SetPivotPoint( x, y );
	}
}