#pragma once

#include <unordered_map>
#include <vector>

#include "animation/r2animation_constant.h"

namespace r2render
{
	class TextureFrame;
}

namespace r2base
{
	class TextureFrameAnimationTableBase
	{
	protected:
		struct AnimationFrame
		{
			float TimeLimit;
			const r2render::TextureFrame* Frame = nullptr;
		};
		struct Animation
		{
			r2animation::eIndex Index;
			std::vector<AnimationFrame> Container;
		};
		struct AnimationPackage
		{
			std::vector<Animation> Container;
		};
		using ContainerT = std::unordered_map<uint32_t, AnimationPackage>;

	public:
		TextureFrameAnimationTableBase();

		virtual void Load() = 0;

		const AnimationPackage& Get( const int index ) const;

	protected:
		ContainerT mContainer;
	};
}