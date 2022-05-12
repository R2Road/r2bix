#include "node_test.h"

#include "r2cm/r2cm_constant.h"

#include "r2bix/r2base_Director.h"
#include "r2bix/r2base_Node.h"
#include "r2bix/r2component_CustomTextureComponent.h"
#include "r2bix/r2component_LabelComponent.h"
#include "r2bix/r2component_TextureFrameAnimationComponent.h"
#include "r2bix/r2component_TextureFrameRenderComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2component_TransformComponent.h"
#include "r2bix/r2node_CustomTextureNode.h"
#include "r2bix/r2node_LabelNode.h"
#include "r2bix/r2node_SceneNode.h"
#include "r2bix/r2node_SpriteAnimationNode.h"
#include "r2bix/r2node_SpriteNode.h"
#include "r2cm/r2cm_Inspector.h"

#include "test/Utility4Test.h"

namespace node_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2base::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Scene::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Scene";
		};
	}
	r2cm::iItem::DoFuncT Scene::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::SceneNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Label::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label";
		};
	}
	r2cm::iItem::DoFuncT Label::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::LabelNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::LabelComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Sprite::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite";
		};
	}
	r2cm::iItem::DoFuncT Sprite::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::SpriteNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureFrameRenderComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT SpriteAnimation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite Animation";
		};
	}
	r2cm::iItem::DoFuncT SpriteAnimation::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::SpriteAnimationNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureFrameRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureFrameAnimationComponent>() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto frame = dummy_node->GetComponent<r2component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto animation = dummy_node->GetComponent<r2component::TextureFrameAnimationComponent>() );
				EXPECT_EQ( frame, animation->GetTextureFrameRenderComponent() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT CustomeTexture::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Custome Texture Node";
		};
	}
	r2cm::iItem::DoFuncT CustomeTexture::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 13, 5 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto node = r2node::CustomTextureNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );

			std::cout << r2cm::split;

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 3, 3, 'T' ) );
				PROCESS_MAIN( node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2cm::linefeed;

				render_target.FillAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 5, 5, 'S' ) );
				PROCESS_MAIN( node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2cm::linefeed;

				render_target.FillAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}