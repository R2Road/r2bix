#pragma once

#include <functional>

namespace r2base
{
	class Director;
}

namespace r2test
{
	enum class eTestEndAction;

	class iTest_Deprecated
	{
	public:
		using TitleFunc = std::function<const char*()>;
		using DoFunc = std::function<eTestEndAction( r2base::Director& director )>;

		virtual ~iTest_Deprecated() {}

		virtual TitleFunc GetTitleFunction() const = 0;
		virtual DoFunc GetDoFunction() = 0;
	};
}