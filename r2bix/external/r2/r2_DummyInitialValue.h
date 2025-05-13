#pragma once

namespace r2
{
	template<typename T>
	class DummyInitialValue
	{
	public:
		const T& operator()()
		{
			static const T ret;
			return ret;
		}
	};
}