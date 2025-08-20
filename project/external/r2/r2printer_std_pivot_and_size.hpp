#pragma once

#include <iomanip>
#include <ostream>

#include "r2_none_copyable.hpp"
#include "r2_pivot_and_size.hpp"

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::PivotAndSize<T>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "     "

		<< "pivot : " << std::setw( w ) << v.GetPivot()

		<< "   "

		<< "size : " << std::setw( w ) << v.GetSize()

		<< "   "

		<< "end : " << std::setw( w ) << v.GetEnd()

		<< "   "

		<< "valid : " << ( v.IsValid() ? "true" : "false" )

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::PivotAndSize<char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "     "

		<< "pivot : " << std::setw( w ) << static_cast<int>( v.GetPivot() )

		<< "   "

		<< "size : " << std::setw( w ) << static_cast<int>( v.GetSize() )

		<< "   "

		<< "end : " << std::setw( w ) << static_cast<int>( v.GetEnd() )

		<< "   "

		<< "valid : " << ( v.IsValid() ? "true" : "false" )

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::PivotAndSize<unsigned char>& v )
{
		static const int w = 5;

	return o
		<< std::left

		<< "     "

		<< "pivot : " << std::setw( w ) << static_cast<int>( v.GetPivot() )

		<< "   "

		<< "size : " << std::setw( w ) << static_cast<int>( v.GetSize() )

		<< "   "

		<< "end : " << std::setw( w ) << static_cast<int>( v.GetEnd() )

		<< "   "

		<< "valid : " << ( v.IsValid() ? "true" : "false" )

		<< std::right
	;
}

namespace r2printer
{
	class STD_PivotAndSize : private r2::NoneCopyable
	{
	private:
		STD_PivotAndSize() = delete;

	public:
		template<typename T>
		inline static void Print( const r2::PivotAndSize<T>& v )
		{
			std::cout
				<< "\t" "Pivot And Size"

				<< v

				<< "\n";
		}
	};
}