#include "r2bix_input_ObservationKeyFlags.hpp"

namespace r2bix_input
{
	ObservationKeyFlags::ObservationKeyFlags() : mFlags{}
	{}

	void ObservationKeyFlags::Add( const r2bix_input::eKeyCode key_code )
	{
		++mFlags[key_code];
	}
	void ObservationKeyFlags::Add( const r2bix_input::ObservationKeyList& key_list )
	{
		for( const auto k : key_list )
		{
			++mFlags[k.GetCode()];
		}
	}

	void ObservationKeyFlags::Remove( const r2bix_input::eKeyCode key_code )
	{
		--mFlags[key_code];
	}
	void ObservationKeyFlags::Remove( const r2bix_input::ObservationKeyList& key_list )
	{
		for( const auto k : key_list )
		{
			--mFlags[k.GetCode()];
		}
	}
}