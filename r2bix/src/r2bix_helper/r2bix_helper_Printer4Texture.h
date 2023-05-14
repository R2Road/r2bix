#pragma once

namespace r2bix_render
{
	class Texture;
	class TextureFrame;
}

namespace r2bix_helper
{
	class Printer4Texture
	{
	private:
		Printer4Texture() = delete;

	public:
		static void DrawTexture( const r2bix_render::Texture& texture );
		static void DrawTextureCharacter( const r2bix_render::Texture& texture );
		static void DrawTextureColor( const r2bix_render::Texture& texture );
		static void DrawTextureDisuse( const r2bix_render::Texture& texture );

		static void DrawTextureFrame( const r2bix_render::TextureFrame& frame );
	};
}