#pragma once

#include <list>

#include "r2bix_input_KeyStatusProcessor.hpp"
#include "r2bix_input_MachineInputCollector.h"
#include "r2bix_input_ObservationKeyFlags.hpp"

namespace r2bix_input
{
	class Listener4Keyboard;
	class Listener4Mouse;

	class InputManager
	{
	public:
		using ListenerContainer4Mouse = std::list<Listener4Mouse*>;
		using ListenerContainer4Keyboard = std::list<Listener4Keyboard*>;



		InputManager( const short offset_x, const short offset_y );



		//
		//
		//
		inline eKeyStep GetStep( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			return mKeyStatusProcessor.GetStep( key_code );
		}
		inline bool GetChanged( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			return mKeyStatusProcessor.GetChanged( key_code );
		}
		inline bool IsPushed( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			return mKeyStatusProcessor.IsPushed( key_code );
		}
		inline bool IsRelease( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			return mKeyStatusProcessor.IsRelease( key_code );
		}
		inline bool HasInput( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			return mKeyStatusProcessor.HasInput( key_code );
		}



		//
		//
		//
		void Update();



		//
		//
		//
		void ClearListener();

		void AddListener( r2bix_input::Listener4Mouse* const listener );
		void RemoveListener( r2bix_input::Listener4Mouse* const listener );

		void AddListener( r2bix_input::Listener4Keyboard* const listener );
		void RemoveListener( r2bix_input::Listener4Keyboard* const listener );

		const ListenerContainer4Mouse& GetListenerContainer4Mouse() const
		{
			return mListenerContainer4Mouse;
		}
		const ListenerContainer4Keyboard& GetListenerContainer4Keyboard() const
		{
			return mListenerContainer4Keyboard;
		}



		//
		//
		//
		CursorPoint GetCursorPoint() const
		{
			return mMachineInputCollector.GetCursorPoint();
		}



	public:
		MachineInputCollector mMachineInputCollector;
		ObservationKeyFlags mObservationKeyFlags;
		KeyStatusProcessor mKeyStatusProcessor;

		ListenerContainer4Mouse mListenerContainer4Mouse;
		ListenerContainer4Keyboard mListenerContainer4Keyboard;
	};
}