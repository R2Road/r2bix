#include "component_test.h"

#include <conio.h>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "r2bix/r2action_TickAction.h"
#include "r2bix/r2bix_Director.h"
#include "r2bix/r2base_Node.h"
#include "r2bix/r2component_CustomTextureComponent.h"
#include "r2bix/r2component_LabelSComponent.h"
#include "r2bix/r2component_LabelMComponent.h"
#include "r2bix/r2component_ActionProcessComponent.h"
#include "r2bix/r2component_TextureFrameAnimationComponent.h"
#include "r2bix/r2component_TextureFrameRenderComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2component_TransformComponent.h"
#include "r2bix/r2render_Camera.h"
#include "r2bix/r2render_Texture.h"
#include "r2bix/r2render_TextureFrame.h"
#include "r2cm/r2cm_WindowUtility.h"

#include "test/test_r2bix/TextureFrameAnimationTable4Test.h"
#include "test/test_r2bix/TextureTable4Test.h"
#include "test/Utility4Test.h"


namespace component_test
{
	r2cm::iItem::TitleFunctionT ComponentID::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component ID";
		};
	}
	r2cm::iItem::DoFunctionT ComponentID::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto transform_1 = r2component::TransformComponent::Create( *node ) );
			DECLARATION_MAIN( auto transform_2 = r2component::TransformComponent::Create( *node ) );
			DECLARATION_MAIN( auto tex_render_1 = r2component::TextureRenderComponent::Create( *node ) );
			DECLARATION_MAIN( auto tex_render_2 = r2component::TextureRenderComponent::Create( *node ) );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( transform_1->GetStaticID(), transform_2->GetStaticID() );
				EXPECT_EQ( transform_1->GetStaticID(), r2base::ComponentStaticID<r2component::TransformComponent>::Get() );

				std::cout << r2cm::linefeed2;

				EXPECT_EQ( tex_render_1->GetStaticID(), tex_render_2->GetStaticID() );
				EXPECT_EQ( tex_render_1->GetStaticID(), r2base::ComponentStaticID<r2component::TextureRenderComponent>::Get() );
				EXPECT_NE( tex_render_1->GetStaticID(), transform_1->GetStaticID() );
			}

			std::cout << r2cm::split;

			{
				std::cout << "transform_1->GetStaticID();" << " : " << transform_1->GetStaticID() << r2cm::linefeed;
				std::cout << "transform_2->GetStaticID();" << " : " << transform_2->GetStaticID() << r2cm::linefeed;
				std::cout << "tex_render_1->GetStaticID();" << " : " << tex_render_1->GetStaticID() << r2cm::linefeed;
				std::cout << "tex_render_2->GetStaticID();" << " : " << tex_render_2->GetStaticID() << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Component_Add_Get::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component : Add, Get";
		};
	}
	r2cm::iItem::DoFunctionT Component_Add_Get::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::Director dummy_director( {} ) );
			DECLARATION_MAIN( auto node = r2base::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );

				std::cout << r2cm::linefeed;

				EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );
				EXPECT_FALSE( node->AddComponent<r2component::TextureRenderComponent>() );

				std::cout << r2cm::linefeed;

				EXPECT_TRUE( node->GetComponent<r2component::TextureRenderComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureRenderComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 1";
		};
	}
	r2cm::iItem::DoFunctionT TextureRenderComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( nullptr, component->GetTexture() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetPivotPoint( 0.5f, 0.5f ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureRenderComponentTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 2";
		};
	}
	r2cm::iItem::DoFunctionT TextureRenderComponentTest_2::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2render::Texture texture( 3, 3, 'A' ) );
			{
				EXPECT_EQ( nullptr, component->GetTexture() );
				PROCESS_MAIN( component->SetTexture( &texture ) );
				EXPECT_EQ( &texture, component->GetTexture() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->SetPivotPoint( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				render_target.FillCharacterAll( '=' );
				PROCESS_MAIN( component->SetPivotPoint( 0.5f, 0.5f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				render_target.FillCharacterAll( '=' );
				PROCESS_MAIN( component->SetPivotPoint( 1.f, 1.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureRenderComponentTest_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 3";
		};
	}
	r2cm::iItem::DoFunctionT TextureRenderComponentTest_3::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 13, 7 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureRenderComponent>() );
			DECLARATION_MAIN( r2render::Texture texture( 3, 3, "123" "abc" "zxc" ) );
			PROCESS_MAIN( component->SetTexture( &texture ) );

			std::cout << r2cm::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->SetVisibleRectForced( -4, -2, 1, 1 ) );
				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->ResetVisibleRect() );
				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CustomTextureComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Custom Texture Component";
		};
	}
	r2cm::iItem::DoFunctionT CustomTextureComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 13, 7 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			std::cout << r2cm::split;

			{
				EXPECT_NE( nullptr, custom_texture->GetTexture() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( custom_texture->GetTexture()->FillCharacterAll( '?' ) );
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( custom_texture->GetTexture()->Reset( "Bla Bla Bla" ) );
				PROCESS_MAIN( texture_render->ResetVisibleRect() );
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LabelSComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label S Component";
		};
	}
	r2cm::iItem::DoFunctionT LabelSComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto label = node->AddComponent<r2component::LabelSComponent>() );
			EXPECT_NE( nullptr, label );
			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( nullptr, label->GetCustomTextureComponent() );
				PROCESS_MAIN( label->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, label->GetCustomTextureComponent() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROCESS_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( const char* const dummy_text = "Bla Bla Bla" );
				PROCESS_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LabelMComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label M Component";
		};
	}
	r2cm::iItem::DoFunctionT LabelMComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 18, 8 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto label = node->AddComponent<r2component::LabelMComponent>() );
			EXPECT_NE( nullptr, label );
			DECLARATION_MAIN( auto custom_texture = node->AddComponent<r2component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( nullptr, label->GetCustomTextureComponent() );
				PROCESS_MAIN( label->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, label->GetCustomTextureComponent() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROCESS_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( const char* const dummy_text = "Bla\nBla\n\nBla" );
				PROCESS_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureFrameRenderComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component 1";
		};
	}
	r2cm::iItem::DoFunctionT TextureFrameRenderComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2cm::linefeed;

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2cm::split;

			EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2component::TextureFrameRenderComponent>() );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( nullptr, component->GetTextureFrame() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureFrameRenderComponentTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component 2";
		};
	}
	r2cm::iItem::DoFunctionT TextureFrameRenderComponentTest_2::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2cm::split;

			EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureFrameRenderComponent>() );
			
			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2component::TextureFrameRenderComponent>() );

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2render::Texture texture( 3, 3,
				"123"
				"456"
				"abc"
			) );
			DECLARATION_MAIN( r2render::TextureFrame frame( &texture ) );
			PROCESS_MAIN( frame.MoveVisibleOrigin( 1, 1 ) );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->SetTextureFrame( &frame ) );
				EXPECT_NE( nullptr, component->GetTextureFrame() );
				EXPECT_EQ( &frame, component->GetTextureFrame() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->SetPivotPoint( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->SetPivotPoint( 1.f, 1.f ) );

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureFrameAnimationComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameAnimation Component 1";
		};
	}
	r2cm::iItem::DoFunctionT TextureFrameAnimationComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2cm::split;

			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameAnimationComponent>() );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto tfrc = node->GetComponent<r2component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto tfac = node->GetComponent<r2component::TextureFrameAnimationComponent>() );
			PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				std::cout << r2cm::linefeed;

				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2bix_animation::eIndex::Walk_1 ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( tfac->RunAnimation_Once( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2bix_animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2bix_animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			std::cout << r2cm::split;

			{
				const auto current_cursor_point = r2cm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2cm::WindowUtility::MoveCursorPoint( current_cursor_point );

					PROCESS_MAIN( node->Update( 0.003f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
					std::cout << "Animation Is Running : " << tfac->IsRunning() << r2cm::linefeed;

					std::cout << r2cm::linefeed;

					Utility4Test::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( tfac->StopAnimation() );
				EXPECT_EQ( r2bix_animation::eIndex::None, tfac->GetCurrentAnimationIndex() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureFrameAnimationComponentTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameAnimation Component 2";
		};
	}
	r2cm::iItem::DoFunctionT TextureFrameAnimationComponentTest_2::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2cm::split;

			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameAnimationComponent>() );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto tfrc = node->GetComponent<r2component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto tfac = node->GetComponent<r2component::TextureFrameAnimationComponent>() );
			PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				std::cout << r2cm::linefeed;

				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2bix_animation::eIndex::Walk_1 ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( tfac->RunAnimation_Repeat( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2bix_animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2bix_animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			std::cout << r2cm::split;

			{
				const auto current_cursor_point = r2cm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2cm::WindowUtility::MoveCursorPoint( current_cursor_point );

					PROCESS_MAIN( node->Update( 0.003f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
					std::cout << "Animation Is Running : " << tfac->IsRunning() << r2cm::linefeed;

					std::cout << r2cm::linefeed;

					Utility4Test::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( tfac->StopAnimation() );
				EXPECT_EQ( r2bix_animation::eIndex::None, tfac->GetCurrentAnimationIndex() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT ActionProcessComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "ActionProcess Component";
		};
	}
	r2cm::iItem::DoFunctionT ActionProcessComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( component->HasAction() );
				EXPECT_FALSE( component->IsRunning() );
				PROCESS_MAIN( component->StartAction() );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto tick_action = r2action::TickAction::Create() );
				PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );

				std::cout << r2cm::linefeed;

				EXPECT_FALSE( component->HasAction() );
				PROCESS_MAIN( component->SetAction( std::move( tick_action ) ) );
				EXPECT_TRUE( component->HasAction() );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}