#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace miniaudio_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class EngineConfig : public r2cm::iItem, public r2::SingleTon<EngineConfig>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Sound_Load : public r2cm::iItem, public r2::SingleTon<Sound_Load>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Sound_Play : public r2cm::iItem, public r2::SingleTon<Sound_Play>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Sound_Volume : public r2cm::iItem, public r2::SingleTon<Sound_Volume>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Group_Init : public r2cm::iItem, public r2::SingleTon<Group_Init>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Group_Volume : public r2cm::iItem, public r2::SingleTon<Group_Volume>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Engine_Volume : public r2cm::iItem, public r2::SingleTon<Engine_Volume>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}