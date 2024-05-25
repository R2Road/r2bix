#include "r2bix_component_HollowRectComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	HollowRectComponent::HollowRectComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<HollowRectComponent>( director, owner_node )
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



	void HollowRectComponent::Set( const uint32_t width, const uint32_t height, const char rect_char, const short rect_color, const char hollow_char, const short hollow_color )
	{
		if( !mCustomTextureComponent )
		{
			return;
		}

		if( !mTextureRenderComponent )
		{
			return;
		}

		fillTexture( width, height, rect_char, rect_color, hollow_char, hollow_color );

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

		//
		// FG_White( 7 ) | BG_Black( 0 ) == 7
		//
		fillTexture( width, height, rect_char, 7, hollow_char, 7 );

		mTextureRenderComponent->ResetVisibleRect();
	}
	void HollowRectComponent::Set( const uint32_t width, const uint32_t height )
	{
		Set( width, height, '#', ' ' );
	}

	void HollowRectComponent::fillTexture( const uint32_t width, const uint32_t height, const char rect_char, const short rect_color, const char hollow_char, const short hollow_color )
	{
		mCustomTextureComponent->GetTexture()->Reset( width, height, rect_char, rect_color );

		for( uint32_t y = 1, endy = height - 1; endy > y; ++y )
		{
			for( uint32_t x = 1, endx = width - 1; endx > x; ++x )
			{
				mCustomTextureComponent->GetTexture()->FillCharacter( x, y, hollow_char );
				mCustomTextureComponent->GetTexture()->FillColor( x, y, hollow_color );
			}
		}
	}
}