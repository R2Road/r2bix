#include "node_test.h"

#include "r2cm/r2cm_ostream.h"

#include "r2bix/r2base_Director.h"
#include "r2bix/r2base_Node.h"
#include "r2bix/r2component_CustomTextureComponent.h"
#include "r2bix/r2component_LabelSComponent.h"
#include "r2bix/r2component_TextureFrameAnimationComponent.h"
#include "r2bix/r2component_TextureFrameRenderComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2component_TransformComponent.h"
#include "r2bix/r2node_CustomTextureNode.h"
#include "r2bix/r2node_LabelSNode.h"
#include "r2bix/r2node_LabelMNode.h"
#include "r2bix/r2node_SceneNode.h"
#include "r2bix/r2node_SpriteAnimationNode.h"
#include "r2bix/r2node_SpriteNode.h"
#include "r2cm/r2cm_Inspector.h"

#include "test/Utility4Test.h"

namespace node_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
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



	r2cm::iItem::TitleFunctionT Child::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Node : Child";
		};
	}
	r2cm::iItem::DoFunctionT Child::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2base::Node::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( 0, dummy_node->GetChildCount() );

				std::cout << r2cm::linefeed;

				EXPECT_NE( nullptr, dummy_node->AddChild<r2base::Node>() );
				EXPECT_EQ( 1, dummy_node->GetChildCount() );

				std::cout << r2cm::linefeed;

				EXPECT_NE( nullptr, dummy_node->AddChild<r2base::Node>() );
				EXPECT_EQ( 2, dummy_node->GetChildCount() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Scene::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Scene";
		};
	}
	r2cm::iItem::DoFunctionT Scene::GetDoFunction()
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



	r2cm::iItem::TitleFunctionT LabelS::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label S";
		};
	}
	r2cm::iItem::DoFunctionT LabelS::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::LabelSNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::LabelSComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LabelM::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label M";
		};
	}
	r2cm::iItem::DoFunctionT LabelM::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto dummy_node = r2node::LabelMNode::Create( dummy_director ) );

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2component::LabelSComponent>() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Sprite::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite";
		};
	}
	r2cm::iItem::DoFunctionT Sprite::GetDoFunction()
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



	r2cm::iItem::TitleFunctionT SpriteAnimation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite Animation";
		};
	}
	r2cm::iItem::DoFunctionT SpriteAnimation::GetDoFunction()
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



	r2cm::iItem::TitleFunctionT CustomeTexture::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Custome Texture Node";
		};
	}
	r2cm::iItem::DoFunctionT CustomeTexture::GetDoFunction()
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

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 5, 5, 'S' ) );
				PROCESS_MAIN( node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect() );

				std::cout << r2cm::linefeed;

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				Utility4Test::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}