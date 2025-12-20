#include "r2bix_input_InputManager.hpp"

#include <numeric>

#include "r2_assert.hpp"

#include "r2bix_input_Listener4Keyboard.hpp"
#include "r2bix_input_Listener4Mouse.hpp"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputSignals( offset_x, offset_y )
		, mObservationKeyFlags()
		, mKeyStatusProcessor()
		, mListenerContainer4Mouse()
		, mListenerContainer4Keyboard()
	{}

	void InputManager::Update()
	{
		//
		// 입력 수집
		//
		mMachineInputSignals.Collect();
		mKeyStatusProcessor.Update( mMachineInputSignals );

		//
		// 업데이트 : Mouse
		//
		if( !mListenerContainer4Mouse.empty() )
		{

			//
			// Mouse Cursor Update
			// > Listen4Cursor 함수가 true 를 반환하면 이후 호출은 더미 Cursor값을 준다.
			//
			{
				if( mMachineInputSignals.IsMouseMoved() )
				{
					eListenMode listen_mode = eListenMode::Pass;
					bool spend_input_signal = false;
					for( r2bix_input::Listener4Mouse* l : mListenerContainer4Mouse )
					{
						if( !l->IsActivated() )
						{
							l->Listen4Cursor( CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
							continue;
						}

						if( eListenMode::Pass == listen_mode && !spend_input_signal )
						{
							spend_input_signal = l->Listen4Cursor( mMachineInputSignals.GetCursorPoint() );
							listen_mode = l->GetListenMode();
						}
						else
						{
							l->Listen4Cursor( CursorPoint{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() } );
						}
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

				eListenMode listen_mode = eListenMode::Pass;
				bool spend_input_signal = false;

				for( const auto key_code : mouse_keys )
				{
					if( !mObservationKeyFlags.Has( key_code ) )
					{
						continue;
					}

					listen_mode = eListenMode::Pass;
					spend_input_signal = false;
					for( r2bix_input::Listener4Mouse* l : mListenerContainer4Mouse )
					{
						if( !l->IsActivated() )
						{
							continue;
						}

						if( !l->IsObservationKey( key_code ) )
						{
							continue;
						}

						if( eListenMode::Pass == listen_mode && !spend_input_signal )
						{
							spend_input_signal = l->Listen4Key( key_code, mMachineInputSignals.HasInput( key_code ) );
							listen_mode = l->GetListenMode();
						}
						else
						{
							l->Listen4Key( key_code, false );
						}
					}
				}
			}
		}

		//
		// 업데이트 : Keyboard
		//
		if( !mListenerContainer4Keyboard.empty() )
		{
			eListenMode listen_mode = eListenMode::Pass;
			bool spend_input_signal = false;

			for(
				r2bix_input::KeyCodeTypeT key_code = r2bix_input::eKeyCode::START, end_code = r2bix_input::eKeyCode::END;
				end_code >= key_code;
				++key_code
			)
			{
				if( !mObservationKeyFlags.Has( key_code ) )
				{
					continue;
				}

				listen_mode = eListenMode::Pass;
				spend_input_signal = false;
				for( r2bix_input::Listener4Keyboard* l : mListenerContainer4Keyboard )
				{
					if( !l->IsActivated() )
					{
						continue;
					}

					if( !l->IsObservationKey( key_code ) )
					{
						continue;
					}

					if( eListenMode::Pass == listen_mode && !spend_input_signal )
					{
						spend_input_signal = l->Listen( key_code, mMachineInputSignals.HasInput( key_code ) );
						listen_mode = l->GetListenMode();
					}
					else
					{
						l->Listen( key_code, false );
					}
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
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), listener );
			if( target_itr != mListenerContainer4Mouse.end() )
			{
				R2ASSERT( false, "이미 등록된 M리스너의 등록을 요청한다." );
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
		mObservationKeyFlags.Add( listener->GetObservationKeyList() );
	}
	void InputManager::RemoveListener( r2bix_input::Listener4Mouse* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 M리스너가 nullptr 이다." );
			return;
		}

		if( mListenerContainer4Mouse.empty() )
		{
			R2ASSERT( false, "등록된 M리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer4Mouse.begin(), mListenerContainer4Mouse.end(), listener );
			if( target_itr == mListenerContainer4Mouse.end() )
			{
				R2ASSERT( false, "등록된적 없는 M리스너의 삭제를 요청한다." );
				return;
			}

			mListenerContainer4Mouse.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mObservationKeyFlags.Remove( listener->GetObservationKeyList() );
	}

	void InputManager::AddListener( r2bix_input::Listener4Keyboard* const listener )
	{
		//
		// 반복 등록 확인
		//
		{
			auto target_itr = std::find( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), listener );
			if( target_itr != mListenerContainer4Keyboard.end() )
			{
				R2ASSERT( false, "이미 등록된 K리스너의 등록을 요청한다." );
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
		mObservationKeyFlags.Add( listener->GetObservationKeyList() );
	}
	void InputManager::RemoveListener( r2bix_input::Listener4Keyboard* const listener )
	{
		if( nullptr == listener )
		{
			R2ASSERT( false, "삭제 요청된 K리스너가 nullptr 이다." );
			return;
		}

		if( mListenerContainer4Keyboard.empty() )
		{
			R2ASSERT( false, "등록된 K리스너가 없는데 삭제를 요청한다." );
			return;
		}

		//
		// Remove
		//
		{
			auto target_itr = std::find( mListenerContainer4Keyboard.begin(), mListenerContainer4Keyboard.end(), listener );
			if( target_itr == mListenerContainer4Keyboard.end() )
			{
				R2ASSERT( false, "등록된적 없는 K리스너의 삭제를 요청한다." );
				return;
			}

			mListenerContainer4Keyboard.erase( target_itr );
		}

		//
		// Unregist Key
		//
		mObservationKeyFlags.Remove( listener->GetObservationKeyList() );
	}
}