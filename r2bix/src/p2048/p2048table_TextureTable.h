#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "r2/r2_Singleton.h"
#include "render/r2render_TextureFrame.h"

namespace r2render
{
	class Texture;
}

namespace p2048table
{
	class TextureTable : public r2::SingleTon<TextureTable>
	{
	private:
		using TextureValueT = std::unique_ptr<r2render::Texture>;
		using TextureContainerT = std::unordered_map<std::string, TextureValueT>;

		using TextureFrameValueT = std::unique_ptr<r2render::TextureFrame>;
		using TextureFrameContainerT = std::unordered_map<std::string, TextureFrameValueT>;

	public:
		TextureTable();

		void Load();

		bool AddTexture( const char* const key_name, const uint32_t width, const uint32_t height, const char fill_char );

		r2render::Texture* const GetTexture( const char* const key_name ) const;
		r2render::TextureFrame* const GetTextureFrame( const char* const key_name ) const;

	private:
		TextureContainerT mTextureContainer;
		TextureFrameContainerT mTextureFrameContainer;
	};
}