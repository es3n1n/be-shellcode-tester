#include "hooks/hooks.hpp"
#include "battleye/reports.hpp"


namespace hooks {
	void send_report( uint8_t* buffer, size_t size, bool unk ) {
		std::vector<uint8_t> report( size - 1 );
		memcpy( report.data( ), buffer + 1, size - 1 );

		util::logger::info( "Got %d size report", report.size( ) );
		//__debugbreak( );
		battleye::reports::execute_handler( report.data( ), report.size( ) );
	}
}
