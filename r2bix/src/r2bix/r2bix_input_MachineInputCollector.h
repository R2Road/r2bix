#pragma once

#include <array>

#include "r2bix_input_Constant.h"
#include "r2bix_input_ObservationKeys.h"

namespace r2bix_input
{
	class MachineInputCollector
	{
	public:
		MachineInputCollector( const int offset_x, const int offset_y );
		MachineInputCollector( const r2::PointInt offset );



		//
		//
		//
		const ObservationKeyStatesT& GetObservationKeyStates() const
		{
			return mObservationKeyStates;
		}
		CursorPoint GetCursorPoint() const
		{
			return mCursorPoint;
		}
		bool IsMouseMoved() const
		{
			//
			// # 2024.03.11 by R
			// Mouse Move Flag 의 가시적인 문제점
			//  > 커서 단위로 CursorPoint 값을 만들다 보니 일정 이상의 이동량이 발생하지 않으면 CursorPoint 가 그대로 이기 때문에
			//  > Mouse가 이동하는 중임에도 값이 Off 로 나온다.
			//  > 한 프레임에 폰트 가로 세로 이상의 움직임을 꾸준히 보여야 On 으로 유지된다는 것이다.
			// 기능적으로는 문제 없다.
			//
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
		ObservationKeyStatesT mObservationKeyStates;

		CursorPoint mCursorPoint_Last;
		CursorPoint mCursorPoint;
		bool mbMouseMoved;
	};
}