#include "test_p2048_stageviewnode.h"

#include "r2bix_Director.h"
#include "r2bix_Camera.h"
#include "helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "project/2048/game/p2048_Stage.h"
#include "project/2048/game/p2048_StageViewComponent.h"
#include "project/2048/game/p2048_StageViewNode.h"
#include "project/2048/game/p2048table_TextureTable.h"


namespace test_p2048_stageviewnode
{
	r2tm::TitleFunctionT Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "StageViewNode : Generate";
		};
	}
	r2tm::DoFunctionT Generate::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_SUB( r2bix::Camera_deprecated camera( 0, 0, 41, 21 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '-' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECL_MAIN( auto stage_view_node = p2048::StageViewNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, stage_view_node->GetComponent<p2048::StageViewComponent>() );

			LS();

			{
				PROC_MAIN( stage_view_node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Setup_Render::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "StageViewNode : Setup And Render";
		};
	}
	r2tm::DoFunctionT Setup_Render::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			p2048table::TextureTable::GetInstance().Load();

			LS();

			DECL_SUB( r2bix::Camera_deprecated camera( 0, 0, 41, 21 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '-' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECL_MAIN( p2048::Stage stage( 4, 4 ) );
			PROC_MAIN( stage.Add( 0, 0, 32 ) );
			PROC_MAIN( stage.Add( 0, 1, 64 ) );
			PROC_MAIN( stage.Add( 3, 0, 512 ) );
			PROC_MAIN( stage.Add( 0, 3, 1024 ) );
			PROC_MAIN( stage.Add( 3, 3, 2048 ) );

			LF();

			DECL_MAIN( auto svn = p2048::StageViewNode::Create( dummy_director ) );
			DECL_MAIN( auto svc = svn->GetComponent<p2048::StageViewComponent>() );
			PROC_MAIN( svc->Setup( stage ) );
			PROC_MAIN( svn->GetComponent<r2bix_component::TransformComponent>()->SetPosition( -svc->GetWidth() * 0.5f, -svc->GetHeight() * 0.5f ) );

			LS();

			{
				PROC_MAIN( svn->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UpdateView::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "StageViewNode : UpdateView";
		};
	}
	r2tm::DoFunctionT UpdateView::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			p2048table::TextureTable::GetInstance().Load();

			LS();

			DECL_SUB( r2bix::Camera_deprecated camera( 0, 0, 41, 21 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '-' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECL_MAIN( p2048::Stage stage( 4, 4 ) );
			PROC_MAIN( stage.Add( 0, 0, 32 ) );
			PROC_MAIN( stage.Add( 0, 1, 64 ) );
			PROC_MAIN( stage.Add( 3, 0, 512 ) );
			PROC_MAIN( stage.Add( 0, 3, 1024 ) );
			PROC_MAIN( stage.Add( 3, 3, 2048 ) );

			LF();

			DECL_MAIN( auto svn = p2048::StageViewNode::Create( dummy_director ) );
			DECL_MAIN( auto svc = svn->GetComponent<p2048::StageViewComponent>() );
			PROC_MAIN( svc->Setup( stage ) );
			PROC_MAIN( svc->UpdateView() );
			PROC_MAIN( svn->GetComponent<r2bix_component::TransformComponent>()->SetPosition( -svc->GetWidth() * 0.5f, -svc->GetHeight() * 0.5f ) );

			LS();

			{
				PROC_MAIN( svn->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}