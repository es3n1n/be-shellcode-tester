#pragma once


namespace battleye::typedefs {
	using shellcode_startup_t = void( * )( uintptr_t a1 /* it should be base addr but idk */, void* send_report_fn, void* get_module_handle_fn, void* get_proc_address_fn, void* a5 /* unknown :shrug: */ );
}
