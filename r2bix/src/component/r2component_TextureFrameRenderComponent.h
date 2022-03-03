#pragma once

#include "base/r2base_Component.h"

#include "r2/r2_RectInt.h"

namespace r2render
{
	class TextureFrame;
}

namespace r2component
{
	class TransformComponent;

	class TextureFrameRenderComponent : public r2base::Component
	{
	private:
		TextureFrameRenderComponent( r2base::Node& owner_node );

	public:
		static std::unique_ptr<TextureFrameRenderComponent> Create( r2base::Node& owner_node );

		//
		// Override
		//
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override;

		//
		// Setter
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mRect.Set( x, y, width, height );
		}
		void SetTextureFrame( r2render::TextureFrame* const texture_frame );

	public:
		r2component::TransformComponent* mTransformComponent;
	private:
		r2::RectInt mRect;
		r2render::TextureFrame* mTextureFrame;
	};
}