#pragma once

#include "r2_singleton_with_static_method.hpp"
#include "r2bix_table_TextureTableBase.h"

namespace p2048table
{
	class TextureTable : public r2bix_table::TextureTableBase, public r2::SingletonWithStaticMethod<TextureTable>
	{
	public:
		void Load() override;
	};
}