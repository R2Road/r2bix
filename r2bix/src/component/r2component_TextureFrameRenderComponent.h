#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

#include "r2/r2_RectInt.h"

namespace r2render
{
	class TextureFrame;
}

namespace r2component
{
	class TextureFrameRenderComponent : public r2base::Component
	{
	private:
		TextureFrameRenderComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<TextureFrameRenderComponent>::Get(); }
		static std::unique_ptr<TextureFrameRenderComponent> Create( r2base::Node& owner_node );

		//
		// Override
		//
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt offset ) override;

		//
		// Setter
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mRect.Set( x, y, width, height );
		}
		void SetTextureFrame( r2render::TextureFrame* const texture_frame );

	private:
		r2::RectInt mRect;
		r2render::TextureFrame* mTextureFrame;
	};
}