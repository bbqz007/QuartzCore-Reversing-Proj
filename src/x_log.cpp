/**
MIT License
Copyright (c) 2016 bbqz007 <https://github.com/bbqz007, http://www.cnblogs.com/bbqzsl>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "typedefs.h"
#include "CA.namespace.h"
#include "CA.struct.h"
#include "CA.ops.h"
#include "OSAtomic.h"
#include "CA.oc.h"

struct va_list_t
{
	int32_t _0;
	int32_t _4;
	void* _8;
	void* _10;
};


void x_logv(int handle, const char* fmt, va_list_t* va_list)
{
	extern dispatch_once_t x_log_once;
	extern ent_off__0x35c8c;
	extern pthread_key_t x_log_stream_slot;
	r14 = va_list;
	rbx = fmt;
	r15d = handle;
	_1038 = 0x0;
	// 55 cmpq $-0x1, 0x35c4d(%rip)
	// 63
	if (ent_off__0x35c8c != -0x1) { // 55 (rip->_35c4d != -0x1)
		// inline goto _f413;
		// 429 call
		dispatch_once_f(&x_log_once, 0, &x_log_init);
		// 434
		goto _b69;
	}
_b69:	// from 434
	eax = handle - 0x1;
	// 76
	if (!(eax > 0x1)) { // 73 (eax > 0x1)
		al = x_log_html;
		// 86
		if (!(0 == al)) { // 84 (0 == al)
			eax = 0;
			// 129 call
			asprintf(&_1038, "<span class=\"%s\">%s</span>", (handle == 0x2) ? rdx : x_log_html, fmt);
			rbx = (eax >= 0) ? _1038 : fmt;
		} // 144
	} // 144
	rdi = x_log_stream_slot;
	// 154
	if (!(0 == x_log_stream_slot)) { // 151 (0 == rdi)
			 // 156 call
		r12 = pthread_getspecific(x_log_stream_slot);
		// 167
		if (!(0 == r12)) { // 164 (0 == r12)
			r15 = &_1030;
			eax = __vsnprintf_chk(&_1030, 0x1000, 0, 0x1000, rbx, va_list);
			// 207
			if (eax > 0xfff) { // 202 (eax > 0xfff)
				// inline jmp 272
			_f272:	// from 207
				// 285 call
				eax = vasprintf(&_1040, rbx, va_list);
				goto _f290;
			}
			else { // 207 next
				_1040 = &_1030;
				// 216
				goto _f290;
			}
		_f290:	// from 216
			// 292
			if (!(0 >= eax)) { // 290 (0 >= eax)
				// 308 call
				x_stream_write(r12->_0, &_1030, eax);
			} // 313
			rdi = _1040;
			// 323
			if (!(_1040 == &_1030)) { // 320 (rdi == r15)
				// 325 call
				free((void*)_1040);
				// 330
				goto _f372;
			} // 372
			goto _f372;
		} // 218
	} // 218

	rax = x_log_function;
	// 228
	if (!(0 == x_log_function)) { // 225 (0 == rax)
		// 243 call
		x_log_function(rbx, va_list, x_log_function_info);
		// 245
		goto _f372;
	} // 247
	rdi = x_log_file_handle;
	// 257
	if (0 == x_log_file_handle) { // 254 (0 == rdi)
		// inline jmp 332
		// 367 call
		asl_vlog(0, 0, (handle != 0x2) ? ((handle != 0x1) | 0x4) : 0x3, rbx, va_list);
		// natural flow 
		goto _f372;
	}
	else { // 257 next
		// 265 call
		vfprintf(x_log_file_handle, rbx, va_list);
		// 270
		goto _f372;
	} // 270 unreachable

_f372:	// from 330
_f372:	// from 270
_f372:	// from 245
	rdi = _1038;
	// 382
	if (!(0 == _1038)) { // 379 (0 == rdi)
			 // 384 call
		free((void*)_1038);
	} // 389
	return;
}