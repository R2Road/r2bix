#pragma once

#include "r2/r2_SingletonWithStaticVariable.h"
#include "r2bix/r2bix_table_TextureFrameAnimationTableBase.h"

namespace p2048table
{
	class TextureFrameAnimationTable : public r2bix_table::TextureFrameAnimationTableBase, public r2::SingletonWithStaticVariable<TextureFrameAnimationTable>
	{
	public:
		void Load() override;
	};
}