//#include "battleye/reports.hpp"
//
// @note: es3n1n: this one is broken
//
//namespace battleye::reports::handlers {
//	void memory_region( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
//		reader.skip( 1 );
// 
//		const auto mem_base_addr = reader.read<uint64_t>( );
//		const auto region_size = reader.read<uint32_t>( );
//		const auto type_protect_state = reader.read<uint32_t>( );
//
//		util::logger::info( "\tbase: 0x%p", mem_base_addr );
//		util::logger::info( "\region_size: %x", mem_base_addr );
//		util::logger::info( "\type_protect_state: %x", mem_base_addr );
//
//		// @fixme: unknown zeroes?
//		reader.skip( reader.get_size( ) );
//	}
//}
