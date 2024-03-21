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
		, mMouseOverCallback()
		, mMouseMoveCallback()
		, mMouseLeaveCallback()
		, mState( eState::None )
		, mListenerContainer()
	{
		mListener4Mouse.SetCallback4CursorMoved( [this]( const r2bix_input::CursorPoint cursor_point )->bool
		{
			const r2::RectInt r( mOwnerNode.mTransformComponent->GetPosition(), r2::SizeInt( GetWidth() - 1, GetHeight() - 1 ) );


			switch( mState )
			{
			case eState::None:
				if( r.IsIn( cursor_point ) )
				{
					mState = eState::MouseOver;

					if( mMouseOverCallback )
					{
						mMouseOverCallback();
					}
				}
				break;

			case eState::MouseOver:
			case eState::MouseMove:
				if( r.IsIn( cursor_point ) )
				{
					//
					// Input Manager ���� Ŀ���� �̵����� �� Callback�� ȣ���ϹǷ� Ŀ�� ��ġ�� ���ߴ��� Ȯ�� ���ص� �ȴ�.
					//

					mState = eState::MouseMove;

					if( mMouseMoveCallback )
					{
						mMouseMoveCallback();
					}
				}
				else
				{
					mState = eState::MouseLeave;

					if( mMouseLeaveCallback )
					{
						mMouseLeaveCallback();
					}
				}
				break;

			case eState::MouseLeave:
				mState = eState::None;
				break;
			}

			return ( eState::MouseOver == mState || eState::MouseMove == mState );
		} );
	}



	void UIPannelComponent::ActivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener4Mouse );
	}
	void UIPannelComponent::DeactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener4Mouse );
	}

	void UIPannelComponent::Update( const float delta_time )
	{

	}



	void UIPannelComponent::AddListener( r2bix_input::UIInputListener* const listener )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mListenerContainer.begin(), mListenerContainer.end(), listener );
			if( target_itr != mListenerContainer.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� �������� ����� ��û�Ѵ�." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mListenerContainer.begin(), mListenerContainer.end(), [listener]( const r2bix_input::UIInputListener* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mListenerContainer.end() == pivot_itr )
			{
				mListenerContainer.push_back( listener );
			}
			else
			{
				mListenerContainer.insert( pivot_itr, listener );
			}
		}
	}
	void UIPannelComponent::RemoveListener( r2bix_input::UIInputListener* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "���� ��û�� �����ʰ� nullptr �̴�." );
			return;
		}

		if( mListenerContainer.empty() )
		{
			R2ASSERT( false, "��ϵ� �����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer.begin(), mListenerContainer.end(), listener );
			if( target_itr == mListenerContainer.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� �������� ������ ��û�Ѵ�." );
				return;
			}

			mListenerContainer.erase( target_itr );
		}
	}
}