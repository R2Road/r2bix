#include "test_node___child.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace test_node___child
{
	r2tm::TitleFunctionT Child_Count::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Child : Count";
		};
	}
	r2tm::DoFunctionT Child_Count::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			{
				EXPECT_EQ( 0, dummy_node->GetChildCount() );

				LF();

				EXPECT_NE( nullptr, dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( 1, dummy_node->GetChildCount() );

				LF();

				EXPECT_NE( nullptr, dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( 2, dummy_node->GetChildCount() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Child_Sequence::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Child : Sequence";
		};
	}
	r2tm::DoFunctionT Child_Sequence::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Z���� ū ��尡 ����� �������� �ڸ��Ѵ�." << r2tm::linefeed2;

				DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				LF();

				DECLARATION_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>( 1 ) );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECLARATION_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>( 0 ) );
				EXPECT_EQ( child_2, ( *dummy_node->GetChildContainer().begin() ).get() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ ������ Z�� ��尡 �̹� �ִٸ� ���� �߰��� ���� ���� Z�� ���� ��� ���� ���� �������� �ڸ��Ѵ�." << r2tm::linefeed2;

				DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				LF();

				DECLARATION_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECLARATION_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECLARATION_MAIN( dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_2, ( *( ++dummy_node->GetChildContainer().begin() ) ).get() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ClearAllChild::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Clear All Child";
			};
	}
	r2tm::DoFunctionT ClearAllChild::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

				LS();

				DECLARATION_MAIN( const auto node = r2bix_node::Node::Create( dummy_director ) );

				LS();

				{
					OUTPUT_SUBJECT( "�׽�Ʈ ȯ�� ����" );

					LF();

					PROCESS_MAIN( node->AddChild<r2bix_node::Node>() );
					PROCESS_MAIN( node->AddChild<r2bix_node::Node>() );
				}

				LS();

				{
					OUTPUT_SUBJECT( "ClearAllChild" );

					LF();

					EXPECT_EQ( 2, node->GetChildCount() );

					LF();

					PROCESS_MAIN( node->ClearAllChild() );

					LF();

					EXPECT_EQ( 0, node->GetChildCount() );
				}

				LS();

				return r2tm::eDoLeaveAction::Pause;
			};
	}
}