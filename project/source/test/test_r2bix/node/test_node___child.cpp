#include "test_node___child.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

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

			DECL_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECL_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

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

			DECL_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Z값이 큰 노드가 목록의 뒤쪽으로 자리한다." << r2tm::linefeed2;

				DECL_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				LF();

				DECL_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>( 1 ) );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECL_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>( 0 ) );
				EXPECT_EQ( child_2, ( *dummy_node->GetChildContainer().begin() ).get() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ 동일한 Z의 노드가 이미 있다면 새로 추가된 노드는 같은 Z를 가진 노드 군의 가장 마지막에 자리한다." << r2tm::linefeed2;

				DECL_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				LF();

				DECL_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECL_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECL_MAIN( dummy_node->AddChild<r2bix_node::Node>() );
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

				DECL_SUB( r2bix::Director dummy_director( {} ) );

				LS();

				DECL_MAIN( const auto node = r2bix_node::Node::Create( dummy_director ) );

				LS();

				{
					OUT_SUBJECT( "테스트 환경 설정" );

					LF();

					PROC_MAIN( node->AddChild<r2bix_node::Node>() );
					PROC_MAIN( node->AddChild<r2bix_node::Node>() );
				}

				LS();

				{
					OUT_SUBJECT( "ClearAllChild" );

					LF();

					EXPECT_EQ( 2, node->GetChildCount() );

					LF();

					PROC_MAIN( node->ClearAllChild() );

					LF();

					EXPECT_EQ( 0, node->GetChildCount() );
				}

				LS();

				return r2tm::eDoLeaveAction::Pause;
			};
	}
}