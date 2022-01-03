#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void beclient_encrypted( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::hexdump( "", reader.get_buffer( ), reader.get_size( ) );
		reader.skip( reader.get_size( ) );

		// @todo: @es3n1n: decryption
		/*
		snippet from beclient:

		LABEL_53:
		LOWORD(_EAX) = v236 ^ inputParam ^ 0x5979;
		encryption_key = v236 ^ inputParam ^ 0x378E5979;
LABEL_90:
		for ( m = 2; m < 505; ++m )
		{
		  *(int *)((char *)v230 + m) ^= encryption_key;
		  _CL = m % 32;
		  if ( ((encryption_key >> _CL) & 1) != 0 )
		  {
			__asm { rcr     cl, 3 }
			encryption_key *= ~encryption_key;
		  }
LABEL_117:
		  v115 = (*((_BYTE *)&encryption_key + m % 4) & 3) + 4;
		  _ECX = 512 - v115;
		  _EAX = v115 & ~(1 << (char)v113);
		  LOWORD(_EAX) = __ROL2__(_EAX, 2);
		  __asm { rcl     eax, cl }
		  v142 = m == _ECX;
		  if ( m < _ECX )
		  {
			LOWORD(_ECX) = __ROR2__(_ECX + 1, _ECX + 1);
			__asm { rcr     ecx, 9 }
			LOWORD(_ECX) = _ECX ^ 0x8F07;
			LOBYTE(_ECX) = BYTE1(v111) | _ECX;
			_ECX = -_ECX;
			LOBYTE(_ECX) = BYTE1(v111) | _ECX;
			BYTE1(_ECX) = -BYTE1(_ECX);
			LOWORD(_ECX) = v112 | _ECX;
			BYTE1(_ECX) <<= 6;
			v23 = m % 4;
LABEL_94:
			__asm { rcr     ch, cl }
			v24 = *((_BYTE *)&encryption_key + v23) & 3;
			v142 = v24 + m == 0;
			LOBYTE(_ECX) = v24 + m;
			m += v24;
		  }
		  while ( !v142 )
		  {
			_EAX = ++m;
			if ( _EAX >= 505 )
			  goto LABEL_324;
			_DH = 117;
			__asm { rcl     dh, 2 }
			*(int *)((char *)v230 + _EAX) ^= encryption_key;
			_RDX = (_EAX >> 31) & 0x1F;
			_CL = -57;
			__asm { rcr     cl, 4 }
			if ( !((encryption_key >> (_EAX % 32)) & 1) )
			  goto LABEL_117;
			__asm { rcr     rdx, 2Bh }
			encryption_key *= ~encryption_key;
			_ECX = 512 - ((*((_BYTE *)&encryption_key + m % 4) & 3) + 4);
			v142 = m == _ECX;
			if ( m < _ECX )
			{
			  v23 = m % 4;
			  goto LABEL_94;
			}
		  }
		  LOWORD(_EAX) = m + 1;
		}
		*/
	}
}
