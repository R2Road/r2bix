#include "r2bix_input_InputManager.h"

#include <numeric>

#include "r2_Assert.h"

#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputCollector( offset_x, offset_y )
		, mListenerContainer4Mouse()
		, mListenerContainer4Keyboard()
	{}

	void InputManager::Update()
	{
		//
		// �Է� ����
		//
		mMachineInputCollector.Collect();

		//
		// ������Ʈ : Mouse
		//
		if( !mListenerContainer4Mouse.empty() )
		{

			//
			// Mouse Cursor Update
			// > UpdateCursor �Լ��� true �� ��ȯ�ϸ� ���� ȣ���� ���� Cursor���� �ش�.
			//
			{
				if( mMachineInputCollector.IsMouseMoved() )
				{
					bool bKeepGoing = true;
					int i = 0;
					for( r2bix_input::Listener4Mouse* l : mListenerContainer4Mouse )
					{
						if( !l->IsActivated() )
						{
							l->UpdateCursor( CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
							continue;
						}

						if( bKeepGoing )
						{
							if( l->UpdateCursor( mMachineInputCollector.GetCursorPoint() ) )
							{
								bKeepGoing = false;
							}
						}
						else
						{
							l->UpdateCursor( CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
						}

						++i;
					}
				}
			}

			//
			// Mouse Key Update
			//
			{
				static const r2bix_input::KeyCodeTypeT mouse_keys[3] = {
					  r2bix_input::eKeyCode::VK_LBUTTON
					, r2bix_input::eKeyCode::VK_MBUTTON
					, r2bix_input::eKeyCode::VK_RBUTTON
				};

				int i = -1;
				for( const auto& k : mouse_keys )
				{
					++i;

					if( !mMachineInputCollector.IsObservationKey( k ) )
					{
						continue;
					}

					bool processed = false;
					for( r2bix_input::Listener4Mouse* l : mListenerContainer4Mouse )
					{
						if( !l->IsActivated() )
						{
							continue;
						}

						if( !l->IsObservationKey( k ) )
						{
							continue;
						}

						if( !processed )
						{
							if( !l->UpdateKey( i, mMachineInputCollector.HasInput( k ) ) )
							{
								processed = true;
								continue;
							}
						}
						else
						{
							l->UpdateKey( i, false );
						}

						break;
					}
				}
			}
		}

		//
		// ������Ʈ : Keyboard
		//
		if( !mListenerContainer4Keyboard.empty() )
		{
			for( int key_code = 0; 256 > key_code; ++key_code )
			{
				if( !mMachineInputCollector.IsObservationKey( key_code ) )
				{
					continue;
				}

				bool processed = false;
				for( r2bix_input::Listener4Keyboard* l : mListenerContainer4Keyboard )
				{
					if( !l->IsActivated() )
					{
						continue;
					}

					if( !processed )
					{
						if( !l->UpdateKey( key_code, mMachineInputCollector.HasInput( key_code ) ) )
						{
							processed = true;
							continue;
						}
					}
					else
					{
						l->UpdateKey( key_code, false );
					}

					break;
				}
			}
		}
	}



	void InputManager::ClearListener()
	{
		mListenerContainer4Mouse.clear();
		mListenerContainer4Keyboard.clear();
	}

	void InputManager::AddListener( r2bix_input::Listener4Mouse* const listener )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), listener );
			if( target_itr != mListenerContainer4Mouse.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� M�������� ����� ��û�Ѵ�." );
				return;
			}
		}

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), [listener]( const r2bix_input::Listener4Mouse* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mListenerContainer4Mouse.end() == pivot_itr )
			{
				mListenerContainer4Mouse.push_back( listener );
			}
			else
			{
				mListenerContainer4Mouse.insert( pivot_itr, listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeyContainer() );
	}
	void InputManager::RemoveListener( r2bix_input::Listener4Mouse* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "���� ��û�� M�����ʰ� nullptr �̴�." );
			return;
		}

		if( mListenerContainer4Mouse.empty() )
		{
			R2ASSERT( false, "��ϵ� M�����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), listener );
			if( target_itr == mListenerContainer4Mouse.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� M�������� ������ ��û�Ѵ�." );
				return;
			}

			mListenerContainer4Mouse.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeyContainer() );
	}

	void InputManager::AddListener( r2bix_input::Listener4Keyboard* const listener )
	{
		//
		// �ݺ� ��� Ȯ��
		//
		{
			auto target_itr = std::find( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), listener );
			if( target_itr != mListenerContainer4Keyboard.end() )
			{
				R2ASSERT( false, "�̹� ��ϵ� K�������� ����� ��û�Ѵ�." );
				return;
			}
		}		

		//
		// Add
		//
		{
			auto pivot_itr = std::find_if( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), [listener]( const r2bix_input::Listener4Keyboard* const l ){
				if( l->GetOrder() <= listener->GetOrder() )
				{
					return true;
				}

				return false;
			} );

			if( mListenerContainer4Keyboard.end() == pivot_itr )
			{
				mListenerContainer4Keyboard.push_back( listener );
			}
			else
			{
				mListenerContainer4Keyboard.insert( pivot_itr, listener );
			}
		}

		//
		// Regist Key
		//
		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeyContainer() );
	}
	void InputManager::RemoveListener( r2bix_input::Listener4Keyboard* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "���� ��û�� K�����ʰ� nullptr �̴�." );
			return;
		}

		if( mListenerContainer4Keyboard.empty() )
		{
			R2ASSERT( false, "��ϵ� K�����ʰ� ���µ� ������ ��û�Ѵ�." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), listener );
			if( target_itr == mListenerContainer4Keyboard.end() )
			{
				R2ASSERT( false, "��ϵ��� ���� K�������� ������ ��û�Ѵ�." );
				return;
			}

			mListenerContainer4Keyboard.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mMachineInputCollector.RemoveObservationKeys( listener->GetObservationKeyContainer() );
	}
}