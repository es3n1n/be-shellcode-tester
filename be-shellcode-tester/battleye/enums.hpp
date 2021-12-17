#pragma once
#include <cstdint>


namespace battleye::enums {
	enum class e_report_id : uint8_t {
		REPORT_UNKNOWN = 0x0,
		REPORT_ENCRYPTED = 0x4B,
		REPORT_GENERAL_INFO = 0x3C,
		REPORT_VEH = 0x31,
		REPORT_MEMORY_ANOMALY = 0x2F,
		REPORT_WINDOW_TITLE = 0x33,
		REPORT_MEMORY_SIGNATURE = 0x35,
		REPORT_DRIVER_PRESENCE_BEEP = 0x3E,
		REPORT_DRIVER_PRESENCE_NULL = 0x3F,
		//REPORT_MEMORY_REGION = 0x21,
		REPORT_BECLIENT_ENCRYPTED = 0x39,
		REPORT_MONO_ASSETS = 0x49
	};

	inline const char* report_id_to_string( e_report_id id ) {
		switch ( id ) {
			case e_report_id::REPORT_BECLIENT_ENCRYPTED:
			case e_report_id::REPORT_ENCRYPTED:
				return "ENCRYPTED";
			case e_report_id::REPORT_GENERAL_INFO:
				return "GENERAL_INFO";
			case e_report_id::REPORT_VEH:
				return "VEH";
			case e_report_id::REPORT_MEMORY_ANOMALY:
				return "MEMORY_ANOMALY";
			case e_report_id::REPORT_WINDOW_TITLE:
				return "WINDOW_TITLE";
			case e_report_id::REPORT_MEMORY_SIGNATURE:
				return "MEMORY_SIGNATURE";
			case e_report_id::REPORT_DRIVER_PRESENCE_NULL:
			case e_report_id::REPORT_DRIVER_PRESENCE_BEEP:
				return "DRIVER_PRESENCE";
			//case e_report_id::REPORT_MEMORY_REGION:
			//	return "MEMORY_REGION";
			case e_report_id::REPORT_MONO_ASSETS:
				return "MONO_ASSETS";
			default:
				return "UNKNOWN";
		}
	}
}
