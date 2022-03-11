#pragma once

#include <vector>

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

namespace r2component
{
	class TextureFrameRenderComponent;
}

namespace r2render
{
	class TextureFrame;
}

namespace r2component
{
	class TextureFrameAnimationComponent : public r2base::Component
	{
	private:
		using TextureFrameContainerT = std::vector<const r2render::TextureFrame*>;

		TextureFrameAnimationComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<TextureFrameAnimationComponent>::Get(); }
		static std::unique_ptr<TextureFrameAnimationComponent> Create( r2base::Node& owner_node );

		//
		//
		//
		void SetTextureFrameRenderComponent( r2component::TextureFrameRenderComponent* const texture_frame_render_component )
		{
			mTextureFrameRenderComponent = texture_frame_render_component;
		}

		//
		//
		//
		void AddTextureFrame( const r2render::TextureFrame* const texture_frame );

	private:
		r2component::TextureFrameRenderComponent* mTextureFrameRenderComponent;
		TextureFrameContainerT mTextureFrameContainer;
	};
}