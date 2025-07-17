#include "test_p2048_numbernode.h"

#include "r2bix_Director.h"
#include "r2bix_Camera.h"
#include "helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_Inspector.h"

#include "p2048/p2048_NumberComponent.h"
#include "p2048/p2048_NumberNode.h"


namespace test_p2048_numbernode
{
	r2tm::TitleFunctionT Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "NumberNode : Generate";
		};
	}
	r2tm::DoFunctionT Generate::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 21, 11 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( auto number_node = p2048::NumberNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, number_node->GetComponent<p2048::NumberComponent>() );

			LS();

			{
				PROCESS_MAIN( number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT SetNumber::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "NumberNode : SetNumber";
		};
	}
	r2tm::DoFunctionT SetNumber::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 11, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_MAIN( auto number_node = p2048::NumberNode::Create( dummy_director ) );

			LS();

			{
				PROCESS_MAIN( number_node->GetComponent<p2048::NumberComponent>()->SetNumber( 2048, false, false ) );
				number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
				EXPECT_EQ( r2bix::BG_Black, render_target.GetColor( 1, 1 ) );
				EXPECT_EQ( r2bix::BG_Black | r2bix::FG_Aqua, render_target.GetColor( 6, 2 ) );

				std::cout << r2tm::linefeed2;

				PROCESS_MAIN( number_node->GetComponent<p2048::NumberComponent>()->SetNumber( 1024, true, false ) );
				number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
				EXPECT_EQ( r2bix::BG_Aqua, render_target.GetColor( 1, 1 ) );
				EXPECT_EQ( r2bix::BG_Aqua | r2bix::FG_Black, render_target.GetColor( 6, 2 ) );

				std::cout << r2tm::linefeed2;

				PROCESS_MAIN( number_node->GetComponent<p2048::NumberComponent>()->SetNumber( 512, true, true ) );
				number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
				EXPECT_EQ( r2bix::BG_Aqua, render_target.GetColor( 1, 1 ) );
				EXPECT_EQ( r2bix::BG_Aqua | r2bix::FG_Black, render_target.GetColor( 6, 2 ) );

				std::cout << r2tm::linefeed2;

				PROCESS_MAIN( number_node->GetComponent<p2048::NumberComponent>()->SetNumber( 4096, false, true ) );
				number_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
				EXPECT_EQ( r2bix::BG_Black, render_target.GetColor( 1, 1 ) );
				EXPECT_EQ( r2bix::BG_Black | r2bix::FG_LightYellow, render_target.GetColor( 6, 2 ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}