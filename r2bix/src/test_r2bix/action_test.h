#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace action_test
{
	class ActionProcessComponentTest_With_TickAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_TickAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_DelayAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_DelayAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_SequenceAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_SequenceAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_MoveByAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_MoveByAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_RepeatAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_RepeatAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_BlinkAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_BlinkAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_CallbackAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_CallbackAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class ActionProcessComponentTest_With_AnimationRequestAction : public r2cm::iItem, public r2::SingleTon<ActionProcessComponentTest_With_AnimationRequestAction>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}