#include "r2bix_component_UIControlComponent.h"

#include "r2_assert.hpp"

#include "r2bix_Director.h"

#include "r2bix_component_UIPannelComponent.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	UIControlComponent::UIControlComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<UIControlComponent>( director, owner_node )
		, mOrder( 0 )

		, mPivotVector( 0.5f, 0.5f )
		, mSlot4PivotChanged( [this]( float x, float y ) {
			mPivotVector.x = x;
			mPivotVector.y = y;

			resetResponseRect();
		} )
		, mResponseRect( 0, 0, 1, 1 )

		, mCursorState( r2bix_ui::eCursorStatus::None )
		, mKeyStep( r2bix_ui::eKeyStep::None)

		, mSignal4CursorResponse()
		, mSignal4KeyResponse()

		, mUIPannelComponent( nullptr )
	{}



	bool UIControlComponent::initProcess()
	{
		GetOwnerNode().mTransformComponent->ConnectSlot4PivotChanged( &mSlot4PivotChanged );

		return true;
	}

	void UIControlComponent::enterProcess()
	{
		r2bix_node::Node* parent_node = GetOwnerNode().GetParentNode();

		//
		// Find UIPannelComponent
		//
		while( parent_node )
		{
			mUIPannelComponent = parent_node->GetComponent<UIPannelComponent>();
			if( mUIPannelComponent )
			{
				break;
			}

			parent_node = parent_node->GetParentNode();
		}

		//
		// Regist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->AddUIControl( this );
		}
	}
	void UIControlComponent::exitProcess()
	{
		//
		// Unregist UI Input Listener
		//
		if( mUIPannelComponent )
		{
			mUIPannelComponent->RemoveUIControl( this );
		}
	}



	void UIControlComponent::SetSize( const uint32_t width, const uint32_t height )
	{
		R2ASSERT( width >= 1 && height >= 1, "" );

		mResponseRect.SetSize( width - 1, height - 1 );

		resetResponseRect();
	}

	void UIControlComponent::resetResponseRect()
	{
		mResponseRect.SetOrigin(
			  static_cast<int>( -mResponseRect.GetWidth() * mPivotVector.x )
			, static_cast<int>( -mResponseRect.GetHeight() * mPivotVector.y )
		);
	}



	bool UIControlComponent::OnCursorResponse( const r2bix_input::CursorPoint cursor_point )
	{
		const r2::RectInt r(
			  mOwnerNode.mTransformComponent->GetWorldPosition() + mResponseRect.GetOrigin()
			, r2::SizeInt( mResponseRect.GetSize().GetWidth(), mResponseRect.GetSize().GetHeight() )
		);

		switch( mCursorState )
		{
		case r2bix_ui::eCursorStatus::None:
		case r2bix_ui::eCursorStatus::CursorLeave:
			if( r.IsIn( cursor_point ) )
			{
				mCursorState = r2bix_ui::eCursorStatus::CursorOver;

				mSignal4CursorResponse.Emit( mCursorState );
			}
			else
			{
				mCursorState = r2bix_ui::eCursorStatus::None;
			}
			break;

		case r2bix_ui::eCursorStatus::CursorOver:
		case r2bix_ui::eCursorStatus::CursorMove:
			if( r.IsIn( cursor_point ) )
			{
				//
				// Input Manager 에서 커서가 이동했을 때 Callback을 호출하므로 커서 위치가 변했는지 확인 안해도 된다.
				//

				mCursorState = r2bix_ui::eCursorStatus::CursorMove;

				mSignal4CursorResponse.Emit( mCursorState );
			}
			else
			{
				mCursorState = r2bix_ui::eCursorStatus::CursorLeave;

				mSignal4CursorResponse.Emit( mCursorState );
			}
			break;
		}

		return ( r2bix_ui::eCursorStatus::CursorOver == mCursorState || r2bix_ui::eCursorStatus::CursorMove == mCursorState );
	}
	bool UIControlComponent::OnKeyResponse( const int key_index, const r2bix_input::eKeyStep key_step )
	{
		switch( mCursorState )
		{
		case r2bix_ui::eCursorStatus::None:
		case r2bix_ui::eCursorStatus::CursorLeave:
			if( r2bix_ui::eKeyStep::Push == mKeyStep || r2bix_ui::eKeyStep::Pressed == mKeyStep )
			{
				mKeyStep = r2bix_ui::eKeyStep::Cancel;
			}
			else
			{
				mKeyStep = r2bix_ui::eKeyStep::None;
			}
			break;

		case r2bix_ui::eCursorStatus::CursorOver:
		case r2bix_ui::eCursorStatus::CursorMove:
		{
			switch( key_step )
			{
			case r2bix_input::eKeyStep::None:
				mKeyStep = r2bix_ui::eKeyStep::None;
				break;
			case r2bix_input::eKeyStep::Push:
				if( r2bix_ui::eKeyStep::None == mKeyStep || r2bix_ui::eKeyStep::Release == mKeyStep || r2bix_ui::eKeyStep::Cancel == mKeyStep )
				{
					mKeyStep = r2bix_ui::eKeyStep::Push;
				}
				break;
			case r2bix_input::eKeyStep::Pressed:
				if( r2bix_ui::eKeyStep::Push == mKeyStep )
				{
					mKeyStep = r2bix_ui::eKeyStep::Pressed;
				}
				break;
			case r2bix_input::eKeyStep::Release:
				if( r2bix_ui::eKeyStep::Push == mKeyStep || r2bix_ui::eKeyStep::Pressed == mKeyStep )
				{
					mKeyStep = r2bix_ui::eKeyStep::Release;
				}
				break;
			}
		}
		break;
		}

		if( r2bix_ui::eKeyStep::None == mKeyStep )
		{
			return false;
		}

		mSignal4KeyResponse.Emit( key_index, mKeyStep );

		return true;
	}
}