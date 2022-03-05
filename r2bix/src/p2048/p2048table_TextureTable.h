#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "r2/r2_Singleton.h"

namespace r2render
{
	class Texture;
	class TextureFrame;
}

namespace p2048table
{
	class TextureTable : public r2::SingleTon<TextureTable>
	{
	private:
		using ValueT = std::unique_ptr<r2render::Texture>;
		using TextureContainerT = std::unordered_map<std::string, ValueT>;

	public:
		TextureTable();

		void Load();


		r2render::TextureFrame* const GetTitleTexture() const;

	private:
		TextureContainerT mTextureContainer;
	};
}