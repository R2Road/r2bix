#pragma once

#include <unordered_map>

#include "r2bix_table_TextureFrameAnimationInfo.h"

namespace r2bix_table
{
	class TextureFrameAnimationTableBase
	{
	protected:
		using ContainerT = std::unordered_map<uint32_t, r2bix_table::TextureFrameAnimationInfo>;

	public:
		TextureFrameAnimationTableBase();

		virtual void Load() = 0;

		const r2bix_table::TextureFrameAnimationInfo& Get( const int index ) const;

	protected:
		ContainerT mContainer;
	};
}