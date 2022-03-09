#include "pch.h"
#include "component_test.h"

#include <Windows.h>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"

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

			r2base::Director dummy_director;
			auto dummy_node = r2base::Node::Create( dummy_director );
			auto transform_1 = r2component::TransformComponent::Create( *dummy_node );
			auto transform_2 = r2component::TransformComponent::Create( *dummy_node );
			auto texture_render_1 = r2component::TextureRenderComponent::Create( *dummy_node );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "auto transform_1 = r2component::TransformComponent::Create( *dummy_node );" << r2::linefeed;
				std::cout << r2::tab << "auto transform_2 = r2component::TransformComponent::Create( *dummy_node );" << r2::linefeed;
				std::cout << r2::tab << "auto texture_render_1 = r2component::TextureRenderComponent::Create( *dummy_node );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << "transform_1->GetStaticID();" << " > " << transform_1->GetStaticID() << r2::linefeed;
				EXPECT_EQ( transform_1->GetStaticID(), r2base::ComponentStaticID<r2component::TransformComponent>::Get() );
				EXPECT_EQ( transform_1->GetStaticID(), transform_2->GetStaticID() );

				std::cout << r2::linefeed2;

				std::cout << "texture_render_1->GetStaticID();" << " > " << texture_render_1->GetStaticID() << r2::linefeed;
				EXPECT_EQ( texture_render_1->GetStaticID(), r2base::ComponentStaticID<r2component::TextureRenderComponent>::Get() );
				EXPECT_NE( texture_render_1->GetStaticID(), transform_1->GetStaticID() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT GetComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetComponent";
		};
	}
	r2cm::iItem::DoFuncT GetComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto dummy_node = r2base::Node::Create( dummy_director );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed;
				std::cout << r2::tab << "auto dummy_node = r2base::Node::Create( dummy_director );" << r2::linefeed2;
			}

			std::cout << r2::split;

			{
				EXPECT_NE( nullptr, dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_EQ( dummy_node->mTransformComponent, dummy_node->GetComponent<r2component::TransformComponent>() );

				EXPECT_EQ( nullptr, dummy_node->GetComponent<r2component::TextureRenderComponent>() );
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

			r2render::Camera camera( { 5, 5 }, { 11, 11 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			r2base::Director dummy_director;
			auto dummy_node = r2base::Node::Create( dummy_director );
			{
				auto component = r2component::TextureRenderComponent::Create( *dummy_node );
				component->SetRect( 0, 0, 4, 4 );
				dummy_node->AddComponent( std::move( component ) );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2render::Camera camera( { 5, 5 }, { 11, 11 } );" << r2::linefeed;
				std::cout << r2::tab << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );" << r2::linefeed2;

				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;

				std::cout << r2::tab << "auto dummy_node = r2base::Node::Create( dummy_director );" << r2::linefeed2;

				std::cout << r2::tab << "auto component = r2component::TextureRenderComponent::Create( *dummy_node );" << r2::linefeed;
				std::cout << r2::tab << "component->SetRect( 0, 0, 4, 4 );" << r2::linefeed;
				std::cout << r2::tab << "dummy_node->AddComponent( std::move( component ) );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, dummy_node->GetComponent<r2component::TextureRenderComponent>()->GetTexture() );
			}

			std::cout << r2::split;

			{
				dummy_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << "+ Process" << r2::linefeed2;
				std::cout << r2::tab << "dummy_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 29 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 44 } );
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

			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			r2base::Director dummy_director;
			r2render::Texture dummy_texture( 5, 5, '+' );
			auto dummy_node = r2base::Node::Create( dummy_director );
			{
				dummy_node->mTransformComponent->SetPosition( 20, 25 );

				auto component = r2component::TextureRenderComponent::Create( *dummy_node );
				component->SetTexture( &dummy_texture );
				component->SetRect( 0, 0, 4, 4 );
				dummy_node->AddComponent( std::move( component ) );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed;
				std::cout << r2::tab << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );" << r2::linefeed2;

				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed2;

				std::cout << r2::tab << "r2render::Texture dummy_texture( 5, 5, '+' );" << r2::linefeed2;

				std::cout << r2::tab << "auto dummy_node = r2base::Node::Create( dummy_director );" << r2::linefeed;
				std::cout << r2::tab << "dummy_node->mTransformComponent->SetPosition( 20, 25 );" << r2::linefeed2;

				std::cout << r2::tab << "auto component = r2component::TextureRenderComponent::Create( *dummy_node ); ..." << r2::linefeed;
				std::cout << r2::tab << "component->SetTexture( &dummy_texture );; ..." << r2::linefeed;
				std::cout << r2::tab << "..." << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_NE( nullptr, dummy_node->GetComponent<r2component::TextureRenderComponent>()->GetTexture() );
			}

			std::cout << r2::split;

			{
				dummy_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );

				std::cout << "+ Process" << r2::linefeed2;
				std::cout << r2::tab << "dummy_node->Render( &camera, &render_target, r2::PointInt::GetZERO() );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 32 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}