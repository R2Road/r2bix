#include "pch.h"
#include "test_background_node.h"

#include <algorithm>	
#include <conio.h>
#include <Windows.h>

#include "base/r2base_Director.h"
#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"

#include "test/Utility4Test.h"

#include "p2048/p2048_BackgroundNode.h"
#include "p2048/p2048table_TextureTable.h"

namespace test_background_node
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Background Node : Basic";
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

			DECLARATION_MAIN( auto node = r2node::CustomTextureNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );

			std::cout << r2::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 3, 3, 'T' ) );
				PROCESS_MAIN( node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2::linefeed;

				render_target.FillAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 5, 5, 'S' ) );
				PROCESS_MAIN( node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2::linefeed;

				render_target.FillAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}