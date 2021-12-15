#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void driver_presence( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::logger::info( "\tDriver: %s", id == enums::e_report_id::REPORT_DRIVER_PRESENCE_BEEP ? "\\\\.\\Beep" : "\\\\.\\Null" );
	}
}
