#include "test_component.h"

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
#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UIPannelComponent.h"
#include "r2bix_Camera.h"
#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"
#include "helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "test/2d/TextureFrameAnimationTable4Test.h"
#include "test/2d/TextureTable4Test.h"


namespace test_component
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

			OUT_NOTE( "ComponentStaticID는 Type 당 1개 할당된다." );

			LS();

			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECL_MAIN( auto transform_1 = r2bix_component::ComponentStaticID<r2bix_component::TransformComponent>::Get() );
			DECL_MAIN( auto transform_2 = r2bix_component::ComponentStaticID<r2bix_component::TransformComponent>::Get() );
			DECL_MAIN( auto tex_render_1 = r2bix_component::ComponentStaticID<r2bix_component::TextureRenderComponent>::Get() );
			DECL_MAIN( auto tex_render_2 = r2bix_component::ComponentStaticID<r2bix_component::TextureRenderComponent>::Get() );

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
				OUT_VALUE( transform_1 );
				OUT_VALUE( transform_2 );
				OUT_VALUE( tex_render_1 );
				OUT_VALUE( tex_render_2 );
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

			OUT_NOTE( "같은 Type의 Component를 2개 갖지 못한다." );

			LS();

			DECL_MAIN( r2bix::Director dummy_director( {} ) );
			DECL_MAIN( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			{
				EXPECT_FALSE( node->GetComponent<r2bix_component::TextureRenderComponent>() );
			}

			LS();

			{
				OUT_SUBJECT( "Component 추가" );

				LF();

				EXPECT_TRUE( node->AddComponent<r2bix_component::TextureRenderComponent>() );
			}

			LS();

			{
				OUT_SUBJECT( "중복 추가 시도" );

				LF();

				EXPECT_FALSE( node->AddComponent<r2bix_component::TextureRenderComponent>() );
			}

			LS();

			{
				OUT_SUBJECT( "Get" );

				LF();

				EXPECT_TRUE( node->GetComponent<r2bix_component::TextureRenderComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Transform_Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Transform Component : Basic";
		};
	}
	r2tm::DoFunctionT Transform_Basic::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			OUT_NOTE( "Node 는 생성 과정에서 Transform Component를 생성 한다." );

			LS();

			DECL_MAIN( r2bix::Director dummy_director( {} ) );
			DECL_MAIN( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			{
				OUT_SUBJECT( "TransformComponent를 직접 생성할 필요 없다." );

				LF();

				EXPECT_TRUE( node->GetComponent<r2bix_component::TransformComponent>() );
			}

			LS();

			{
				OUT_SUBJECT( "Node는 TransformComponent를 Public 멤버로 가지고 있다." );

				LF();

				EXPECT_TRUE( node->mTransformComponent );
			}

			LS();

			{
				EXPECT_EQ( node->mTransformComponent, node->GetComponent<r2bix_component::TransformComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Transform_PivotPoint::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Transform Component : PivotPoint";
		};
	}
	r2tm::DoFunctionT Transform_PivotPoint::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			OUT_NOTE( "PivotPoint를 변경하면 Callback이 작동한다." );

			LS();

			DECL_MAIN( r2bix::Director dummy_director( {} ) );
			DECL_MAIN( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECL_MAIN( bool b = false );
			DECL_MAIN( r2bix_component::TransformComponent::Slot4PivotPointChanged s );
			PROC_MAIN( s.SetCallback( [&b]( float x, float y )
			{
				OUT_VALUE( x );
				OUT_VALUE( y );

				b = true;
			} ) );

			LS();

			{
				OUT_SUBJECT( "Slot 설정" );

				LF();

				PROC_MAIN( node->mTransformComponent->ConnectSlot4PivotChanged( &s ) );
			}

			LS();

			{
				OUT_SUBJECT( "Slot 설정" );

				LF();

				PROC_MAIN( node->mTransformComponent->SetPivot( 1.f, 2.f ) );

				LF();

				EXPECT_TRUE( b );
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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 6 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			LS();

			{
				EXPECT_EQ( nullptr, component->GetTexture() );

				LF();

				PROC_MAIN( component->SetPivot( 0.5f, 0.5f ) );
			}

			LS();

			{
				PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 6 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, component );

			LS();

			DECL_MAIN( r2bix_render::Texture texture( 3, 3, 'A' ) );
			{
				EXPECT_EQ( nullptr, component->GetTexture() );
				PROC_MAIN( component->SetTexture( &texture ) );
				EXPECT_EQ( &texture, component->GetTexture() );
			}

			LS();

			{
				PROC_MAIN( component->SetPivot( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				render_target.FillCharacterAll( '=' );
				PROC_MAIN( component->SetPivot( 0.5f, 0.5f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				render_target.FillCharacterAll( '=' );
				PROC_MAIN( component->SetPivot( 1.f, 1.f ) );
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

			DECL_SUB( r2bix::Camera camera( 20, 25, 13, 7 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			DECL_MAIN( r2bix_render::Texture texture( 3, 3, "123" "abc" "zxc" ) );
			PROC_MAIN( component->SetTexture( &texture ) );

			LS();

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROC_MAIN( component->SetVisibleRectForced( -4, -2, 1, 1 ) );
				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROC_MAIN( component->ResetVisibleRect() );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 13, 7 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			DECL_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECL_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_NE( nullptr, custom_texture->GetTexture() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROC_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );
			}

			LS();

			{
				PROC_MAIN( custom_texture->GetTexture()->FillCharacterAll( '?' ) );
				PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROC_MAIN( custom_texture->GetTexture()->Reset( "Bla Bla Bla" ) );
				PROC_MAIN( texture_render->ResetVisibleRect() );
				PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 6 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			LS();

			DECL_MAIN( auto label = node->AddComponent<r2bix_component::LabelSComponent>() );
			EXPECT_NE( nullptr, label );
			DECL_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECL_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_EQ( nullptr, label->GetCustomTextureComponent() );
				PROC_MAIN( label->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, label->GetCustomTextureComponent() );

				LF();

				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROC_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROC_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				LF();

				DECL_MAIN( const char* const dummy_text = "Bla\nBla\nBla" );
				PROC_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			LS();

			{
				PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

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

			DECL_SUB( r2bix::Camera camera( 0, 0, 18, 8 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto label = node->AddComponent<r2bix_component::LabelMComponent>() );
			EXPECT_NE( nullptr, label );
			DECL_MAIN( auto custom_texture = node->AddComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, custom_texture );
			DECL_MAIN( auto texture_render = node->AddComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, texture_render );

			LS();

			{
				EXPECT_EQ( nullptr, label->GetCustomTextureComponent() );
				PROC_MAIN( label->SetCustomTextureComponent( custom_texture ) );
				EXPECT_EQ( custom_texture, label->GetCustomTextureComponent() );

				LF();

				EXPECT_EQ( nullptr, label->GetTextureRenderComponent() );
				PROC_MAIN( label->SetTextureRenderComponent( texture_render ) );
				EXPECT_EQ( texture_render, label->GetTextureRenderComponent() );

				LF();

				EXPECT_EQ( nullptr, texture_render->GetTexture() );
				PROC_MAIN( texture_render->SetTexture( custom_texture->GetTexture() ) );
				EXPECT_EQ( custom_texture->GetTexture(), texture_render->GetTexture() );

				LF();

				DECL_MAIN( const char* const dummy_text = "Bla\nBla\n\nBla" );
				PROC_MAIN( label->SetString( dummy_text ) );
				EXPECT_EQ( dummy_text, label->GetString() );
			}

			LS();

			{
				PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 6 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			LF();

			DECL_SUB( r2bix::Director dummy_director( {} ) );

			LF();

			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			LS();

			EXPECT_EQ( nullptr, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			DECL_MAIN( auto component = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );

			LS();

			{
				EXPECT_EQ( nullptr, component->GetTextureFrame() );
			}

			LS();

			{
				PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 6 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			EXPECT_EQ( nullptr, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			
			LF();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_EQ( component, node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );

			LS();

			DECL_MAIN( r2bix_render::Texture texture( 3, 3,
				"123"
				"456"
				"abc"
			) );
			DECL_MAIN( r2bix_render::TextureFrame frame( &texture ) );
			PROC_MAIN( frame.MoveVisibleOrigin( 1, 1 ) );

			LS();

			{
				PROC_MAIN( component->SetTextureFrame( &frame ) );
				EXPECT_NE( nullptr, component->GetTextureFrame() );
				EXPECT_EQ( &frame, component->GetTextureFrame() );
			}

			LS();

			{
				PROC_MAIN( component->SetPivot( 0.f, 0.f ) );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROC_MAIN( component->SetPivot( 1.f, 1.f ) );

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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );

			LS();

			DECL_MAIN( auto tfrc = node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			DECL_MAIN( auto tfac = node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );
			PROC_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				LF();

				PROC_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2bix_animation::eIndex::Walk_1 ) );

				LF();

				PROC_MAIN( tfac->RunAnimation_Once( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2bix_animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2bix_animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			LS();

			{
				const auto current_cursor_point = r2tm::WindowsUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowsUtility::MoveCursorPoint( current_cursor_point );

					PROC_MAIN( node->Update( 0.003f ) );
					PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
					std::cout << "Animation Is Running : " << tfac->IsRunning() << r2tm::linefeed;

					LF();

					r2bix_helper::Printer4Texture::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				LF();

				PROC_MAIN( tfac->StopAnimation() );
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

			DECL_SUB( r2bix::Camera camera( 20, 25, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 20, 26 ) );

			LS();

			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );

			LS();

			DECL_MAIN( auto tfrc = node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			DECL_MAIN( auto tfac = node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );
			PROC_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
			{
				LF();

				PROC_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Idle_1 ) );
				EXPECT_TRUE( tfac->HasAnimation( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( tfac->HasAnimation( r2bix_animation::eIndex::Walk_1 ) );

				LF();

				PROC_MAIN( tfac->RunAnimation_Repeat( r2bix_animation::eIndex::Run_1 ) );
				EXPECT_FALSE( r2bix_animation::eIndex::Idle_1 == tfac->GetCurrentAnimationIndex() );
				EXPECT_TRUE( r2bix_animation::eIndex::Run_1 == tfac->GetCurrentAnimationIndex() );
			}

			LS();

			{
				const auto current_cursor_point = r2tm::WindowsUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowsUtility::MoveCursorPoint( current_cursor_point );

					PROC_MAIN( node->Update( 0.003f ) );
					PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
					std::cout << "Animation Is Running : " << tfac->IsRunning() << r2tm::linefeed;

					LF();

					r2bix_helper::Printer4Texture::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}

				LF();

				PROC_MAIN( tfac->StopAnimation() );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );
				EXPECT_FALSE( component->IsRunning() );
				PROC_MAIN( component->StartAction() );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			{
				DECL_MAIN( auto tick_action = r2bix_action::TickAction::Create() );
				PROC_MAIN( tick_action->SetTickLimit( 1 ) );

				LF();

				EXPECT_FALSE( component->HasAction() );
				PROC_MAIN( component->SetAction( std::move( tick_action ) ) );
				EXPECT_TRUE( component->HasAction() );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}






	std::ostream& operator<<( std::ostream& o, const r2bix_ui::eCursorStatus& v )
	{
		o << static_cast< int >( v );
		return o;
	}

	r2tm::TitleFunctionT UIControl::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIControl Component";
		};
	}
	r2tm::DoFunctionT UIControl::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto ui_control = node->AddComponent<r2bix_component::UIControlComponent>() );
			EXPECT_TRUE( nullptr != ui_control );

			LS();

			{
				EXPECT_EQ( 0, ui_control->GetOrder() );

				LF();

				PROC_MAIN( ui_control->SetOrder( 10 ) );
				EXPECT_EQ( 10, ui_control->GetOrder() );
			}

			LS();

			{
				EXPECT_EQ( 0, ui_control->GetWidth() );
				EXPECT_EQ( 0, ui_control->GetHeight() );

				LF();

				PROC_MAIN( ui_control->SetSize( 7, 5 ) );

				LF();

				EXPECT_EQ( 7, ui_control->GetWidth() );
				EXPECT_EQ( 5, ui_control->GetHeight() );
			}

			LS();

			{
				EXPECT_EQ( r2bix_ui::eCursorStatus::None, ui_control->GetState() );
			}

			LS();

			{
				EXPECT_EQ( 0, ui_control->GetSlotCount4CursorResponse() );
				EXPECT_EQ( 0, ui_control->GetSlotCount4KeyResponse() );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 18, 8 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto ui_pannel = node->AddComponent<r2bix_component::UIPannelComponent>() );
			EXPECT_TRUE( nullptr != ui_pannel );
			DECL_MAIN( auto ui_control = node->AddComponent<r2bix_component::UIControlComponent>() );
			EXPECT_NE( nullptr, ui_control );

			LS();

			{
				EXPECT_EQ( nullptr, ui_pannel->GetMyUIControlComponent() );

				LF();

				PROC_MAIN( ui_pannel->SetMyUIControlComponent( ui_control ) );
				EXPECT_EQ( ui_control, ui_pannel->GetMyUIControlComponent() );
			}

			LS();

			{
				PROC_MAIN( ui_pannel->SetSize( 7, 5 ) );

				LF();

				EXPECT_EQ( 7, ui_pannel->GetWidth() );
				EXPECT_EQ( 5, ui_pannel->GetHeight() );

				LF();

				EXPECT_EQ( 7, ui_control->GetWidth() );
				EXPECT_EQ( 5, ui_control->GetHeight() );
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

			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto c = node->AddComponent<r2bix_component::UIPannelComponent>() );

			LS();

			{
				EXPECT_TRUE( dummy_director.GetInputManager().GetListenerContainer4Mouse().empty() );
			}

			LS();

			{
				OUT_SUBJECT( "Activate 호출로 Input Listener 등록" );

				LF();

				PROC_MAIN( c->Activate() );
				EXPECT_FALSE( dummy_director.GetInputManager().GetListenerContainer4Mouse().empty() );
				EXPECT_EQ( *dummy_director.GetInputManager().GetListenerContainer4Mouse().begin(), c->GetListener4Mouse() );
			}

			LS();

			{
				OUT_SUBJECT( "Deactivate 호출로 Input Listener 해제" );

				LF();

				PROC_MAIN( c->Deactivate() );
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

			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto u = node->AddComponent<r2bix_component::UIControlComponent>() );

			LS();

			{
				PROC_MAIN( u->SetSize( 10, 10 ) );
				PROC_MAIN( u->Activate() );
			}

			LS();

			DECL_MAIN( r2bix_component::UIControlComponent::Slot4CursorResponseT slot );
			{
				DECL_MAIN( bool bOver = false; );

				LF();

				OUT_SUBJECT( "Mouse Over, Leave Callback 설정" );

				LF();

				PROC_MAIN( slot.SetCallback( [&bOver]( r2bix_ui::eCursorStatus s )
				{
					switch( s )
					{
					case r2bix_ui::eCursorStatus::CursorOver:
						bOver = true;
						break;
					case r2bix_ui::eCursorStatus::CursorLeave:
						bOver = false;
						break;
					}
				} ) );
				PROC_MAIN( u->ConnectSlot4CursorResponse( &slot ) );

				LF();

				PROC_MAIN( u->OnCursorResponse( r2bix_input::CursorPoint{ 0, 0 } ) );
				EXPECT_TRUE( bOver );
				EXPECT_EQ( r2bix_ui::eCursorStatus::CursorOver, u->GetState() );

				LF();

				PROC_MAIN( u->OnCursorResponse( r2bix_input::CursorPoint{ 1, 1 } ) );
				EXPECT_TRUE( bOver );
				EXPECT_EQ( r2bix_ui::eCursorStatus::CursorMove, u->GetState() );

				LF();

				PROC_MAIN( u->OnCursorResponse( r2bix_input::CursorPoint{ 10, 10 } ) );
				EXPECT_FALSE( bOver );
				EXPECT_EQ( r2bix_ui::eCursorStatus::CursorLeave, u->GetState() );

				LF();

				PROC_MAIN( u->OnCursorResponse( r2bix_input::CursorPoint{ 10, 10 } ) );
				EXPECT_FALSE( bOver );
				EXPECT_EQ( r2bix_ui::eCursorStatus::None, u->GetState() );

				LF();

				PROC_MAIN( u->OnCursorResponse( r2bix_input::CursorPoint{ 9, 9 } ) );
				EXPECT_TRUE( bOver );
				EXPECT_EQ( r2bix_ui::eCursorStatus::CursorOver, u->GetState() );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 18, 8 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto ui_button = node->AddComponent<r2bix_component::UIButtonComponent>() );
			EXPECT_TRUE( nullptr != ui_button );
			DECL_MAIN( auto ui_control = node->AddComponent<r2bix_component::UIControlComponent>() );
			EXPECT_TRUE( nullptr != ui_control );

			LS();

			{
				EXPECT_EQ( nullptr, ui_button->GetMyUIControlComponent() );

				LF();

				PROC_MAIN( ui_button->SetMyUIControlComponent( ui_control ) );
				EXPECT_EQ( ui_control, ui_button->GetMyUIControlComponent() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}