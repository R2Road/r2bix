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
			// Mouse Move Flag �� �������� ������
			//  > Ŀ�� ������ CursorPoint ���� ����� ���� ���� �̻��� �̵����� �߻����� ������ CursorPoint �� �״�� �̱� ������
			//  > Mouse�� �̵��ϴ� ���ӿ��� ���� Off �� ���´�.
			//  > �� �����ӿ� ��Ʈ ���� ���� �̻��� �������� ������ ������ On ���� �����ȴٴ� ���̴�.
			// ��������δ� ���� ����.
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