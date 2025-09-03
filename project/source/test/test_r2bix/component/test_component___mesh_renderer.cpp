#include "test_component___mesh_renderer.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "r2bix_component_StaticMeshComponent.h"
#include "r2bix_component_MeshRendererComponent.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"


namespace test_component___mesh_renderer
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mesh Renderer Component : Basic";
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

			DECL_MAIN( auto s = node->AddComponent<r2bix_component::StaticMeshComponent>() );
			EXPECT_TRUE( nullptr != s );
			DECL_MAIN( auto r = node->AddComponent<r2bix_component::MeshRendererComponent>() );
			EXPECT_TRUE( nullptr != r );

			LS();

			{
				EXPECT_EQ( nullptr, r->GetStaticMesh() );

				LF();

				PROC_MAIN( r->SetStaticMesh( s ) );
				EXPECT_NE( nullptr, r->GetStaticMesh() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}