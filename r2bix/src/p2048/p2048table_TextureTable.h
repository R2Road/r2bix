#pragma once

#include "r2/r2_Singleton.h"

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