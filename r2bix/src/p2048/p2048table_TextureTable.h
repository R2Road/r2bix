#pragma once

#include "base/r2base_Singleton.h"

namespace r2render
{
	class TextureFrame;
}

namespace p2048table
{
	class TextureTable : public r2::SingleTon<TextureTable>
	{
	public:
		r2render::TextureFrame* const GetTitleTexture() const;
	};
}