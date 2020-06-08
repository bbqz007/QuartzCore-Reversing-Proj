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

CA::Render::Shmem::~Shmem()
{

}

void* CA::Render::Shmem::copy_image(CGColorSpace* colorSpace)
{
	_40 = colorSpace;
	_38 = this;
	CA::Render::ShmemBitmap*& shmemBitmap = r13; // &=r13
	unsigned long*& format_rowbytes_array; // &=r14
	shmemBitmap = this->_18;
	r12d = shmemBitmap->_1c;
	format_rowbytes_array = (unsigned long*)alloca((shmemBitmap->_1c * 8 + f) & -0x10);
	edi = shmemBitmap->_10;
	esi = shmemBitmap->_14;
	// 79
	if (!(0 == shmemBitmap->_1c)) { // 68 (0 == r12)
		ebx = 0;
		r15d = 0x1;
		do {
		_b89:	// from 122
			esi = (0 == (shmemBitmap->_14 >> rbx)) ? 0x1 : (shmemBitmap->_14 >> rbx);
			// 99 call
			format_rowbytes_array[rbx] = CA::Render::format_rowbytes((unsigned int)shmemBitmap->_10, 
																	(unsigned int)(0 == (shmemBitmap->_14 >> rbx)) ? 0x1 : (shmemBitmap->_14 >> rbx));
			++rbx;
			edi = shmemBitmap->_10;
			esi = shmemBitmap->_14;
			// 122
		} while (shmemBitmap->_1c != ebx); // 119 (r12d != ebx) goto _b89;

	} // 124
	CA::Render::Image*& retImage = rbx; // &=rbx
	r15 = this;				// via _38;
	  // 171 call
	retImage = CA::Render::Image::new_image((unsigned int)shmemBitmap->_10, (unsigned int)shmemBitmap->_14,
									(unsigned int)shmemBitmap->_18,
									(unsigned int)shmemBitmap->_1c,
									(CGColorSpace*)colorSpace,
									(void const*)shmemBitmap->_c,
									(unsigned long const*)format_rowbytes_array,
									(void(*)(void const*, void*))& CA::Render::release_shmem_bitmap,
									(void*)this);
	eax = 0;
	// 188
	if (!(0 == retImage)) { // 185 (0 == rbx)
			 // 190 lock
		OSAtomicIncrement32((volatile int32_t*)&shmemBitmap->_0);
		// 198 call
		((CA::Render::Object*)this)->ref();
		// 213 call
		((X::Ref<CA::Render::Shmem>*)&shmemBitmap->_50)->operator=((CA::Render::Shmem*)this);
		retImage->_1c = shmemBitmap->_4;
		return retImage;
	} // 228
	else {
		return 0;
	}
}

CGImage* CA::Render::Shmem::copy_cgimage(CGColorSpace* colorSpace)
{
	_30 = colorSpace;
	r12 = this;
	CA::Render::ShmemBitmap*& shmemBitmap = r13; // &=r13
	CGDataProvider* cgDataProvider = r15; // &=r15
	shmemBitmap = this->_18;
	rsi = (int64_t)(int32_t&)shmemBitmap->_c;
	rdx = this->_10 - shmemBitmap->_c;
	rsi = shmemBitmap->_c + shmemBitmap;
	rcx = &CA::Render::release_provider(void*, void const*, unsigned long);
	// 51 call
	cgDataProvider = (CGDataProvider*)CGDataProviderCreateWithData((void*)this,
		(const void*)(shmemBitmap->_c + shmemBitmap),
		(int64_t)(this->_10 - shmemBitmaps->_c),
		(void(*)(void*, void const*, unsigned long)) &CA::Render::release_provider);
	ebx = shmemBitmap->_10;
	// 194 call
	rbx = (CGImage*)CGImageCreate((uint64_t)shmemBitmap->_14,
						(uint64_t)shmemBitmap->_18,
						(uint64_t)CA::Render::format_bpc((unsigned int)shmemBitmap->_10),// 81 call
						(uint64_t)CA::Render::format_bpp((unsigned int)shmemBitmap->_10),// 94 call
						(uint64_t)CA::Render::format_rowbytes((unsigned int)shmemBitmap->_10, (unsigned int)(0 != shmemBitmap->_14) ? shmemBitmap->_14 : 0x1),// 123 call
						(CGColorSpace*)colorSpace,
						(CGBitmapInfo)CA::Render::format_bitmap_info((unsigned int)shmemBitmap->_10),// 133 call
						(CGDataProvider*)cgDataProvider,
						(const CGFloat*)0x0,
						(bool)0x1,
						(CGColorRenderingIntent)0x0);
	// 205 call
	CGDataProviderRelease(cgDataProvider);
	eax = 0;
	// 215
	if (!(0 == rbx)) { // 212 (0 == rbx)
			 // 217 lock
		OSAtomicIncrement32((volatile int32_t*)&shmemBitmap->_0);
		// 225 call
		((CA::Render::Object*)this)->ref();
		return rbx;
	} // 233
	else {
		return 0;
	}
}

int CA::Render::Shmem::type() const
{
	return 0x29;
}

bool CA::Render::Shmem::set_volatile(bool bVolatile, int flag)
{
	r15d = bVolatile;
	rbx = this;
	r12d = (uint32_t)(uint8_t&)bVolatile;
	eax = bVolatile * 4;
	ecx = (this->_8 >> 0x10) & 0x4;
	r14b = 0x1;
	// 46
	if (ecx == eax) { // 44 (ecx == eax)
		return true;
	} // 121
	r13 = &this->_8;
	// 60
	if (!(0 == (0x100000 & this->_8))) { // 52 (0 == ((0x100000<<NaN) & r13->_0))
		_2c = (flag & -0x4) | bVolatile;
		extern mach_port_t vm_map_t;
		extern uint64_t vm_page_size;
		// 105 call
		// 112
		if (0 == vm_purgable_control((vm_map_t)mach_task_self_, (uint64_t)((0 - vm_page_size) & this->_18), (vm_purgable_t)0, (int*)&_2c)) { // 110 (0 == eax)
			// inline goto _f139;
		_f139:	// from 112
				// 139 lock
			OSAtomicXor32(0x40000, (volatile int32_t*)&this->_8);
			// 156
			if (!(0 == (0x80000 & this->_8))) { // 148 (0 == ((0x80000<<NaN) & r13->_0))
				rax = this->_18;
				// 162	shll $0x1f, %r12d
				// 166	sarl $0x1f, %r12d
				this->_18->_8 = (bVolatile) ? 0xffffffff : 0;
			} // 174
			  // 182
			if (!(0 == (0x200000 & this->_8))) { // 174 (0 == ((0x200000<<NaN) & r13->_0))
				// 201 call
				CARecordImageBytes((0 == bVolatile) ? this->_10 : -this->_10);
			} // 206
			  // 209
			if (0 != bVolatile) // 206 (0 != r15b)
				// inline goto _b121;
				return true;
			r14b = ((int32_t&)_2c != 0x2);
			// 219
			// inline goto _b121;
			return ((int32_t&)_2c != 0x2);
		}
	} // 114
	r14b = !(bool)bVolatile;			// r15b = r15b ^ 0x1;

	return r14b;
}

void CA::Render::Shmem::show(unsigned int, unsigned int) const
{
	return x_log("(shmem %lu bytes)", this->_10);
}

bool CA::Render::Shmem::caches_encoding() const
{
	return (0 == (0x800000 & this->_8));
}

CA::Render::Shmem* CA::Render::Shmem::decode(CA::Render::Decoder* decoder)
{
	rbx = decoder;
	// 20 call
	r13d = ((CA::Render::Decoder*)decoder)->decode_int16();

	mach_port_t& decode_port = r15d;
	// 33
	if (!(0 == (0x3 & r13b))) { // 29 (0 == (0x3 & r13b))
		// 38 call
		r14 = ((CA::Render::Decoder*)decoder)->decode_vm_size_t();
		// 49 call
		r12 = ((CA::Render::Decoder*)decoder)->decode_vm_size_t();
		// 61
		if (0x40 & r13b) { // 57 (0x40 & r13b)
					// inline jmp 160
		_f160:	// from 61
			decode_port = decoder->_40->_a4;
			_29 = 0x0;
			goto _f175;
		}
		else { // 61 next
			   // 72 call
			decode_port = ((CA::Render::Decoder*)decoder)->decode_port((unsigned int*)0, (bool&)_29);
			// 80
			goto _f175;

		}

	_f175:	// from 80
		eax = 0;
		// 180
		if (0 == decode_port) { // 177 (0 == r15d)
			return 0;
		} // 234
		CA::Render::Shmem*& newShmem = rax;
		// 198 call
		newShmem = CA::Render::Shmem::new_shmem((unsigned int)decode_port, (unsigned long)r14, (unsigned long long)r12, (bool)_29, (unsigned int)r13d);
		// 206
		if (0 != newShmem) { // 203 (0 != rax)
			return newShmem;
		} // 234
		cl = _29;
		// 213
		if (!(false == _29)) { // 211 (0 == cl) // 234
			extern mach_port mach_task_self_;
			// 227 call
			mach_port_deallocate((mach_port)mach_task_self_, (mach_port)decode_port);
			eax = 0;
		}
		return 0;

		// 82 unreachable
	}// 82
_f82:	// from 33
  // 97 call
	rbx = ((CA::Render::Decoder*)decoder)->decode_data_async((unsigned long&)&_38, (void(*&)(void const*, void*))_40, (void*&)_48);
	eax = 0;
	// 107 testq %rbx, %rbx
	// 110
	if (0 == rbx) { // 107 (0 == rbx)
		return 0;
	} // 234
	CA::Render::Shmem*& newShmem = rax;
	// 130 call
	newShmem = CA::Render::Shmem::new_shmem((void const*)rbx, (unsigned long)_38, (unsigned int)r13d, (void(*)(void const*, void*))_40, (void*)_48);
	// 135 testq %rax, %rax
	// 138
	if (0 != newShmem) { // 135 (0 != rax)
		return newShmem;
	} // 234
	rcx = _40;
	// 147
	if (0 == _40) { // 144 (0 == rcx)
		return 0;
	} // 234
			 // 156 call
	(*(void(*)(void const*, void*))_40)(rbx, _48); // *%rcx;
// 158
// inline goto _f232;
	return 0;
}

CA::Render::Shmem* CA::Render::Shmem::encode(CA::Render::Encoder* encoder) const
{
	r14 = encoder;
	r15 = this;
	ebx = this->_8 >> 0x10;
	// 26
	if (!(0 == (0x3 & (this->_8 >> 0x10)))) { // 23 (0 == (0x3 & bl))
			 ebx = ((int32_t&)this->_20 == 0x0) ? (this->_8 >> 0x10) | 0x40 : this->_8 >> 0x10;
	} // 41
	  // 47 call
	((CA::Render::Encoder*)encoder)->encode_int16((unsigned short)bx);
	// 55
	if (!(0x40 & bl)) { // 52 (0x40 & bl)
		rax = this->_10;
		// 64
		if (0x3 & bl) { // 57 (0 == (0x3 & bl))
					// inline jmp 187
			   // 207 call
			((CA::Render::Encoder*)encoder)->encode_data_async((void const*)this->_18, (unsigned long)this->_10, (void(*)(void const*, void*)) &CA::Render::release_object, (void*)this);
			return ((CA::Render::Object*)this)->ref();
		}
		else { // 64 next
			extern unsigned long long vm_page_size;
			// 72 call
			((CA::Render::Encoder*)encoder)->encode_int64((unsigned long long)this->_10);
			// 97 call
			((CA::Render::Encoder*)encoder)->encode_int64((unsigned long long)((vm_page_size - 1) & (uintptr_t)this->_18));
			return ((CA::Render::Encoder*)encoder)->encode_port(((CA::Render::Shmem*)this)->port(), 0x13, false);

		}
	} // 137
	  // 144 call
	((CA::Render::Encoder*)encoder)->encode_int64((unsigned long long)this->_10);
	// 156 call
	((CA::Render::Encoder*)encoder)->encode_int64((unsigned long long)this->_18);
	encoder->_58 = 0x1;
	return ((CA::Render::Encoder*)encoder)->retain_object((CA::Render::Object const*)this);
}

bool CA::Render::Shmem::is_purged() const
{
	// 13
	if (!(0x40000 & this->_8)) { // 6 (0x40000 & rdi->_8)
		return false;
	} // 19
	bool& is_purged = bl;
	is_purged = 0x1;
	// 28
	if (!(0 == (0x100000 & rdi->_8))) { // 21 (0 == (0x100000 & rdi->_8))
		_c = 0x0;
		// 80
		if (!(0 != vm_purgable_control((vm_map_t)mach_task_self_, (uint64_t)(0 - vm_page_size->_0) & this->_18, (vm_purgable_t)0x1, (int*)&_c))) { // 78 (0 != eax)
			is_purged = ((int32_t&)_c == 0x2);
		} // 89
	} // 89
	return is_purged;
}

bool CA::Render::Shmem::is_volatile() const
{
	// 11
	if (!(0x80000 & this->_8)) { // 4 (0x80000 & rdi->_8)
		return (0 != ((this->_8 >> 0x10) & 0x4));
	} // 24
	else {
		return (0 != this->_18->_8);
	}
}

CA::Render::ShmemBitmap CA::Render::Shmem::new_bitmap(unsigned int arg1, unsigned int width, unsigned int height, unsigned int scale)
{
	int64_t& alignment_property = rcx;	// &=rcx
	_2c = scale;
	r14d = height;
	r15d = width;
	_30 = arg1;
	r12d = 0;
	edi = 0;
	// 34 call
	alignment_property = CA::Render::alignment_property((CA::Render::AlignmentProperty)0);
	esi = 0x20;
	// 50
	if (!(0 == alignment_property)) { // 47 (0 == rcx)
		rax = alignment_property - 0x1;
		rsi = alignment_property + 0x1f;
		// 63
		if (!(0 == (alignment_property & (alignment_property - 0x1)))) {
			rsi = alignment_property + 0x1f - (alignment_property % (alignment_property + 0x1f));
		} // 78
		else {
			rsi = (alignment_property + 0x1f) & -alignment_property;
		}
	} // 84

	uint64_t& fixup_image_data_size = r15;
  // 88
	if (!((int32_t&)scale == 0x0)) { // 84 ((int32_t&)_2c == 0x0)

		_40 = rsi;
		eax = 0;
		_38 = 0;
		ebx = 0x1;
		r13d = height;
		_44 = height;
		r14d = width;
		_48 = width;
		r15d = 0;

		
		uint32_t& fixup_width = r14d;
		uint32_t& fixup_height = r13d;
		uint64_t& format_rowbytes = rax;
		uint64_t& image_data_size = rax;
		fixup_image_data_size = 0;
		fixup_width = width;
		fixup_height = height;
		do {
		_b122:	// from 177
			
			// 128 call
			format_rowbytes = (unsigned long)CA::Render::format_rowbytes((unsigned int)arg1, (unsigned int)fixup_width)
		// 139 call
			image_data_size = CA::Render::image_data_size(format_rowbytes, (unsigned int)fixup_height);
			// 147
			if (0 == image_data_size) { // 144 (0 == rax)
				// inline jmp 300
				return 0;
			}

			fixup_image_data_size = fixup_image_data_size + image_data_size;
			fixup_width = fixup_width >> 1;
			fixup_width = (0 == fixup_width) ? fixup_width : 1;
			fixup_height = fixup_height >> 1;
			fixup_height = (0 == fixup_height) ? fixup_height : 1;
			++r12d;
			// 177
		} while (r12d < (int32_t&)arg4); // 173 (r12d < (int32_t&)_2c) goto _b122;

		// 179
		goto _f196;

	} // 181
	else {
		_40 = rsi;
		_48 = width;
		_44 = height;
		fixup_image_data_size = 0;
	}

	CA::Render::Shmem*& newShmem = r14; // &=r14
_f196:	// from 179
	fixup_image_data_size = fixup_image_data_size + _40;
	// 203 call
	newShmem = CA::Render::Shmem::new_shmem((unsigned long)fixup_image_data_size);
	_38 = 0;
	// 220
	if (!(0 == newShmem)) { // 217 (0 == r14)
		CA::Render::ShmemBitmap*& shmemBitmap = rbx; // &=rbx
		shmemBitmap = newShmem->_18;
		// 229
		if (!(0 == newShmem->_18)) { // 226 (0 == rbx)
			// 231 lock
			OSAtomicOr32(0x280000, (volatile int32_t*)&newShmem->_8);
			// 244 call
			CARecordImageBytes(newShmem->_10);
			shmemBitmap->_c = _40;
			shmemBitmap->_10 = arg1;
			shmemBitmap->_14 = width;
			shmemBitmap->_18 = height;
			shmemBitmap->_1c = scale;
			// 284
			// goto _f300;
			return newShmem;
		} // 286
		  // 289 call
		((CA::Render::Object*)newShmem)->unref();
	} // 300
	return 0;
}


CA::Render::Shmem* CA::Render::Shmem::new_shmem(unsigned long size)
{
	uint64_t& offset_in_vm = _20;		// &=_20
	CA::Render::Shmem*& newShmem = rbx; // &=rbx
	// 60 call
	// 67
	if (!(0 != vm_allocate((vm_map_t)mach_task_self_, (uint64_t*)&offset_in_vm, (uint64_t)(-vm_page_size & (size + vm_page_size - 1)), 0x33000003))) { // 65 (0 != eax)
		r15 = offset_in_vm;
		// 76
		if (!(0 == offset_in_vm)) { // 73 (0 == r15)
				 // 81 call
			x_blame_allocation(offset_in_vm);
			// 91 call
			newShmem = x_mem_alloc_bucket(0x3);
			newShmem->_0 = (uintptr_t)CA::Render::Object::vtable + 0x10;
			newShmem->_8 = 0x110001;
			++CA::Render::Object::_instance_counts[0xa4 >> 2];
			rax = &vtable for CA::Render::Shmem + 16;
			newShmem->_0 = (uintptr_t)CA::Render::Shmem::vtable + 0x10;
			newShmem->_10 = size;
			newShmem->_18 = (CA::Render::ShmemBitmap*)offset_in_vm;
			newShmem->_20 = 0x0;
			newShmem->_28 = (void(*)(void const*, void*))&CA::Render::release_deallocate;
			newShmem->_30 = 0x0;
			newShmem->_24 = 0x0;
			newShmem->_30 = newShmem;
		} // 190
	} // 190
	else {
		newShmem = 0;
		eax = 0;
		// 204 call
		x_log_err("CoreAnimation: failed to allocate %ld bytes\n", size);
	}
_f209:	// from 188
	return newShmem;
}

uint64_t CA::Render::Shmem::offset() const
{
	extern uint64_t vm_page_size;
	return (vm_page_size - 1) & this->_18;
}

mach_port CA::Render::Shmem::port() const
{
	rbx = this;
	eax = this->_20;
	extern vm_map_t mach_task_self_;
	// 14
	if (!(0 != this->_20)) { // 12 (0 != eax)
		_10 = this->_10;
		// 63 call
		mach_make_memory_entry_64((vm_map_t)mach_task_self_, (uint64_t*)&_10, (uint64_t)this->_18, (vm_port_t)this->_8, (mach_port_t*)&this->_20, (mach_port_t)0);
		eax = this->_20;
	} // 71
	return this->_20;
}
