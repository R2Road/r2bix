#include "r2bix_component_UIPannelComponent.h"

#include "r2_Assert.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

#include "r2bix_input_UIInputListener.h"

#include "r2bix_node_Node.h"

namespace r2bix_component
{
	UIPannelComponent::UIPannelComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<UIPannelComponent>( owner_node )
		, mListener4Mouse()
		, mCursorResponseCallback()
		, mCursorState( r2bix_ui::eCursorStatus::None )
		, mUIInputListenerContainer()
	{}



	bool UIPannelComponent::InitProcess()
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetWorldPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );

			switch( mCursorState )
			{
			case r2bix_ui::eCursorStatus::None:
			case r2bix_ui::eCursorStatus::CursorLeave:
				if( r.IsIn( cursor_point ) )
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorOver;

					if( mCursorResponseCallback )
					{
						mCursorResponseCallback( mCursorState );
					}

					OnCursorResponse( cursor_point );
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

					if( mCursorResponseCallback )
					{
						mCursorResponseCallback( mCursorState );
					}

					OnCursorResponse( cursor_point );
				}
				else
				{
					mCursorState = r2bix_ui::eCursorStatus::CursorLeave;

					if( mCursorResponseCallback )
					{
						mCursorResponseCallback( mCursorState );
					}

					OnCursorResponse( r2bix_input::CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
				}
				break;
			}

			return ( r2bix_ui::eCursorStatus::CursorOver == mCursorState || r2bix_ui::eCursorStatus::CursorMove == mCursorState );
		} );

		return true;
	}

	void UIPannelComponent::ActivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener4Mouse );
	}
	void UIPannelComponent::DeactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener4Mouse );
	}



	void UIPannelComponent::AddListener( r2bix_input::UIInputListener* const listener )
	{
		//
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mUIInputListenerContainer.begin(), mUIInputListenerContainer.end(), listener );
			if( target_itr != mUIInputListenerContainer.end() )
			{
				R2ASSERT( false, "이미 등록된 리스너의 등록을 요청한다." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mUIInputListenerContainer.begin(), mUIInputListenerContainer.end(), [listener]( const r2bix_input::UIInputListener* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mUIInputListenerContainer.end() == pivot_itr )
			{
				mUIInputListenerContainer.push_back( listener );
			}
			else
			{
				mUIInputListenerContainer.insert( pivot_itr, listener );
			}

			mListener4Mouse;
		}
	}
	void UIPannelComponent::RemoveListener( r2bix_input::UIInputListener* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 리스너가 nullptr 이다." );
			return;
		}

		if( mUIInputListenerContainer.empty() )
		{
			R2ASSERT( false, "등록된 리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mUIInputListenerContainer.begin(), mUIInputListenerContainer.end(), listener );
			if( target_itr == mUIInputListenerContainer.end() )
			{
				R2ASSERT( false, "등록된적 없는 리스너의 삭제를 요청한다." );
				return;
			}

			mUIInputListenerContainer.erase( target_itr );
		}
	}
	void UIPannelComponent::OnCursorResponse( const r2bix_input::CursorPoint cursor_point )
	{
		for( auto l : mUIInputListenerContainer )
		{
			if( l->OnCursorResponse( cursor_point ) )
			{
				break;
			}
		}
	}
}