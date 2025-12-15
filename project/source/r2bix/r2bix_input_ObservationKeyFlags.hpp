//
// # Summary
// - 입력 처리가 필요한 키들을 수집/관리
//

#pragma once

#include <array>

#include "r2bix_input_Constant.h"
#include "r2bix_input_ObservationKeyList.hpp"

namespace r2bix_input
{
	class ObservationKeyFlags
	{
	private:
		using Container = std::array<char, MAX_OBSERVATION_KEY_COUNT>;

	public:
		ObservationKeyFlags();


		//
		//
		// 
		const Container& GetFlags() const
		{
			return mFlags;
		}

		bool Has( const KeyCodeTypeT key_value ) const
		{
			return 0 < mFlags[key_value];
		}


		//
		//
		//
		void Add( const r2bix_input::eKeyCode key_code );
		void Add( const r2bix_input::ObservationKeyList& key_list );

		void Remove( const r2bix_input::eKeyCode key_code );
		void Remove( const r2bix_input::ObservationKeyList& key_list );


	private:
		Container mFlags;
	};
}