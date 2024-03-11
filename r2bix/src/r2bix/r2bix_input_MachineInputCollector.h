#pragma once

#include <array>
#include <bitset>

#include "r2bix_input_Constant.h"
#include "r2bix_input_ObservationKeys.h"

namespace r2bix_input
{
	class MachineInputCollector
	{
	public:
		MachineInputCollector( const int offset_x, const int offset_y );



		//
		//
		//
		const std::bitset<255>& GetObservationKeyStates() const
		{
			return mObservationKeyStates;
		}
		CursorPoint GetCursorPoint() const
		{
			return mCursorPoint;
		}
		bool IsMouseMoved() const
		{
			return mbMouseMoved;
		}
		


		//
		//
		//
		void Collect();



		//
		//
		//
		void AddObservationKeys( const ObservationKeys& observation_keys );
		void RemoveObservationKeys( const ObservationKeys& observation_keys );



		//
		//
		//
		bool HasInput( const KeyCodeTypeT key_value ) const
		{
			return mObservationKeyStates.test( key_value );
		}



	private:
		CursorPoint mOffset;

		std::array<KeyCodeTypeT, 255> mObservationKeyList;
		std::bitset<255> mObservationKeyStates;

		CursorPoint mCursorPoint_Last;
		CursorPoint mCursorPoint;
		bool mbMouseMoved;
	};
}