#include "r2bix_component_HollowRectComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	HollowRectComponent::HollowRectComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<HollowRectComponent>( owner_node )
		, mCustomTextureComponent( nullptr )
		, mTextureRenderComponent( nullptr )
	{}



	int HollowRectComponent::GetWidth() const
	{
		return mCustomTextureComponent->GetTexture()->GetWidth();
	}
	int HollowRectComponent::GetHeight() const
	{
		return mCustomTextureComponent->GetTexture()->GetHeight();
	}



	void HollowRectComponent::Set( const r2::Vector2& pivot, const uint32_t width, const uint32_t height, const char rect_char, const char hollow_char )
	{
		if( !mCustomTextureComponent )
		{
			return;
		}

		if( !mTextureRenderComponent )
		{
			return;
		}

		fillTexture( width, height, rect_char, hollow_char );

		mTextureRenderComponent->SetPivotPoint( pivot.x, pivot.y );
		mTextureRenderComponent->ResetVisibleRect();
	}
	void HollowRectComponent::Set( const uint32_t width, const uint32_t height, const char rect_char, const char hollow_char )
	{
		if( !mCustomTextureComponent )
		{
			return;
		}

		if( !mTextureRenderComponent )
		{
			return;
		}

		fillTexture( width, height, rect_char, hollow_char );

		mTextureRenderComponent->ResetVisibleRect();
	}
	void HollowRectComponent::Set( const uint32_t width, const uint32_t height )
	{
		Set( width, height, '#', ' ' );
	}

	void HollowRectComponent::fillTexture( const uint32_t width, const uint32_t height, const char rect_char, const char hollow_char )
	{
		mCustomTextureComponent->GetTexture()->Reset( width, height, rect_char );

		for( uint32_t y = 1, endy = height - 1; endy > y; ++y )
		{
			for( uint32_t x = 1, endx = width - 1; endx > x; ++x )
			{
				mCustomTextureComponent->GetTexture()->FillCharacter( x, y, hollow_char );
			}
		}
	}
}