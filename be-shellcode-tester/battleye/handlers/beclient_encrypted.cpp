#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void beclient_encrypted( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::hexdump( reader.get_buffer( ), reader.get_size( ) );
	}
}
