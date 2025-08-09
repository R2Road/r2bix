#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "r2bix_render_TextureFrame.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bix_table
{
	class TextureTableBase
	{
	protected:
		using TextureValueT = std::unique_ptr<r2bix_render::Texture>;
		using TextureContainerT = std::unordered_map<std::string, TextureValueT>;

		using TextureFrameValueT = std::unique_ptr<r2bix_render::TextureFrame>;
		using TextureFrameContainerT = std::unordered_map<std::string, TextureFrameValueT>;

	public:
		TextureTableBase();

		virtual void Load() = 0;

		bool AddTexture( const char* const key_name, const uint32_t width, const uint32_t height, const char fill_char );
		bool RemoveTexture( const char* const key_name );

		r2bix_render::Texture* const GetTexture( const char* const key_name ) const;
		r2bix_render::TextureFrame* const GetTextureFrame( const char* const key_name ) const;

	protected:
		TextureContainerT mTextureContainer;
		TextureFrameContainerT mTextureFrameContainer;
	};
}