#include "test_component___static_mesh.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "r2bix_component_StaticMeshComponent.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "r2printer_std_vector3.hpp"


namespace test_component___static_mesh
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Static Mesh Component : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECL_MAIN( auto c = node->AddComponent<r2bix_component::StaticMeshComponent>() );
			EXPECT_TRUE( nullptr != c );

			LS();

			{
				EXPECT_EQ( 0, c->Size() );
				EXPECT_TRUE( c->IsEmpty() );
			}

			LS();

			{
				OUTPUT_SOURCE_READY_N_BEGIN;
				using V = r2bix_component::StaticMeshComponent::VertexT;
				const auto vs = { V( 0, 10, 0 ), V( 5, 0, 0 ), V( -5, 0, 0 ) };
				OUTPUT_SOURCE_END;

				LF();

				PROC_MAIN( c->SetVertices( vs ) );

				LF();

				EXPECT_EQ( 3, c->Size() );
				EXPECT_FALSE( c->IsEmpty() );

				LF();

				decltype( vs.size() ) i = 0;
				for( const auto& v : vs )
				{
					EXPECT_EQ( v, c->Get()[i] );
					++i;
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}