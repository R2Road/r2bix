#pragma once

#include "r2_SingletonWithStaticFunction.h"
#include "r2bix_table_TextureFrameAnimationTableBase.h"

namespace p2048table
{
	class TextureFrameAnimationTable : public r2bix_table::TextureFrameAnimationTableBase, public r2::SingletonWithStaticFunction<TextureFrameAnimationTable>
	{
	public:
		void Load() override;
	};
}