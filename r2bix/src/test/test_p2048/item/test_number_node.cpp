#include "pch.h"
#include "test_number_node.h"

#include <algorithm>	

#include "r2bix/r2base_Director.h"
#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"
#include "r2bix/r2render_Camera.h"
#include "r2bix/r2render_Texture.h"

#include "test/Utility4Test.h"

#include "p2048/p2048_NumberComponent.h"
#include "p2048/p2048_NumberNode.h"
#include "p2048/p2048table_TextureTable.h"

namespace test_number_node
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Number Node : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			p2048table::TextureTable::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 13, 5 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::split;

			DECLARATION_MAIN( auto number_node = p2048::NumberNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, number_node->GetComponent<r2component::TransformComponent>() );
			EXPECT_NE( nullptr, number_node->GetComponent<p2048::NumberComponent>() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( number_node->GetComponent<p2048::NumberComponent>()->SetNumber( 8 ) );
				PROCESS_MAIN( number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( number_node->GetComponent<p2048::NumberComponent>()->SetNumber( 2048 ) );
				PROCESS_MAIN( number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}