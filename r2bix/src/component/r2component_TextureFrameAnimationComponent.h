#pragma once

#include <vector>

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

namespace r2render
{
	class TextureFrame;
}

namespace r2component
{
	class TextureFrameAnimationComponent : public r2base::Component
	{
	private:
		using TextureFrameContainerT = std::vector<r2render::TextureFrame*>;

		TextureFrameAnimationComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<TextureFrameAnimationComponent>::Get(); }
		static std::unique_ptr<TextureFrameAnimationComponent> Create( r2base::Node& owner_node );

		//
		//
		//
		void AddTextureFrame( const r2render::TextureFrame* const texture_frame );

	private:
		TextureFrameContainerT mTextureFrameContainer;
	};
}