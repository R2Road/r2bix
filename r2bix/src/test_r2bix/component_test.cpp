#include "pch.h"
#include "component_test.h"

#include <conio.h>
#include <Windows.h>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameAnimationComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

#include "test_r2bix/TextureFrameAnimationTable4Test.h"
#include "test_r2bix/TextureTable4Test.h"
#include "test_r2bix/Utility4Test.h"

namespace component_test
{
	r2cm::iItem::TitleFuncT ComponentID::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component ID";
		};
	}
	r2cm::iItem::DoFuncT ComponentID::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto transform_1 = r2component::TransformComponent::Create( *node ) );
			DECLARATION_MAIN( auto transform_2 = r2component::TransformComponent::Create( *node ) );
			DECLARATION_MAIN( auto tex_render_1 = r2component::TextureRenderComponent::Create( *node ) );
			DECLARATION_MAIN( auto tex_render_2 = r2component::TextureRenderComponent::Create( *node ) );

			std::cout << r2::split;

			{
				EXPECT_EQ( transform_1->GetStaticID(), transform_2->GetStaticID() );
				EXPECT_EQ( transform_1->GetStaticID(), r2base::ComponentStaticID<r2component::TransformComponent>::Get() );

				std::cout << r2::linefeed2;

				EXPECT_EQ( tex_render_1->GetStaticID(), tex_render_2->GetStaticID() );
				EXPECT_EQ( tex_render_1->GetStaticID(), r2base::ComponentStaticID<r2component::TextureRenderComponent>::Get() );
				EXPECT_NE( tex_render_1->GetStaticID(), transform_1->GetStaticID() );
			}

			std::cout << r2::split;

			{
				std::cout << "transform_1->GetStaticID();" << " : " << transform_1->GetStaticID() << r2::linefeed;
				std::cout << "transform_2->GetStaticID();" << " : " << transform_2->GetStaticID() << r2::linefeed;
				std::cout << "tex_render_1->GetStaticID();" << " : " << tex_render_1->GetStaticID() << r2::linefeed;
				std::cout << "tex_render_2->GetStaticID();" << " : " << tex_render_2->GetStaticID() << r2::linefeed;
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Component_Add_Get::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component : Add, Get";
		};
	}
	r2cm::iItem::DoFuncT Component_Add_Get::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( r2base::Director dummy_director );
			DECLARATION_MAIN( auto node = r2base::Node::Create( dummy_director ) );

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );

				std::cout << r2::linefeed;

				EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );
				EXPECT_FALSE( node->AddComponent<r2component::TextureRenderComponent>() );

				std::cout << r2::linefeed;

				EXPECT_TRUE( node->GetComponent<r2component::TextureRenderComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 1";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, component->GetTexture() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 2";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_2::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			std::cout << r2::split;

			DECLARATION_MAIN( r2render::Texture texture( 3, 3, 'A' ) );
			{
				EXPECT_EQ( nullptr, component->GetTexture() );
				PROCESS_MAIN( component->SetTexture( &texture ) );
				EXPECT_EQ( &texture, component->GetTexture() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->SetPivotPoint( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			{
				render_target.FillAll( '=' );
				PROCESS_MAIN( component->SetPivotPoint( 0.5f, 0.5f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			{
				render_target.FillAll( '=' );
				PROCESS_MAIN( component->SetPivotPoint( 1.f, 1.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 3";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_3::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureRenderComponent>() );
			DECLARATION_MAIN( r2render::Texture texture( 3, 3, "123" "abc" "zxc" ) );
			PROCESS_MAIN( component->SetTexture( &texture ) );

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->SetVisibleRectForced( -4, -2, 1, 1 ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT LabelComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label Component";
		};
	}
	r2cm::iItem::DoFuncT LabelComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto label = node->AddComponent<r2component::LabelComponent>() );
			EXPECT_NE( nullptr, label );
			DECLARATION_MAIN( auto texture_render = node->AddComponent<r2component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROCESS_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				std::cout << r2::linefeed;

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROCESS_MAIN( texture_render->SetTexture( label->GetTexture() ) );
				EXPECT_EQ( label->GetTexture(), texture_render->GetTexture() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const char* const dummy_text = "Bla Bla Bla" );
				PROCESS_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureFrameRenderComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component 1";
		};
	}
	r2cm::iItem::DoFuncT TextureFrameRenderComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2component::TextureFrameRenderComponent>() );

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, component->GetTextureFrame() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureFrameRenderComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component";
		};
	}
	r2cm::iItem::DoFuncT TextureFrameRenderComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureFrameRenderComponent>() );
			
			std::cout << r2::linefeed;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2component::TextureFrameRenderComponent>() );

			std::cout << r2::split;

			DECLARATION_MAIN( r2render::Texture texture( 3, 3,
				"123"
				"456"
				"abc"
			) );
			DECLARATION_MAIN( r2render::TextureFrame frame( &texture ) );
			PROCESS_MAIN( frame.MoveVisibleOrigin( 1, 1 ) );

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, component->GetTextureFrame() );
				PROCESS_MAIN( component->SetTextureFrame( &frame ) );
				EXPECT_NE( nullptr, component->GetTextureFrame() );
				EXPECT_EQ( &frame, component->GetTextureFrame() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureFrameAnimationComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameAnimation Component";
		};
	}
	r2cm::iItem::DoFuncT TextureFrameAnimationComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 17, 22 ) );

			std::cout << r2::split;

			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameAnimationComponent>() );

			std::cout << r2::split;

			DECLARATION_MAIN( auto tfrc = node->GetComponent<r2component::TextureFrameRenderComponent>() );
			DECLARATION_MAIN( auto tfac = node->GetComponent<r2component::TextureFrameAnimationComponent>() );
			PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				std::cout << r2::linefeed;

				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2animation::eIndex::Walk_1 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( tfac->RunAnimation( r2animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			std::cout << r2::split;

			{
				CONSOLE_SCREEN_BUFFER_INFO csbi{};
				GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
				while( true )
				{
					SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), csbi.dwCursorPosition );

					PROCESS_MAIN( node->Update( 0.003f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

					std::cout << r2::linefeed;

					Utility4Test::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				std::cout << r2::linefeed;

				PROCESS_MAIN( tfac->StopAnimation() );
				EXPECT_EQ( r2animation::eIndex::None, tfac->GetCurrentAnimationIndex() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}