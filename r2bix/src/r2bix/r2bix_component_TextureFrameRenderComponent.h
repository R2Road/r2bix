#pragma once

#include "r2_RectInt.h"
#include "r2_SignalSlot.h"
#include "r2_Vector2.h"

#include "r2bix_ColorMaskOption.h"

#include "r2bix_component_Component.h"

namespace r2bix_render
{
	class TextureFrame;
}

namespace r2bix_component
{
	class TextureFrameRenderComponent : public r2bix_component::Component<TextureFrameRenderComponent>
	{
	public:
		using Slot4PivotChangedT = r2::Slot<void( float, float )>;



		TextureFrameRenderComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
		void Render( const r2bix::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset ) override;



		//
		// Getter
		//
		const r2bix_render::TextureFrame* const GetTextureFrame() const
		{
			return mTextureFrame;
		}

		//
		// Setter
		//
		void SetPivot( const float x, const float y );
		void SetTextureFrame( const r2bix_render::TextureFrame* const texture_frame );
		void SetVisibleRectForced( const int x, const int y, const int width, const int height )
		{
			mVisibleRect.Set( x, y, width, height );
		}
		void MoveRectOriginForced( const int move_x, const int move_y )
		{
			mVisibleRect.MoveOrigin( move_x, move_y );
		}
	private:
		void resetVisibleRect();



	private:
		Slot4PivotChangedT mSlot4PivotChanged;
		r2::Vector2 mPivotVector;
		r2::RectInt mVisibleRect;
		const r2bix_render::TextureFrame* mTextureFrame;
		r2bix::ColorMaskOption mColorMaskOption;
	};
}