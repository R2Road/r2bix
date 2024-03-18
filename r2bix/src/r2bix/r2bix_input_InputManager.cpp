#include "r2bix_input_InputManager.h"

#include "r2_Assert.h"

#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputCollector( offset_x, offset_y )
		, mKeyboardListener()
		, mMouseListener()
	{}

	void InputManager::Update()
	{
		//
		// �Է� ����
		//
		mMachineInputCollector.Collect();

		//
		// Ű ���� ������Ʈ
		//
		if( !mMouseListener.empty() )
		{
			( *mMouseListener.begin() )->Update(mMachineInputCollector.GetObservationKeyStates(), mMachineInputCollector.GetCursorPoint());
		}
		if( !mKeyboardListener.empty() )
		{
			( *mKeyboardListener.begin() )->Update(mMachineInputCollector.GetObservationKeyStates());
		}
	}



	void InputManager::AddMouseListener( r2bix_input::Listener4Mouse* const listener )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mMouseListener.begin(), mMouseListener.end(), listener );
			if( target_itr != mMouseListener.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� M�������� ����� ��û�Ѵ�." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mMouseListener.begin(), mMouseListener.end(), [listener]( const r2bix_input::Listener4Mouse* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mMouseListener.end() == pivot_itr )
			{
				mMouseListener.insert( pivot_itr, listener );
			}
			else
			{
				mMouseListener.push_back( listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveMouseListener( r2bix_input::Listener4Mouse* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "���� ��û�� M�����ʰ� nullptr �̴�." );
			return;
		}

		if( mMouseListener.empty() )
		{
			R2ASSERT( false, "��ϵ� M�����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mMouseListener.begin(), mMouseListener.end(), listener );
			if( target_itr == mMouseListener.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� M�������� ������ ��û�Ѵ�." );
				return;
			}

			mMouseListener.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeys() );
	}

	void InputManager::AddKeyboardListener( r2bix_input::Listener4Keyboard* const listener )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mKeyboardListener.begin(), mKeyboardListener.end(), listener );
			if( target_itr != mKeyboardListener.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� K�������� ����� ��û�Ѵ�." );
				return;
			}
		}		

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mKeyboardListener.begin(), mKeyboardListener.end(), [listener]( const r2bix_input::Listener4Keyboard* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mKeyboardListener.end() == pivot_itr )
			{
				mKeyboardListener.insert( pivot_itr, listener );
			}
			else
			{
				mKeyboardListener.push_back( listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveKeyboardListener( r2bix_input::Listener4Keyboard* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "���� ��û�� K�����ʰ� nullptr �̴�." );
			return;
		}

		if( mKeyboardListener.empty() )
		{
			R2ASSERT( false, "��ϵ� K�����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mKeyboardListener.begin(), mKeyboardListener.end(), listener );
			if( target_itr == mKeyboardListener.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� K�������� ������ ��û�Ѵ�." );
				return;
			}

			mKeyboardListener.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeys() );
	}
}