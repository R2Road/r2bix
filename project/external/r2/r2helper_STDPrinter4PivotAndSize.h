#pragma once

#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_PivotAndSize.h"

namespace r2helper
{
	class STDPrinter4PivotAndSize : private r2::NoneCopyable
	{
	private:
		STDPrinter4PivotAndSize() = delete;

	public:
		template<typename T>
		inline static void PrintPivotAndEnd( const r2::PivotAndSize<T>& v )
		{
			std::cout
				<< "\t" "Pivot And Size"

				<< "      "
				   "p : " << v.GetPivot()
				<< "      "
				   "e : " << v.GetEnd()

				<< "\n";
		}

		template<>
		inline static void PrintPivotAndEnd( const r2::PivotAndSize<char>& v )
		{
			std::cout
				<< "\t" "Pivot And Size"

				<< "      "
				   "p : " << static_cast<int>( v.GetPivot() )
				<< "      "
				   "e : " << static_cast<int>( v.GetEnd() )

				<< "\n";
		}
		template<>
		inline static void PrintPivotAndEnd( const r2::PivotAndSize<unsigned char>& v )
		{
			std::cout
				<< "\t" "Pivot And Size"

				<< "      "
				   "p : " << static_cast<int>( v.GetPivot() )
				<< "      "
				   "e : " << static_cast<int>( v.GetEnd() )

				<< "\n";
		}
	};
}

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::PivotAndSize<T>& v )
{
	return o << v.GetPivot() << "   " << v.GetSize();
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::PivotAndSize<char>& v )
{
	return o << static_cast<int>( v.GetPivot() ) << "   " << static_cast<int>( v.GetSize() );
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::PivotAndSize<unsigned char>& v )
{
	return o << static_cast<int>( v.GetPivot() ) << "   " << static_cast<int>( v.GetSize() );
}