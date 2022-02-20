#include "pch.h"
#include "r2render_TextureFrame.h"

namespace r2render
{
	TextureFrame::TextureFrame( const Texture* const texture ) :
		mTexture( texture )
		, mVisibleRect( 0, 0, texture->GetWidth(), texture->GetHeight() )
	{}

	Texture::ValueT TextureFrame::Get( const uint32_t x, const uint32_t y ) const
	{
		return mTexture->Get( x + mVisibleRect.GetOrigin().GetX(), y + mVisibleRect.GetOrigin().GetY() );
	}
}