#pragma once

#include "r2render_Texture.h"

namespace r2render
{
	class TextureFrame
	{
	public:
		explicit TextureFrame( const Texture* const texture );

		//
		//
		//
		const r2::RectInt& GetVisibleRect() const { return mVisibleRect; }
		Texture::ValueT Get( const uint32_t x, const uint32_t y ) const;

		//
		//
		//
		void SetVisibleRect( const r2::RectInt& rect ) { mVisibleRect = rect; }

	private:
		const Texture* const mTexture;
		r2::RectInt mVisibleRect;
	};
}