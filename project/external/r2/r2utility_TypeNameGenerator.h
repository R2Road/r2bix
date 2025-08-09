#pragma once

#include "r2utility_StringBuilder.h"

namespace r2utility
{
	template<typename Owner_T, char... chars>
	class TypeNameGenerator
	{
	public:
		static constexpr size_t size = sizeof...( chars );
		static constexpr const char post_fix[size + 1] = { chars..., '\0' };

	private:
		using OwnerT = Owner_T;
		using IndexT = unsigned long long int;

		TypeNameGenerator() = delete;

		static IndexT& getIndex()
		{
			static IndexT index = 0;
			return index;
		}

	public:
		static const char* Get()
		{
			return r2utility::StringBuilder::Build( "%s%d", post_fix, getIndex()++ );
		}

		static void Clear()
		{
			getIndex() = 0ll;
		}
	};
}

