//
// # Summary
// - 입력 처리를 위한 가장 아랫단의 클래스
//

#pragma once

#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	class MachineInputSignals
	{
	public:
		MachineInputSignals();
		explicit MachineInputSignals( const int offset_x, const int offset_y );
		explicit MachineInputSignals( const CursorPoint& offset );



		//
		//
		//
		CursorPoint GetOffset() const
		{
			return mOffset;
		}
		CursorPoint::ValueT GetOffsetX() const
		{
			return mOffset.GetX();
		}
		CursorPoint::ValueT GetOffsetY() const
		{
			return mOffset.GetY();
		}

		const ObservationKeySignalsT& GetObservationKeySignals() const
		{
			return mObservationKeySignals;
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
		bool HasInput( const KeyCodeTypeT key_value ) const
		{
			return mObservationKeySignals.test( key_value );
		}


	private:
		CursorPoint mOffset;

		ObservationKeySignalsT mObservationKeySignals;

		CursorPoint mCursorPoint;
		bool mbMouseMoved;
	};
}