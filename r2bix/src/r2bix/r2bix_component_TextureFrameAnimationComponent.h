#pragma once

#include <vector>

#include "r2bix_component_Component.h"

#include "r2/r2_TimerFloat.h"
#include "r2bix_table_TextureFrameAnimationInfo.h"

namespace r2bix_component
{
	class TextureFrameRenderComponent;
}

namespace r2bix_render
{
	class TextureFrame;
}

namespace r2bix_component
{
	class TextureFrameAnimationComponent : public r2bix_component::Component<TextureFrameAnimationComponent>
	{
	private:
		struct AnimationFrame
		{
			r2::TimerFloat Timer;
			const r2bix_render::TextureFrame* Frame = nullptr;
		};
		struct Animation
		{
			r2bix_animation::eIndex Index;
			std::vector<AnimationFrame> Container;
		};
		using AnimationPackageT = std::vector<Animation>;

	public:
		TextureFrameAnimationComponent( r2bix_node::Node& owner_node );

		//
		//
		//
		void Update( const float delta_time ) override;

		//
		//
		//
		r2bix_component::TextureFrameRenderComponent* const GetTextureFrameRenderComponent()
		{
			return mTextureFrameRenderComponent;
		}
		void SetTextureFrameRenderComponent( r2bix_component::TextureFrameRenderComponent* const texture_frame_render_component )
		{
			mTextureFrameRenderComponent = texture_frame_render_component;
		}

		//
		//
		//
		void LoadAnimation( const r2bix_table::TextureFrameAnimationInfo& info );
		bool HasAnimation( const r2bix_animation::eIndex animation_index ) const;
		void RunAnimation_Once( const r2bix_animation::eIndex animation_index );
		void RunAnimation_Repeat( const r2bix_animation::eIndex animation_index );
		bool IsRunning() const { return mAnimationPackage.end() != mCurrentAnimation; }
		void StopAnimation();
		const r2bix_animation::eIndex GetCurrentAnimationIndex() const;

	private:
		r2bix_component::TextureFrameRenderComponent* mTextureFrameRenderComponent;

		bool mbRepeat;
		AnimationPackageT mAnimationPackage;
		AnimationPackageT::iterator mCurrentAnimation;
		uint32_t mCurrentAnimationFrameIndex;
	};
}