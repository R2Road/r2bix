#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace action_test
{
	class TickActionTest : public r2cm::iItem, public r2::SingleTon<TickActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class DelayActionTest : public r2cm::iItem, public r2::SingleTon<DelayActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class SequenceActionTest : public r2cm::iItem, public r2::SingleTon<SequenceActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class MoveByActionTest : public r2cm::iItem, public r2::SingleTon<MoveByActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class RepeatActionTest : public r2cm::iItem, public r2::SingleTon<RepeatActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class BlinkActionTest : public r2cm::iItem, public r2::SingleTon<BlinkActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class CallbackActionTest : public r2cm::iItem, public r2::SingleTon<CallbackActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
	class AnimationRequestActionTest : public r2cm::iItem, public r2::SingleTon<AnimationRequestActionTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}