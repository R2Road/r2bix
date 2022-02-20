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
		int GetWidth() const { return mVisibleRect.GetWidth(); }
		int GetHeight() const { return mVisibleRect.GetHeight(); }

		int GetMinX() const { return mVisibleRect.GetMinX(); }
		int GetMinY() const { return mVisibleRect.GetMinY(); }
		int GetMaxX() const { return mVisibleRect.GetMaxX(); }
		int GetMaxY() const { return mVisibleRect.GetMaxY(); }

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