#include "pch.h"
#include "r2component_TextRenderComponent.h"

#include "base/r2base_DebugConfig.h"
#include "r2component_TransformComponent.h"
#include "render/r2render_Camera.h"

namespace r2component
{
	TextRenderComponent::TextRenderComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mTransformComponent( nullptr )
		, mRect()
		, mTexture( " " )
	{}

	std::unique_ptr<TextRenderComponent> TextRenderComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<TextRenderComponent> ret( new ( std::nothrow ) TextRenderComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void TextRenderComponent::Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target )
	{
		//
		// World Space : My Rect : Test
		//
		{
			const r2::RectInt my_world_space_rect( mRect.GetOrigin() + mTransformComponent->GetPosition(), mRect.GetSize() );
			if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
			{
				return;
			}
		}

		//
		// Camera Space : My Position
		//
		const auto camera_space_my_position = mTransformComponent->GetPosition() - camera->GetPoint();

		//
		// Render Target Space : My Position
		//
		const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();

		//
		// Render Target Space : My Rect
		//
		auto render_target_space_my_rect = mRect;
		render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );

		//
		// Render Target Space : Intersect Rect
		//
		auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );

		//
		// Offset
		//
		const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
		for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() > y; ++y, ++ty )
		{
			for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() > x; ++x, ++tx )
			{
				render_target->Fill(
					x, y
					, mTexture.Get( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
				);
			}
		}

		//
		// Debug
		//
		if( r2base::DebugConfig::GetLabelConfig().bShowPositionPivot )
		{
			render_target->Fill( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), '+' );
		}
	}
}