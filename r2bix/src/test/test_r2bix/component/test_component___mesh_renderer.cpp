#include "test_component___mesh_renderer.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "r2bix_component_StaticMeshComponent.h"
#include "r2bix_component_MeshRendererComponent.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"


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

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECLARATION_MAIN( auto s = node->AddComponent<r2bix_component::StaticMeshComponent>() );
			EXPECT_TRUE( nullptr != s );
			DECLARATION_MAIN( auto r = node->AddComponent<r2bix_component::MeshRendererComponent>() );
			EXPECT_TRUE( nullptr != r );

			LS();

			{
				EXPECT_EQ( nullptr, r->GetStaticMesh() );

				LF();

				PROCESS_MAIN( r->SetStaticMesh( s ) );
				EXPECT_NE( nullptr, r->GetStaticMesh() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}