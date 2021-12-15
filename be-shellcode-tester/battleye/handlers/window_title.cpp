#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void window_title( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		char buf[ 128 ] = { '\0' };
		reader.read_to( buf, reader.read<uint16_t>( ) );
		util::logger::info( "\ttitle: %s", buf );
	}
}
