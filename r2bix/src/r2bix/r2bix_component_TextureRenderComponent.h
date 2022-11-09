#pragma once

#include "r2bix_component_Component.h"

#include "r2bix_ColorMaskOption.h"

#include "r2/r2_PointFloat.h"
#include "r2/r2_RectInt.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bix_component
{
	class TextureRenderComponent : public r2bix_component::Component<TextureRenderComponent>
	{
	public:
		TextureRenderComponent( r2bix_node::Node& owner_node );

		//
		// Override
		//
		void Render( const r2bix_render::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset ) override;

		//
		// Getter
		//
		const r2bix_render::Texture* const GetTexture() const
		{
			return mTexture;
		}
		r2::RectInt GetRect() const
		{
			return mVisibleRect;
		}

		//
		// Setter
		//
		void SetPivotPoint( const float x, const float y );
		void SetTexture( const r2bix_render::Texture* const texture );
		void ResetVisibleRect();
		void SetVisibleRectForced( const int x, const int y, const int width, const int height )
		{
			mVisibleRect.Set( x, y, width, height );
		}
		void MoveRectOrigin( const int move_x, const int move_y )
		{
			mVisibleRect.MoveOrigin( move_x, move_y );
		}

	private:
		r2::PointFloat mPivotPoint;
		r2::RectInt mVisibleRect;
		const r2bix_render::Texture* mTexture;
		r2bix::ColorMaskOption mColorMaskOption;
	};
}