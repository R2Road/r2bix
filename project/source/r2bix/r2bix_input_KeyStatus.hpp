//
// # 사용되는 유효 bit
// > X000 0XXX
// 
// # 설명
// > 앞의 X000 은 key step 이 지난 프레임과 달라 졌는가.
// > 뒤의 0XXX 은 현재 프레임의 key step
//

#pragma once

#include "r2bix_input_Constant.hpp"

namespace r2bix_input
{
	class KeyStatus
	{
	public:
		KeyStatus() : mInfo( 0 )
		{}

		void Set( const r2bix_input::eKeyStep key_step, const bool changed )
		{
			mInfo = static_cast<KeyStepTypeT>( key_step ) | ( changed ? 0b10000000 : 0b00000000 );
		}

		inline r2bix_input::eKeyStep GetStep() const
		{
			return static_cast<r2bix_input::eKeyStep>( mInfo & 0b00001111 );
		}
		inline bool GetChanged() const
		{
			return ( mInfo & 0b10000000 );
		}

		void Update( const bool signal_flag )
		{
			if( signal_flag )
			{
				switch( GetStep() )
				{
				case eKeyStep::None:
					Set( eKeyStep::Push, true );
					break;

				case eKeyStep::Push:
					Set( eKeyStep::Pressed, true );
					break;

				case eKeyStep::Pressed:
					Set( eKeyStep::Pressed, true );
					break;

				case eKeyStep::Release:
					Set( eKeyStep::Push, true );
					break;

				}
			}
			else
			{
				switch( GetStep() )
				{
				case eKeyStep::None:
					Set( eKeyStep::None, false );
					break;

				case eKeyStep::Push:
				case eKeyStep::Pressed:
					Set( eKeyStep::Release, true );
					break;

				case eKeyStep::Release:
					Set( eKeyStep::None, true );
					break;
				}
			}
		}

	private:
		r2bix_input::KeyStepTypeT mInfo;
	};
}