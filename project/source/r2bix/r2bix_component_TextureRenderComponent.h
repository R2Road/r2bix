#pragma once

#include "r2_rect_int.hpp"
#include "r2_signal_slot.hpp"
#include "r2_vector2.hpp"

#include "r2bix_ColorMaskOption.h"

#include "r2bix_component_Component.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bix_component
{
	class TextureRenderComponent : public r2bix_component::Component<TextureRenderComponent>
	{
	public:
		using Slot4PivotChangedT = r2::Slot<void( float, float )>;


		TextureRenderComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
		bool initProcess() override;
		void Render_deprecated( const r2bix::Camera_deprecated* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset ) override;



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
		void SetPivot( const float x, const float y );
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
		Slot4PivotChangedT mSlot4PivotChanged;
		r2::Vector2 mPivotVector;
		r2::RectInt mVisibleRect;
		const r2bix_render::Texture* mTexture;
		r2bix::ColorMaskOption mColorMaskOption;
	};
}