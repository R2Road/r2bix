#include "vector2_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "r2bix/r2bix_Vector2.h"

namespace vector2_test
{
	std::ostream& operator<<( std::ostream& os, const r2bix::Vector2& v )
	{
		os << "x : " << v.x << "     " "y : " << v.y;
		return os;
	}

	r2cm::iItem::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Declaration";
		};
	}
	r2cm::iItem::DoFunctionT Declaration::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix::Vector2 v( 1.f, 1.1f ) );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT OperatorPlus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Operator+";
		};
	}
	r2cm::iItem::DoFunctionT OperatorPlus::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
			DECLARATION_MAIN( const r2bix::Vector2 v1( 1.f, 1.1f ) );
			DECLARATION_MAIN( const r2bix::Vector2 v2( 2.1f, 0.f ) );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto v3 = v1 + v2 );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v3 );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}

	r2cm::iItem::TitleFunctionT OperatorPlusEqual::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Operator+=";
		};
	}
	r2cm::iItem::DoFunctionT OperatorPlusEqual::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Vector2 v1( 3.f, .2f ) );
			DECLARATION_MAIN( const r2bix::Vector2 v2( 1.4f, 1.3f ) );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( v1 += v2 );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v1 );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT OperatorMinus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Operator-";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMinus::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix::Vector2 v1( 1.f, 1.1f ) );
			DECLARATION_MAIN( const r2bix::Vector2 v2( 2.1f, 0.f ) );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto v3 = v1 - v2 );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v3 );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}

	r2cm::iItem::TitleFunctionT OperatorMinusEqual::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Operator-=";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMinusEqual::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Vector2 v1( 3.f, .2f ) );
			DECLARATION_MAIN( const r2bix::Vector2 v2( 1.4f, 1.3f ) );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( v1 -= v2 );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v1 );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT OperatorMultiply_With_Scalar::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Operator* Scalar";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMultiply_With_Scalar::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix::Vector2 v1( 1.f, 1.1f ) );
			DECLARATION_MAIN( const float scalar = 3.f );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto v3 = v1 * scalar );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v3 );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}

	r2cm::iItem::TitleFunctionT OperatorMultiplyEqual_With_Scalar::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector2 : Operator*= Scalar";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMultiplyEqual_With_Scalar::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Vector2 v1( 1.f, 1.1f ) );
			DECLARATION_MAIN( const float scalar = 3.f );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( v1 *= scalar );

				std::cout << r2cm::linefeed;

				OUTPUT_VALUE( v1 );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}