#include "UIMenu.h"

#include "r2tm/r2tm_Director.h"

#include "r2bix/r2bix_Director.h"

#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_InputKeyboardComponent.h"
#include "r2bix/r2bix_component_RectComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_component_UIButtonComponent.h"
#include "r2bix/r2bix_component_UIControlComponent.h"
#include "r2bix/r2bix_component_UIPannelComponent.h"

#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_RectNode.h"
#include "r2bix/r2bix_node_UIButtonNode.h"
#include "r2bix/r2bix_node_UIPannelNode.h"

#include "r2bix/r2bix_utility_InputUtil.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT UIMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "UI";
	};
}
r2tm::DescriptionFunctionT UIMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT UIMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
			ret->AddItem(
				32
				, []()->const char* { return "UI Test Scene"; }
				, []()->r2tm::eDoLeaveAction
				{
					r2bix::Director director( { 51, 51, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

					//
					// Scene
					//
					r2bix_node::Node* scene;
					{
						auto temp = r2bix_node::Node::Create( director );
						scene = temp.get();

						director.Setup( std::move( temp ) );

						auto input_component = scene->AddComponent<r2bix_component::InputKeyboardComponent>();
						input_component->SetCallback( r2bix_input::eKeyCode::VK_ESCAPE, [&director]( r2bix_input::eKeyStatus )->bool
						{
							director.RequestAbort();
							r2bix_utility::ClearCInputBuffer();

							return false;
						} );

						input_component->Activate();
					}

					//
					// Background
					//
					{
						auto node = scene->AddChild<r2bix_node::CustomTextureNode>();
						node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 50, 50, '#', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
						node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
					}

					//
					// Button Node Test
					//
					{
						//
						// Button 1 : Listener Add Failed Test
						//
						{
							auto btn_node = scene->AddChild<r2bix_node::UIButtonNode>();
							btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
							btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 10, 3 );
						}

						//
						// Button 2 : Listener Add Failed Test
						//
						{
							auto node_1 = scene->AddChild<r2bix_node::Node>();

							auto node_2 = node_1->AddChild<r2bix_node::Node>();

							auto btn_node = node_2->AddChild<r2bix_node::UIButtonNode>();
							btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
							btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 16, 6 );
						}

						//
						// Button 3 : Listener Add Success Test + Pannel Size 0
						//
						{
							auto pn_node = scene->AddChild<r2bix_node::UIPannelNode>();

							auto btn_node = pn_node->AddChild<r2bix_node::UIButtonNode>();
							btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
							btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 22, 9 );
						}

						//
						// Button 4 : Listener Add Success Test + Valid Pannel Size
						//
						{
							auto pn_node = scene->AddChild<r2bix_node::UIPannelNode>();
							pn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 28, 12 );
							pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 15, 7 );
							{
								auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
								rect_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
								rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
									  pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
									, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
									, 'P'
								);
							}

							auto empty_node = pn_node->AddChild<r2bix_node::Node>();

							auto btn_node = empty_node->AddChild<r2bix_node::UIButtonNode>();
							btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 7, 3 );
							btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
							{
								auto rect_node = btn_node->AddChild<r2bix_node::RectNode>();
								rect_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
								rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
									btn_node->GetComponent<r2bix_component::UIButtonComponent>()->GetWidth()
									, btn_node->GetComponent<r2bix_component::UIButtonComponent>()->GetHeight()
								);

								btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetCallback4CursorResponse( [rect_node]( r2bix_ui::eCursorStatus s )->bool
								{
									switch( s )
									{
									case r2bix_ui::eCursorStatus::CursorOver:
										rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
										break;
									case r2bix_ui::eCursorStatus::CursorMove:
										rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
										break;
									case r2bix_ui::eCursorStatus::CursorLeave:
										rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
										break;
									}

									return false;
								} );

								btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetCallback4KeyResponse( [rect_node]( int, r2bix_ui::eKeyStatus s )->bool
								{
									switch( s )
									{
									case r2bix_ui::eKeyStatus::Push:
										rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightAqua );
										break;
									case r2bix_ui::eKeyStatus::Pressed:
										rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightYellow );
										break;
									case r2bix_ui::eKeyStatus::Release:
										rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightPurple );
										break;
									}

									return false;
								} );
							}
						}
					}

					//
					// Process
					//
					director.Run();

					//
					// Terminate
					//
					director.Terminate();

					return r2tm::eDoLeaveAction::None;
				}
			);



		ret->AddSplit();



		ret->AddMenu( 27, R2bixMenu() );
	};
}