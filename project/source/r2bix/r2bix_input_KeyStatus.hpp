#pragma once

#include "r2bix_input_Constant.h"

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
			return static_cast< r2bix_input::eKeyStep >( mInfo & 0b00001111 );
		}
		inline bool GetChanged() const
		{
			return ( mInfo & 0b10000000 );
		}

	private:
		r2bix_input::KeyStepTypeT mInfo;
	};
}