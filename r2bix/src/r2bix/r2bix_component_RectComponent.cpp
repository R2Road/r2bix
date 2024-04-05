#include "r2bix_component_RectComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	RectComponent::RectComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<RectComponent>( owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
	{}



	int RectComponent::GetWidth() const
	{
		return mCustomTextureComponent->GetTexture()->GetWidth();
	}
	int RectComponent::GetHeight() const
	{
		return mCustomTextureComponent->GetTexture()->GetHeight();
	}



	void RectComponent::Set( const r2::Vector2& pivot, const uint32_t width, const uint32_t height, const char fill_char )
	{
		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( width, height, fill_char );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->SetPivotPoint( pivot.x, pivot.y );
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
	void RectComponent::SetSize( const uint32_t width, const uint32_t height, const char fill_char )
	{
		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( width, height, fill_char );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
	void RectComponent::SetSize( const uint32_t width, const uint32_t height )
	{
		SetSize( width, height, '#' );
	}
}