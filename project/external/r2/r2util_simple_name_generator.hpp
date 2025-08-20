#pragma once

#include "r2util_string_builder.hpp"

namespace r2util
{
	template<char... chars>
	class SimpleNameGenerator
	{
	public:
		static constexpr size_t size = sizeof...( chars );
		static constexpr const char post_fix[size + 1] = { chars..., '\0' };

	private:
		using IndexT = unsigned long long int;

		SimpleNameGenerator() = delete;

		static IndexT& getIndex()
		{
			static IndexT index = 0;
			return index;
		}

	public:
		static const char* Get()
		{
			return r2util::StringBuilder::Build( "%s%d", post_fix, getIndex()++ );
		}

		static void Clear()
		{
			getIndex() = 0ll;
		}
	};
}

