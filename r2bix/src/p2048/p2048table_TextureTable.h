#pragma once

#include "r2/r2_SingletonWithStaticVariable.h"
#include "r2bix/r2bix_table_TextureTableBase.h"

namespace p2048table
{
	class TextureTable : public r2bix_table::TextureTableBase, public r2::SingletonWithStaticVariable<TextureTable>
	{
	public:
		void Load() override;
	};
}