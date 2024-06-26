#include "r2bix_component_RectComponent.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_component
{
	RectComponent::RectComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<RectComponent>( director, owner_node )
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



	void RectComponent::Set( const uint32_t width, const uint32_t height, const char fill_char, const short fill_color )
	{
		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( width, height, fill_char, fill_color );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}

	void RectComponent::Set( const uint32_t width, const uint32_t height, const char fill_char )
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
	void RectComponent::Set( const uint32_t width, const uint32_t height, const char* fill_str )
	{
		if( mCustomTextureComponent )
		{
			mCustomTextureComponent->GetTexture()->Reset( width, height, ' ' );
			mCustomTextureComponent->GetTexture()->FillStringAll( fill_str );
		}

		if( mTextureRenderComponent )
		{
			mTextureRenderComponent->ResetVisibleRect();
		}
	}
	void RectComponent::Set( const uint32_t width, const uint32_t height )
	{
		Set( width, height, '#' );
	}
}