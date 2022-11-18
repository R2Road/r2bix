#include "vector3_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "r2bix/r2bix_Vector3.h"

namespace vector3_test
{
	std::ostream& operator<<( std::ostream& os, const r2bix::Vector3& v )
	{
		os << "x : " << v.x << "     " "y : " << v.y << "     " "z : " << v.z;
		return os;
	}

	r2cm::iItem::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Vector3 : Declaration";
		};
	}
	r2cm::iItem::DoFunctionT Declaration::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix::Vector3 v( 1.f, 1.1f, 2.2f ) );

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
			return "Vector3 : Operator+";
		};
	}
	r2cm::iItem::DoFunctionT OperatorPlus::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
			DECLARATION_MAIN( const r2bix::Vector3 v1( 1.f, 1.1f, 2.2f ) );
			DECLARATION_MAIN( const r2bix::Vector3 v2( 2.1f, 0.f, 2.f ) );

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
			return "Vector3 : Operator+=";
		};
	}
	r2cm::iItem::DoFunctionT OperatorPlusEqual::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Vector3 v1( 3.f, .2f, 1.2f ) );
			DECLARATION_MAIN( const r2bix::Vector3 v2( 1.4f, 1.3f, 1.5f ) );

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
			return "Vector3 : Operator-";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMinus::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix::Vector3 v1( 1.f, 1.1f, 2.2f ) );
			DECLARATION_MAIN( const r2bix::Vector3 v2( 2.1f, 0.f, 2.f ) );

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
			return "Vector3 : Operator-=";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMinusEqual::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Vector3 v1( 3.f, .2f, 1.2f ) );
			DECLARATION_MAIN( const r2bix::Vector3 v2( 1.4f, 1.3f, 1.5f ) );

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
			return "Vector3 : Operator* Scalar";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMultiply_With_Scalar::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix::Vector3 v1( 1.f, 1.1f, 2.2f ) );
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
			return "Vector3 : Operator*= Scalar";
		};
	}
	r2cm::iItem::DoFunctionT OperatorMultiplyEqual_With_Scalar::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Vector3 v1( 1.f, 1.1f, 2.2f ) );
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