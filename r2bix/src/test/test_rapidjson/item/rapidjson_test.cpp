#include "rapidjson_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace rapidjson_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Rapidjson : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_NOTE( "Copy From : https://github.com/Tencent/rapidjson" );

			std::cout << r2cm::split;

			DECLARATION_MAIN( rapidjson::Document d );

			std::cout << r2cm::split;
			{
				// 1. Parse a JSON string into DOM.
				DECLARATION_MAIN( const char* json = "{ \"project\":\"rapidjson\", \"stars\":10 }" );
				PROCESS_MAIN( d.Parse( json ) );

				std::cout << r2cm::linefeed;

				// 2. Modify it by DOM.
				DECLARATION_MAIN( rapidjson::Value& s = d["stars"] );
				PROCESS_MAIN( s.SetInt( s.GetInt() + 1 ) );

				std::cout << r2cm::linefeed;

				// 3. Stringify the DOM
				DECLARATION_MAIN( rapidjson::StringBuffer buffer );
				DECLARATION_MAIN( rapidjson::Writer<rapidjson::StringBuffer> writer( buffer ) );
				PROCESS_MAIN( d.Accept( writer ) );

				std::cout << r2cm::linefeed;

				// 4. Output {"project":"rapidjson","stars":11}
				OUTPUT_VALUE( buffer.GetString() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}