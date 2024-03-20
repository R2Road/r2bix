#include "component_test.h"

#include <conio.h>

#include "r2bix_action_TickAction.h"
#include "r2bix_Director.h"
#include "r2bix_node_Node.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_LabelMComponent.h"
#include "r2bix_component_ActionProcessComponent.h"
#include "r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_TransformComponent.h"
#include "r2bix_component_UIButtonComponent.h"
#include "r2bix_component_UIPannelComponent.h"
#include "r2bix_render_Camera.h"
#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"
#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

#include "test/test_r2bix/TextureFrameAnimationTable4Test.h"
#include "test/test_r2bix/TextureTable4Test.h"


namespace component_test
{
	std::ostream& operator<<( std::ostream& o, const r2bix_animation::eIndex& i )
	{
		o << "x : " << static_cast<int>( i ) << r2tm::linefeed;
		return o;
	}

	r2tm::TitleFunctionT ComponentID::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component ID";
		};
	}
	r2tm::DoFunctionT ComponentID::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_NOTE( "ComponentStaticID�� Type �� 1�� �Ҵ�ȴ�." );

			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECLARATION_MAIN( auto transform_1 = r2bix_component::ComponentStaticID<r2bix_component::TransformComponent>::Get() );
			DECLARATION_MAIN( auto transform_2 = r2bix_component::ComponentStaticID<r2bix_component::TransformComponent>::Get() );
			DECLARATION_MAIN( auto tex_render_1 = r2bix_component::ComponentStaticID<r2bix_component::TextureRenderComponent>::Get() );
			DECLARATION_MAIN( auto tex_render_2 = r2bix_component::ComponentStaticID<r2bix_component::TextureRenderComponent>::Get() );

			LS();

			{
				EXPECT_EQ( transform_1, transform_2 );
				EXPECT_EQ( transform_1, r2bix_component::ComponentStaticID<r2bix_component::TransformComponent>::Get() );

				std::cout << r2tm::linefeed2;

				EXPECT_EQ( tex_render_1, tex_render_2 );
				EXPECT_EQ( tex_render_1, r2bix_component::ComponentStaticID<r2bix_component::TextureRenderComponent>::Get() );
				EXPECT_NE( tex_render_1, transform_1 );
			}

			LS();

			{
				OUTPUT_VALUE( transform_1 );
				OUTPUT_VALUE( transform_2 );
				OUTPUT_VALUE( tex_render_1 );
				OUTPUT_VALUE( tex_render_2 );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Component_Add_Get::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component : Add, Get";
		};
	}
	r2tm::DoFunctionT Component_Add_Get::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::Director dummy_director( {} ) );
			DECLARATION_MAIN( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			{
				EXPECT_EQ( nullptr, node->GetComponent<r2bix_component::TextureRenderComponent>() );

				LF();

				EXPECT_TRUE( node->AddComponent<r2bix_component::TextureRenderComponent>() );
				EXPECT_FALSE( node->AddComponent<r2bix_component::TextureRenderComponent>() );

				LF();

				EXPECT_TRUE( node->GetComponent<r2bix_component::TextureRenderComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureRender_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 1";
		};
	}
	r2tm::DoFunctionT TextureRender_1::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 6 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			LS();

			{
				EXPECT_EQ( nullptr, component->GetTexture() );

				LF();

				PROCESS_MAIN( component->SetPivotPoint( 0.5f, 0.5f ) );
			}

			LS();

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureRender_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 2";
		};
	}
	r2tm::DoFunctionT TextureRender_2::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 6 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			LS();

			DECLARATION_MAIN( r2bix_render::Texture texture( 3, 3, 'A' ) );
			{
				EXPECT_EQ( nullptr, component->GetTexture() );
				PROCESS_MAIN( component->SetTexture( &texture ) );
				EXPECT_EQ( &texture, component->GetTexture() );
			}

			LS();

			{
				PROCESS_MAIN( component->SetPivotPoint( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				render_target.FillCharacterAll( '=' );
				PROCESS_MAIN( component->SetPivotPoint( 0.5f, 0.5f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				render_target.FillCharacterAll( '=' );
				PROCESS_MAIN( component->SetPivotPoint( 1.f, 1.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureRender_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 3";
		};
	}
	r2tm::DoFunctionT TextureRender_3::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 13, 7 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			DECLARATION_MAIN( r2bix_render::Texture texture( 3, 3, "123" "abc" "zxc" ) );
			PROCESS_MAIN( component->SetTexture( &texture ) );

			LS();

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( component->SetVisibleRectForced( -4, -2, 1, 1 ) );
				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( component->ResetVisibleRect() );
				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CustomTexture::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Custom Texture Component";
		};
	}
	r2tm::DoFunctionT CustomTexture::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 7 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_NE( nullptr, custom_texture->GetTexture() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );
			}

			LS();

			{
				PROCESS_MAIN( custom_texture->GetTexture()->FillCharacterAll( '?' ) );
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( custom_texture->GetTexture()->Reset( "Bla Bla Bla" ) );
				PROCESS_MAIN( texture_render->ResetVisibleRect() );
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT LabelS::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label S Component";
		};
	}
	r2tm::DoFunctionT LabelS::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 6 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			LS();

			DECLARATION_MAIN( auto label = node->AddComponent<r2bix_component::LabelSComponent>() );
			EXPECT_NE( nullptr, label );
			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_EQ( nullptr, label->GetCustomTextureComponent() );
				PROCESS_MAIN( label->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, label->GetCustomTextureComponent() );

				LF();

				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROCESS_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				LF();

				DECLARATION_MAIN( const char* const dummy_text = "Bla\nBla\nBla" );
				PROCESS_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			LS();

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT LabelM::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label M Component";
		};
	}
	r2tm::DoFunctionT LabelM::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 18, 8 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto label = node->AddComponent<r2bix_component::LabelMComponent>() );
			EXPECT_NE( nullptr, label );
			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_EQ( nullptr, label->GetCustomTextureComponent() );
				PROCESS_MAIN( label->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, label->GetCustomTextureComponent() );

				LF();

				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROCESS_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				LF();

				DECLARATION_MAIN( const char* const dummy_text = "Bla\nBla\n\nBla" );
				PROCESS_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			LS();

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureFrameRender_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component 1";
		};
	}
	r2tm::DoFunctionT TextureFrameRender_1::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 6 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			LF();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LF();

			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			LS();

			EXPECT_EQ( nullptr, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );

			LS();

			{
				EXPECT_EQ( nullptr, component->GetTextureFrame() );
			}

			LS();

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureFrameRender_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component 2";
		};
	}
	r2tm::DoFunctionT TextureFrameRender_2::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 6 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			EXPECT_EQ( nullptr, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			
			LF();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );

			LS();

			DECLARATION_MAIN( r2bix_render::Texture texture( 3, 3,
				"123"
				"456"
				"abc"
			) );
			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );
			PROCESS_MAIN( frame.MoveVisibleOrigin( 1, 1 ) );

			LS();

			{
				PROCESS_MAIN( component->SetTextureFrame( &frame ) );
				EXPECT_NE( nullptr, component->GetTextureFrame() );
				EXPECT_EQ( &frame, component->GetTextureFrame() );
			}

			LS();

			{
				PROCESS_MAIN( component->SetPivotPoint( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( component->SetPivotPoint( 1.f, 1.f ) );

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureFrameAnimation_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameAnimation Component 1";
		};
	}
	r2tm::DoFunctionT TextureFrameAnimation_1::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );

			LS();

			DECLARATION_MAIN( auto tfrc = node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto tfac = node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );
			PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				LF();

				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2bix_animation::eIndex::Walk_1 ) );

				LF();

				PROCESS_MAIN( tfac->RunAnimation_Once( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2bix_animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2bix_animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			LS();

			{
				const auto current_cursor_point = r2tm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowUtility::MoveCursorPoint( current_cursor_point );

					PROCESS_MAIN( node->Update( 0.003f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
					std::cout << "Animation Is Running : " << tfac->IsRunning() << r2tm::linefeed;

					LF();

					r2bix_helper::Printer4Texture::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				LF();

				PROCESS_MAIN( tfac->StopAnimation() );
				EXPECT_EQ( r2bix_animation::eIndex::None, tfac->GetCurrentAnimationIndex() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureFrameAnimation_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameAnimation Component 2";
		};
	}
	r2tm::DoFunctionT TextureFrameAnimation_2::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 20, 25, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );

			LS();

			DECLARATION_MAIN( auto tfrc = node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto tfac = node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );
			PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				LF();

				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2bix_animation::eIndex::Walk_1 ) );

				LF();

				PROCESS_MAIN( tfac->RunAnimation_Repeat( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2bix_animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2bix_animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			LS();

			{
				const auto current_cursor_point = r2tm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowUtility::MoveCursorPoint( current_cursor_point );

					PROCESS_MAIN( node->Update( 0.003f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
					std::cout << "Animation Is Running : " << tfac->IsRunning() << r2tm::linefeed;

					LF();

					r2bix_helper::Printer4Texture::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				LF();

				PROCESS_MAIN( tfac->StopAnimation() );
				EXPECT_EQ( r2bix_animation::eIndex::None, tfac->GetCurrentAnimationIndex() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ActionProcess::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "ActionProcess Component";
		};
	}
	r2tm::DoFunctionT ActionProcess::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );
				EXPECT_FALSE( component->IsRunning() );
				PROCESS_MAIN( component->StartAction() );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			{
				DECLARATION_MAIN( auto tick_action = r2bix_action::TickAction::Create() );
				PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );

				LF();

				EXPECT_FALSE( component->HasAction() );
				PROCESS_MAIN( component->SetAction( std::move( tick_action ) ) );
				EXPECT_TRUE( component->HasAction() );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}






	r2tm::TitleFunctionT UIPannel::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIPannel Component";
		};
	}
	r2tm::DoFunctionT UIPannel::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 18, 8 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto ui_pannel = node->AddComponent<r2bix_component::UIPannelComponent>() );
			EXPECT_NE( nullptr, ui_pannel );
			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_EQ( nullptr, ui_pannel->GetCustomTextureComponent() );
				PROCESS_MAIN( ui_pannel->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, ui_pannel->GetCustomTextureComponent() );

				LF();

				EXPECT_EQ( nullptr, ui_pannel->GetTextureRenderComponent() );
				PROCESS_MAIN( ui_pannel->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, ui_pannel->GetTextureRenderComponent() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				LF();

				PROCESS_MAIN( ui_pannel->SetSize( 7, 5, 'x' ));
				EXPECT_EQ( 7, ui_pannel->GetWidth() );
				EXPECT_EQ( 5, ui_pannel->GetHeight() );
			}

			LS();

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UIPannel_InputListener_Regist::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIPannel Component : InputListener Regist";
		};
	}
	r2tm::DoFunctionT UIPannel_InputListener_Regist::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto c = node->AddComponent<r2bix_component::UIPannelComponent>() );

			LS();

			{
				EXPECT_TRUE( dummy_director.GetInputManager().GetListenerContainer4Mouse().empty() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Activate ȣ��� Input Listener ���" );

				LF();

				PROCESS_MAIN( c->Activate() );
				EXPECT_FALSE( dummy_director.GetInputManager().GetListenerContainer4Mouse().empty() );
				EXPECT_EQ( *dummy_director.GetInputManager().GetListenerContainer4Mouse().begin(), c->GetListener4Mouse() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Deactivate ȣ��� Input Listener ����" );

				LF();

				PROCESS_MAIN( c->Deactivate() );
				EXPECT_TRUE( dummy_director.GetInputManager().GetListenerContainer4Mouse().empty() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UIPannel_Cursor_Response::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIPannel Component : Cursor Response";
		};
	}
	r2tm::DoFunctionT UIPannel_Cursor_Response::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto u = node->AddComponent<r2bix_component::UIPannelComponent>() );
			DECLARATION_MAIN( auto t = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			DECLARATION_MAIN( auto r = node->AddComponent<r2bix_component::TextureRenderComponent>() );

			LS();

			{
				PROCESS_MAIN( u->SetCustomTextureComponent( t ) );
				PROCESS_MAIN( u->SetTextureRenderComponent( r ) );
				PROCESS_MAIN( r->SetTexture( t->GetTexture() ) );
				PROCESS_MAIN( u->SetSize( 10, 10 ) );
				PROCESS_MAIN( u->Activate() );
			}

			LS();

			{
				DECLARATION_MAIN( bool bOver = false; );

				LF();

				OUTPUT_SUBJECT( "Mouse Over, Leave Callback ����" );

				LF();

				PROCESS_MAIN( u->SetMouseOverCallback( [&bOver]() { bOver = true; } ) );
				PROCESS_MAIN( u->SetMouseLeaveCallback( [&bOver]() { bOver = false; } ) );

				LF();

				PROCESS_MAIN( u->GetListener4Mouse()->UpdateCursor( r2bix_input::CursorPoint{ 0, 0 } ) );
				EXPECT_TRUE( bOver );
				PROCESS_MAIN( u->GetListener4Mouse()->UpdateCursor( r2bix_input::CursorPoint{ 10, 10 } ) );
				EXPECT_FALSE( bOver );
				PROCESS_MAIN( u->GetListener4Mouse()->UpdateCursor( r2bix_input::CursorPoint{ 9, 9 } ) );
				EXPECT_TRUE( bOver );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UIButton::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIButton Component";
		};
	}
	r2tm::DoFunctionT UIButton::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 18, 8 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto ui_button = node->AddComponent<r2bix_component::UIButtonComponent>() );
			EXPECT_NE( nullptr, ui_button );
			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_EQ( nullptr, ui_button->GetCustomTextureComponent() );
				PROCESS_MAIN( ui_button->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, ui_button->GetCustomTextureComponent() );

				LF();

				EXPECT_EQ( nullptr, ui_button->GetTextureRenderComponent() );
				PROCESS_MAIN( ui_button->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, ui_button->GetTextureRenderComponent() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				LF();

				PROCESS_MAIN( ui_button->SetSize( 7, 5 ) );
				EXPECT_EQ( 7, ui_button->GetWidth() );
				EXPECT_EQ( 5, ui_button->GetHeight() );
			}

			LS();

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}