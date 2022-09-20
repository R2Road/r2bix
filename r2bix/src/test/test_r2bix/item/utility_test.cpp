#include "utility_test.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Inspector.h"

#include "r2bix/r2utility_StringDecomposition.h"
#include "r2bix/r2utility_StringSize.h"

namespace utility_test
{
	r2cm::iItem::TitleFunctionT StringSize::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Utility : StringSize";
		};
	}
	r2cm::iItem::DoFunctionT StringSize::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( "" ) );
				EXPECT_EQ( 0u, s.width );
				EXPECT_EQ( 0u, s.height );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( "" "\n" ) );
				EXPECT_EQ( 0u, s.width );
				EXPECT_EQ( 2u, s.height );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( "" "\n" "\n" ) );
				EXPECT_EQ( 0u, s.width );
				EXPECT_EQ( 3u, s.height );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( " " ) );
				EXPECT_EQ( 1u, s.width );
				EXPECT_EQ( 1u, s.height );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( "123" ) );
				EXPECT_EQ( 3u, s.width );
				EXPECT_EQ( 1u, s.height );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( "123\n" ) );
				EXPECT_EQ( 3u, s.width );
				EXPECT_EQ( 2u, s.height );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto s = r2utility::StringSize::Calculate( "" "\n" "\n123" "\n4567" "\n" "\nABC" ) );
				EXPECT_EQ( 4u, s.width );
				EXPECT_EQ( 6u, s.height );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT StringDecomposition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Utility : StringDecomposition";
		};
	}
	r2cm::iItem::DoFunctionT StringDecomposition::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const std::string_view token( "\n" ) );
			DECLARATION_MAIN( r2utility::StringDecomposition::ResultContainerT str_list );

			std::cout << r2cm::split;

			const auto printer = []( const r2utility::StringDecomposition::ResultContainerT& result_container )
			{
				std::cout << "<Begin>" << r2cm::linefeed;
				for( const auto& s : result_container )
				{
					std::cout << r2cm::tab << "<";
					if( s.empty() )
					{
						std::cout << "empty";
					}
					else
					{
						std::cout << s;
					}
					std::cout << "> : " << s.size() << r2cm::linefeed;
				}
				std::cout << "<End>" << r2cm::linefeed;
			};

			{
				PROCESS_MAIN( str_list = r2utility::StringDecomposition::Do( token, "" ) );
				printer( str_list );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( str_list = r2utility::StringDecomposition::Do( token, " " ) );
				printer( str_list );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( str_list = r2utility::StringDecomposition::Do( token, "" "\n" ) );
				printer( str_list );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( str_list = r2utility::StringDecomposition::Do( token, "\n" " " ) );
				printer( str_list );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( str_list = r2utility::StringDecomposition::Do( token, "" "\n" "\n123" "\n4567" "\n" "\nABC" ) );
				printer( str_list );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}