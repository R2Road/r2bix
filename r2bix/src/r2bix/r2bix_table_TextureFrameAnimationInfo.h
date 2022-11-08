#pragma once

#include <vector>

#include "r2bix_animation_constant.h"

namespace r2bix_render
{
	class TextureFrame;
}

namespace r2bix_table
{
	class TextureFrameAnimationInfo
	{
	public:
		struct AnimationFrame
		{
			float TimeLimit;
			const r2bix_render::TextureFrame* Frame = nullptr;
		};
		struct Animation
		{
			r2bix_animation::eIndex Index;
			std::vector<AnimationFrame> Container;
		};
		using AnimationPackageT = std::vector<Animation>;

		TextureFrameAnimationInfo( AnimationPackageT&& animation_package );

		const AnimationPackageT& Get() const { return mAnimationPackage; }

	private:
		const AnimationPackageT mAnimationPackage;
	};
}