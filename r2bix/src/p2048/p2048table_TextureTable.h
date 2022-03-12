#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "r2/r2_Singleton.h"
#include "base/r2base_TextureTableBase.h"

namespace r2render
{
	class Texture;
}

namespace p2048table
{
	class TextureTable : public r2base::TextureTableBase, public r2::SingleTon<TextureTable>
	{
	public:
		void Load() override;
	};
}