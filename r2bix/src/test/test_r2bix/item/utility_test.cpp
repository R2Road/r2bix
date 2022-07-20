#include "utility_test.h"

#include "r2cm/r2cm_constant.h"
#include "r2cm/r2cm_Inspector.h"

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
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2cm::linefeed;

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
}