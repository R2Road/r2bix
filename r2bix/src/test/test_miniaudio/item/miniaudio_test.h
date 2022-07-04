#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace miniaudio_test
{
	class Engine_Init : public r2cm::iItem, public r2cm::SingleTon<Engine_Init>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Engine_Config : public r2cm::iItem, public r2cm::SingleTon<Engine_Config>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Engine_Volume : public r2cm::iItem, public r2cm::SingleTon<Engine_Volume>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Engine_PlaySound : public r2cm::iItem, public r2cm::SingleTon<Engine_PlaySound>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Engine_Time : public r2cm::iItem, public r2cm::SingleTon<Engine_Time>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};



	class Sound_Init_Load : public r2cm::iItem, public r2cm::SingleTon<Sound_Init_Load>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Sound_Play : public r2cm::iItem, public r2cm::SingleTon<Sound_Play>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Sound_Volume : public r2cm::iItem, public r2cm::SingleTon<Sound_Volume>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Sound_Time : public r2cm::iItem, public r2cm::SingleTon<Sound_Time>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Sound_FadeIn : public r2cm::iItem, public r2cm::SingleTon<Sound_FadeIn>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};



	class Group_Init : public r2cm::iItem, public r2cm::SingleTon<Group_Init>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Group_Volume : public r2cm::iItem, public r2cm::SingleTon<Group_Volume>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Group_Time : public r2cm::iItem, public r2cm::SingleTon<Group_Time>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

}