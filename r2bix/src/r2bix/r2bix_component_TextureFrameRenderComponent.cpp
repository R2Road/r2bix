#include "r2bix_component_TextureFrameRenderComponent.h"

#include "r2bix_DebugConfig.h"

#include "r2bix_component_TransformComponent.h"

#include "r2bix_node_Node.h"

#include "r2bix_Camera.h"
#include "r2bix_render_TextureFrame.h"

namespace r2bix_component
{
	TextureFrameRenderComponent::TextureFrameRenderComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<TextureFrameRenderComponent>( director, owner_node )
		, mSlot4PivotChanged( [this]( float x, float y )
		{
			mPivotVector.x = x;
			mPivotVector.y = y;
			resetVisibleRect();
		} )
		, mPivotVector( 0.5f, 0.5f )
		, mVisibleRect()
		, mTextureFrame( nullptr )
		, mColorMaskOption( r2bix::eColorMaskFlag::CMF_Foreground | r2bix::eColorMaskFlag::CMF_Background )
	{}



	void TextureFrameRenderComponent::Render( const r2bix::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset )
	{
		if( nullptr == mTextureFrame )
		{
			return;
		}

		//
		// World Space : My Rect : Test
		//
		{
			const r2::RectInt my_world_space_rect( offset + mVisibleRect.GetOrigin() + mOwnerNode.mTransformComponent->GetPosition(), mVisibleRect.GetSize() );
			if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
			{
				return;
			}
		}

		//
		// Camera Space : My Position
		//
		const auto camera_space_my_position = offset + mOwnerNode.mTransformComponent->GetPosition() - camera->GetPoint();

		//
		// Render Target Space : My Position
		//
		const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();

		//
		// Render Target Space : My Rect
		//
		auto render_target_space_my_rect = mVisibleRect;
		render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );

		//
		// Render Target Space : Intersect Rect
		//
		auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );

		//
		// Offset
		//
		const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
		for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() >= y; ++y, ++ty )
		{
			for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() >= x; ++x, ++tx )
			{
				if( !mTextureFrame->GetCharacterDisuse( off_set_point.GetX() + tx, off_set_point.GetY() + ty ) )
				{
					render_target->FillCharacter(
						x, y
						, mTextureFrame->GetCharacter( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
					);
				}

				render_target->FillColorWithMask(
					x, y
					, mTextureFrame->GetColor( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
					, mColorMaskOption
				);
			}
		}

		//
		// Debug
		//
		if( r2bix::DebugConfig::GetInstance().GetRenderConfig().bShowPositionPivot )
		{
			render_target->FillCharacter( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), '+' );
		}
	}



	void TextureFrameRenderComponent::SetPivot( const float x, const float y )
	{
		mPivotVector.x = x;
		mPivotVector.y = y;

		resetVisibleRect();
	}

	void TextureFrameRenderComponent::SetTextureFrame( const r2bix_render::TextureFrame* const texture_frame )
	{
		mTextureFrame = texture_frame;

		resetVisibleRect();
	}

	void TextureFrameRenderComponent::resetVisibleRect()
	{
		if( !mTextureFrame )
		{
			return;
		}

		mVisibleRect.Set(
			  -static_cast<int>( mTextureFrame->GetWidth() * mPivotVector.x )
			, -static_cast<int>( mTextureFrame->GetHeight() * mPivotVector.y )
			, mTextureFrame->GetVisibleRect().GetSize().GetWidth()
			, mTextureFrame->GetVisibleRect().GetSize().GetHeight()
		);
	}
}