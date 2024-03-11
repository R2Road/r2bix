#pragma once

#include "r2_SingletonWithStaticFunction.h"
#include "r2bix_table_TextureTableBase.h"

namespace p2048table
{
	class TextureTable : public r2bix_table::TextureTableBase, public r2::SingletonWithStaticFunction<TextureTable>
	{
	public:
		void Load() override;
	};
}