#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void memory_anomaly( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::logger::info( "\tbase_address: 0x%p", reader.read<uint64_t>( ) );
		util::logger::info( "\tregion_size: 0x%x", reader.read<uint32_t>( ) );
		util::logger::info( "\tmemory_info: %x", reader.read<uint32_t>( ) );
	}
}
