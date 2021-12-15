#include "pe.hpp"


namespace util {
	c_pe::import_list c_pe::get_imports( ) {
		c_pe::import_list import_modules;

		auto import_dir = this->get_dir( IMAGE_DIRECTORY_ENTRY_IMPORT );
		if ( import_dir.VirtualAddress == 0 || import_dir.Size == 0 )
			return import_modules;

		auto import_table = reinterpret_cast< ::PIMAGE_IMPORT_DESCRIPTOR >( this->get_image_base( ) + import_dir.VirtualAddress );

		for ( std::uint32_t previous_name = 0;
			previous_name < import_table->Name;
			previous_name = import_table->Name, ++import_table ) {
			auto module_name = std::string( reinterpret_cast< char* >( uintptr_t( m_base ) + import_table->Name ) );

			if ( module_name.empty( ) ) // probably shoud be handled somehow ?
				continue;

			auto entry = reinterpret_cast< ::PIMAGE_THUNK_DATA32 >( uintptr_t( m_base ) + import_table->OriginalFirstThunk );
			for ( std::uintptr_t index = 0; entry->u1.AddressOfData; index += sizeof( std::uint32_t ), ++entry ) {
				auto import_by_name = reinterpret_cast< ::PIMAGE_IMPORT_BY_NAME >( uintptr_t( m_base ) + entry->u1.AddressOfData );

				auto& data = import_modules[ module_name ].emplace_back( );
				data.function_rva = import_table->FirstThunk + index;

				if ( entry->u1.Ordinal < IMAGE_ORDINAL_FLAG32 && import_by_name->Name[ 0 ] ) {
					data.name = reinterpret_cast< const char* >( import_by_name->Name ); // IMPORT BY NAME
				} else {
					data.ordinal = IMAGE_ORDINAL32( entry->u1.AddressOfData ); // IMPORT BY ORDINAL
				}
			}
		}

		return import_modules;
	}
}