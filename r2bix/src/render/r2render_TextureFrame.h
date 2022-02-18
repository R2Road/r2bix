#pragma once

#include "r2render_Texture.h"

namespace r2render
{
	class TextureFrame
	{
	public:
		explicit TextureFrame( const Texture* const texture );

	private:
		const Texture* const mTexture;
	};
}