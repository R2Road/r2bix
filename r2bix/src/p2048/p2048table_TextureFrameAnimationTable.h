#pragma once

#include "r2/r2_Singleton.h"
#include "r2bix/r2base_TextureFrameAnimationTableBase.h"

namespace p2048table
{
	class TextureFrameAnimationTable : public r2base::TextureFrameAnimationTableBase, public r2::SingleTon<TextureFrameAnimationTable>
	{
	public:
		void Load() override;
	};
}