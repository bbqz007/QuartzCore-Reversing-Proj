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

void CA::Transaction::unlock()
{
	rbx = this;
	// 14
	if (!(0 == this->_20)) { // 12 (0 == eax)
			 // 21
		if (!(0 != --this->_20)) {
			// 27 call
			OSSpinLockUnlock(this->_18);
			// 39
			if (!(0 == this->_48)) { // 36 (0 == rdi)
				this->_48 = 0x0;
				return CA::release_objects((X::List<void const*>*)this->_48);
			} // 60
		} // 60
	} // 60
	return;
}


void CA::Transaction::set_value(unsigned int hkey, _CAValueType valueType, void const* value)
{
	r14 = value;
	r15d = valueType;
	r12d = hkey;
	rbx = this;
	// 30
	if (!((int32_t&)this->_0->_10 != 0x0)) { // 26 ((int32_t&)rax->_10 != 0x0)
			 // 35 call
		((CA::Transaction*)this)->ensure_implicit();
	} // 40
	CA::Transaction::Level*& level = rax; // &=rax
	level = this->_28;
	// 47
	if (!(0 != level)) { // 44 (0 != rax)
		// 54 call
		level = x_mem_alloc_bucket(0x1);
		level->_10 = 0x0;
		level->_8 = 0x0;
		level->_0 = 0x0;
		this->_28 = level;
	} // 86
	CA::AttrList*& attrList = rdi;
	attrList = level->_10;
	// 93
	if (!(0 != attrList)) { // 90 (0 != rdi)
			 // 97 call
		attrList = x_mem_alloc0_bucket(0);
	} // 105
	  // 114 call
	this->_28->_10 = ((CA::AttrList*)attrList)->set((unsigned int)hkey, (_CAValueType)valueType, (void const*)r14);
	return;
}


void CA::Transaction::set_fence(unsigned int port1, unsigned int port2, block_pointer Block)
{
	rbx = Block;
	r12d = port2;
	r13d = port1;
	r15 = this;
	// 37
	if (!(0x2 & this->_84)) { // 29 (0x2 & r15->_84)
		_29 = 0x0;
		// 64 call
		al = (bool)((CA::Transaction*)r15)->get_value((unsigned int)0x124, (_CAValueType)0x7, (void*)&_29);
		// 73
		if (!((int8_t&)_29 == 0x0)) { // 69 ((int8_t&)_29 == 0x0)
				 // 77
			if (!(false == !(bool)al)) {
				_29 = 0x0;
				// 100 call
				((CA::Transaction*)r15)->set_value((unsigned int)0x124, (_CAValueType)0x7, (void const*)&_29);
				eax = 0;
				// 114 call
				x_log("CoreAnimation: new transaction fence disabling existing low latency hint.\\n");
			} // 119
		} // 119
		  // 126
		if (!((int32_t&)this->_0->_10 != 0x0)) { // 122 ((int32_t&)rax->_10 != 0x0)
				 // 131 call
			((CA::Transaction*)r15)->ensure_implicit();
		} // 136
		eax = port2 + 1;
		// 144
		if (!((port2 + 1) < 0x2)) { // 141 (eax < 0x2)
			_38 = Block;				// save rbx (Block)
			// 170 call
			kdebug_trace(0x31ca0018, port1, port2, 0, 0);
			CA::Transaction::Shared*& shared = r14;			// &=r14
			int& old = eax;		// &=eax;
			shared = this->_0;
			old = this->_20;
			this->_20 = this->_20 + 1;
			// 191
			if (!(0 != old)) { // 189 (0 != eax)
					 // 197 call
				OSSpinLockLock(this->_18);
			} // 202
			CA::Transaction::Fence*& itFence = rbx;		// &=rbx
			itFence = shared->_28;
			// 206
			goto _f211;
			for (;
		_b208:	 // from 226
		_b208:	 // from 220
			; itFence = itFence->_0) {
			_f211:	 // from 206
					 // 214
				if (!(0 == itFence)) { // 211 (0 == rbx)
						 // 220
					if ((int32_t&)itFence->_8 != port1) // 216 ((int32_t&)rbx->_8 != r13d)
						continue;	// goto _b208;
					// 226
					if ((int32_t&)itFence->_14 != port2) // 222 ((int32_t&)rbx->_14 != r12d)
						continue;	// goto _b208;
					// 228
					break;	// goto _f310;
				}
				break;
			}// 230
			if (0 == itFence) {	// by hand
				// 235 call
				itFence = x_mem_alloc_bucket(0x1);
				itFence->_18 = 0x0;
				itFence->_10 = 0x0;
				itFence->_8 = 0x0;
				itFence->_8 = port1;
				itFence->_14 = port2;
				extern mach_port mach_task_self_;
				// 294 call
				mach_port_mod_refs((mach_port)mach_task_self_, (mach_port)port2, 0, 0x1);
				itFence->_0 = shared->_28;
				shared->_28 = itFence;
			} // 310
				 // 317
			if (!(0 == Block)) { // 314 (0 == rdi)
				// 334 call
				itFence->_18 = x_list_prepend((x_list*)itFence->_18, (uintptr_t)_Block_copy(Block));
			} // 343
			  // 346 call
			((CA::Transaction*)this)->unlock();
		} // 351
	} // 351
	return;
}


void CA::Transaction::set_continuation(block_pointer Block)
{
	CA::Transaction::Level*& level = rbx;	 // &=rbx
	CA::Transaction::Level*& nextLevel = r15;	// &=r15
	r14 = Block;
	level = this->_28;
	nextLevel = level->_0;
	rdi = level->_8;
	/**
	* relase the continuation belonging to top level
	*/
	// 27
	if (!(0 == level->_8)) { // 24 (0 == rdi)
			 // 29 call
		((CA::Transaction::Continuation*)level->_8)->unref();
		level->_8 = 0x0;
	} // 42

	  /**
	  * new a continuation if the set Block is not null
	  * otherwise, the level->_8 has point to null-continuation.
	  */
	  // 45
	if (!(0 == Block)) { // 42 (0 == r14)
		CA::Transaction::Continuation*& continuation = rcx;	// &=rcx
		CA::Transaction::Continuation*& newContinuation = rax;	// &=rax
			 // 52 call
		newContinuation = x_mem_alloc_bucket(0x1);
		// 60
		if (0 == nextLevel) { // 57 (0 == r15)
				// inline jmp 81
			continuation = 0;
			goto _f83;
		}
		else {
			/**
			* the continuations of levels should be linked together, and one continuation per level.
			* transaction
			* |
			* |
			* level --> level --> ...
			* |         |
			* |         |
			* cont  --> cont  --> ...
			*/
			CA::Transaction::Continuation*& pickContinuation = rdx;	// &=rdx
			pickContinuation = nextLevel->_8;
			continuation = 0;
			// 71
			if (0 == pickContinuation) { // 68 (0 == rdx)
					 // gen jmp 83
				goto _f83;
			}
			else { // 71 next
				   // 73 lock
				OSAtomicIncrement32((volatile int32_t*)&pickContinuation->_0);
				continuation = pickContinuation;
				// 79
				goto _f83;
			}
		}// 81
	_f83:	 // from 79
	_f83:	 // from 71
		newContinuation->_8 = continuation;
		newContinuation->_10 = Block;
		newContinuation->_0 = 0x1;
		level->_8 = newContinuation;
	} // 101
	return;
}


void CA::Transaction::run_deferred_visibility_layer_calls()
{
	r14 = this;
	rbx = this->_78;
	x_list*& itDeferredLayer = rbx;	// &=rbx
	itDeferredLayer = this->_78;
	// 20
	if (!(0 == itDeferredLayer)) { // 17 (0 == rbx)
		do {
		_b22:	 // from 81
			CA::Layer*& deferredLayer = r15;	// &=r15
			deferredLayer = listDeferredLayers->_0;
			// 28
			if (!(0 == deferredLayer)) { // 25 (0 == r15)
					 // 33 call
				deferredLayer->call_did_become_visible();
				// 43 lock
				// 51
				if (!(0x1 != OSAtomicAdd32(-1, (volatile int32_t*)&deferredLayer->_0))) { // 48 (eax != 0x1)
						 // 56 call
					((CA::Layer*)deferredLayer)->~Layer();
					// 69 call
					x_mem_dealloc_bucket(0xb, (void*)r15);
				} // 74
			} // 74
			itDeferredLayer = itDeferredLayer->_8;
			// 81
		} while (itDeferredLayer); // 78 (0 != rbx) goto _b22;

		// 87 call
		x_list_free((x_list*)this->_78);
		this->_78 = 0x0;
	} // 100
	return;
}


void CA::Transaction::run_commit_handlers(CATransactionPhase phase)
{
	CA::Transaction::Shared*& shared = r14;
	x_list**& blockList_place = r14;
	shared = this->_0;
	eax = phase;
	switch (phase) {
	case 0:
		blockList_place = &shared->_30;
		break;
	case 1:
		blockList_place = &shared->_38;
		break;
	case 2:
		blockList_place = &shared->_40;
		break;
	case 3:
		blockList_place = &shared->_48;
		break;
	default:
		eax = 0;
		// 26 call
		x_log("CoreAnimation: invalid commit handler phase! Defaulting to pre-commit.\\n");
		// 31
		blockList_place = &shared->0x38;
		break;
	}

	block_pointer& blockList = rbx;
	blockList = *blockList_place;
	// 77
	if (!(0 == blockList)) { // 74 (0 == rbx)
		do {
		_b79:	 // from 100
			block_pointer& Block = rdi;
			Block = blockList->_0;
			// 82 call
			Block->invoke(Blcok);
			// 88 call
			_Block_release(Block);
			blockList = blockList->_8;
			// 100
		} while (0 != blockList); // 97 (0 != rbx) goto _b79;

		// 105 call
		x_list_free(*blockList_place);
		*blockList_place = 0x0;
	} // 117
	return;
}


void CA::Transaction::reset_animators()
{
	r14 = this;
	rbx = this->_30;
	x_list*& itBlockList = rbx;
	itBlockList = this->_30;
	// 17
	if (!(0 == itBlockList)) { // 14 (0 == rbx)
		do {
		_b19:	 // from 39
				 // 25
			if (!(0 == itBlockList->_0)) { // 22 (0 == rdi)
					 // 27 call
				_Block_release(itBlockList->_0);
			} // 32
			itBlockList = itBlockList->_8;
			// 39
		} while (0 != itBlockList); // 36 (0 != rbx) goto _b19;

		// 45 call
		x_list_free(this->_30);
		this->_30 = 0x0;
	} // 58
}


void CA::Transaction::remove_root(CA::Layer* root)
{
	rbx = root;
	// 17 call
	OSSpinLockLock(&CA::Transaction::roots_lock);
	rdi = CA::Transaction::roots;
	// 32
	if (0 == CA::Transaction::roots) // 29 (0 == rdi)
	// inline goto _f111;
		return OSSpinLockUnlock(&CA::Transaction::roots_lock);
	// 37 call
	r14 = x_hash_table_remove_ptr(CA::Transaction::roots, root);
	// 52 call
	OSSpinLockUnlock(&CA::Transaction::roots_lock);
	// 60
	if (!(0 == r14)) { // 57 (0 == r14)
		int& old = rax;
		// 67 lock
		old = OSAtomicAdd32(-1, (volatile int32_t*)&root->_0);
		// 74
		if (!(0 == root)) { // 71 (0 == rbx)
				 // 79
			if (!(old != 0x1)) { // 76 (eax != 0x1)
				// 84 call
				((CA::Layer*)root)->~Layer();
				return x_mem_dealloc_bucket(0xb, root);
			} // 106
		} // 106
	} // 106
	return;
}


void CA::Transaction::release_thread(void* thread)
{
	CA::Transaction::Shared*& shared = r12;
	r14 = this;
	shared = this->_0;
	extern bool ent_off__0x51e24;	// cmpb $0x0, 0x51dea(%rip);	 CA::Transaction::global_deleted + 7
	// 26
	if (!((int32_t&)shared->_10 == 0x0)) { // 20 ((int32_t&)r12->_10 == 0x0)
		// 46 call
		kdebug_trace(0x31ca0021, 0, 0, 0, 0);
		// 58
		if (!((int8_t&)ent_off__0x51e24 == 0x0)) { // 51 ((int8_t&)rip->_51dea == 0x0)
			// 60 call
			x_log_begin();
			eax = 0;
			// 74 call
			x_log("CoreAnimation: warning, deleted thread with uncommitted CATransaction; created by:\\n");
			// 95 call
			char**& symbols = r13;
			symbols = backtrace_symbols(&shared->_90, shared->_110);
			// 106
			if (!(0 == symbols)) { // 103 (0 == r13)
				int& count = ebx;
				count = 0;
				// 119
				if (!((int32_t&)shared->_110 <= 0x0)) { // 110 ((int32_t&)r12->_110 <= 0x0)
				_b128:	 // from 157
					eax = 0;
					// 138 call
					x_log("%s\\n", symbols[rbx]);
					++count;
					// 157
					if (count < (int64_t)(int32_t&)shared->_110) // 154 (rbx < rax)
						goto _b128;
				} // 159
				  // 162 call
				free(symbols);
			} // 167
			  // 172 call
			x_log_end(0x1);
		} // 179
		else {
			eax = 0;
			// 188 call
			x_log_warn("CoreAnimation: warning, deleted thread with uncommitted CATransaction; set CA_DEBUG_TRANSACTIONS=1 in environment to log backtraces.\\n");
		}
		// 203 call
		pthread_setspecific(CA::Transaction::transaction_key, this);
		// 208 call
		objc_autoreleasePoolPush(CA::Transaction::transaction_key);
		// 219 call
		this->commit();
		// 227 call
		objc_autoreleasePoolPop(CA::Transaction::transaction_key);
		// 241 call
		pthread_setspecific(CA::Transaction::transaction_key, 0);
		// 260 call
		kdebug_trace(0x31ca0022, 0, 0, 0, 0);
	} // 265
	  // 272
	if (!(0 == this->_68)) { // 269 (0 == rdi)
		// 274 call
		CFRunLoopObserverInvalidate(this->_68);
		// 283 call
		CFRelease(this->_68);
	} // 288
	  // 294
	if (!(shared->_18 == 0x0)) { // 288 (r12->_18 == 0x0)
		// 301 call
		CA::Transaction::free_command_list((CA::Transaction::Command*)shared->_18);
	} // 306
	  // 312
	if (!(shared->_20 == 0x0)) { // 306 (r12->_20 == 0x0)
		x_list*& list_node = rcx;
		// 316 call
		list_node = x_mem_alloc_bucket(0);
		list_node->_0 = shared->_20;
		list_node->_8 = 0x0;
		do {
		_b340:	 // from 360
			rax = CA::Transaction::global_deleted;
			list_node->_8 = (x_list*)CA::Transaction::global_deleted;
			// 351 lock
			// 360
		} while (false == OSAtomicCompareAndSwapPtr(CA::Transaction::global_deleted, list_node, (void* volatile*)& CA::Transaction::global_deleted)); // 352 (false == OSAtomicCompareAndSwapPtr(rax, rcx, (void* volatile*)& CA::Transaction::global_deleted)) goto _b340;

	} // 362
	  // 365 call
	this->reset_animators();
	return free(this);
}


void CA::Transaction::release_object(void const* obj)
{
	rbx = this;
	// 13
	if ((int32_t&)this->_20 == 0x0) // 9 ((int32_t&)rbx->_20 == 0x0)
		// inline goto _f35;
		return CFRelease(obj);
	// 19 call
	this->_48 = x_list_prepend(this->_48, obj);
	return;
}


void CA::Transaction::push_animator(block_pointer Block)
{
	rax = Block;
	rbx = this;
	  // 34 call
	this->_30 = x_list_prepend(this->_30, (0 == Block) ? 0 : _Block_copy(Block));
	return;
}


void CA::Transaction::push()
{
	CA::Transaction::Shared*& shared = r14;
	r15 = this;
	shared = this->_0;
	r12d = 0x1;
	eax = 0x1;
	// 28 lock
	// 36
	if (!(0 == OSAtomicAdd32(0x1, (volatile int32_t*)&shared->_10))) { // 34 (0 == eax)
			 // 43
		if (!(this->_28 != 0x0)) { // 38 (r15->_28 != 0x0)
				 // 50 call
			this->_28 = new (x_mem_alloc_bucket(0x1)) CA::Transaction::Level;
		} // 82
		  // 87 call
		this->_28 = new (x_mem_alloc_bucket(0x1)) CA::Transaction::Level(this->_28);
		// 126
		// inline goto _f325;
		return;
	} // 131
	shared->_68 = shared->_68 & -0x4;
	shared->_60 = 0x0;
	shared->_88 = 0x0;
	// 172 call
	shared->_50 = (x_heap_struct*) x_heap_new_with_ptr(0x1000, &this->_1a0, 0xe60);
	// 188 call
	OSSpinLockLock(&CA::Transaction::slot_lock);
	ebx = 0;
	eax = CA::Transaction::slot_mask;
	int& shift = ebx;
	int& setbit = r12d;

	for (shift = 0, setbit = 1		// fake
		; shift < 0x3
		; ++shift, setbit <<= 1) {
	_b201:	 // from 214
			 // 204
		if (0 == (setbit & CA::Transaction::slot_mask)) {
			// inline goto _f256
			CA::Transaction::slot_mask = CA::Transaction::slot_mask | setbit;
			// 272 call
			OSSpinLockUnlock(&CA::Transaction::slot_lock);
			shared->_0 = shift;
			this->_8 = shift;
			this->_10 = shared->_8;
			break;	// natural flow to 292
		}
	}
	if (!(shift < 0x3)) {
		// 223 call
		OSSpinLockUnlock(&CA::Transaction::slot_lock);
		// 242 call
		shared->_8 = x_hash_table_new_(0, 0, 0, 0, 0, 0);
		// goto _f284
		this->_8 = shared->_0;
		this->_10 = shared->_8;
	}


	extern bool ent_off__0x51b28;		// 0x519fd(%rip); CA::Transaction::global_deleted + 7
			 // 299
	if (!((int8_t&)ent_off__0x51b28 == 0x0)) { // 292 ((int8_t&)rip->_519fd == 0x0)
			 // 313 call
		shared->_110 = backtrace(&shared->_90, 0x10);

	} // 325
_f325:	 // from 126
	return;
}

void CA::Transaction::pop_animator()
{
	rbx = this;
	rdi = this->_30;
	// 16
	if (!(0 == this->_30)) { // 13 (0 == rdi)
		block_pointer& Block = rax;
		Block = (block_pointer)((x_list*)this->_30)->_0;
		// 24
		if (!(0 == Block)) { // 21 (0 == rax)
				 // 29 call
			_Block_release(Block);
		} // 38
			// 38 call
		this->_30 = x_list_remove_head(this->_30);
	} // 47
	return;
}


void CA::Transaction::pop()
{
	CA::Transaction::Shared*& shared = r12;
	r14 = this;
	shared = this->_0;
	// 23
	if (!((int32_t&)shared->_10 == 0x0)) { // 17 ((int32_t&)r12->_10 == 0x0)
		rbx = &shared->_10;
		// 42
		if (!(OSAtomicAdd32(-1, (volatile int32_t*)&shared->_10) != 0x1)) { // 39 (eax != 0x1)
			/**
			* keep the shared->_10 greater than 0
			*/
			shared->_10 = 0x1;
		_b50:	// from 128
			return this->commit();
		} // 66

		CA::Transaction::Level*& popLevel = r15;
		popLevel = this->_28;
		this->_28 = popLevel->_0;
		// 80
		if (!(0 == popLevel)) { // 77 (0 == r15)
				 // 85 call
			((CA::Transaction::Level*)popLevel)->~Level();
			// 98 call
			x_mem_dealloc_bucket(0x1, popLevel);
		} // 103
		// 108
		if (!(shared->_10 != 0x1)) { // 105 (eax != 0x1)
				 // 116
			if (!(0 == (0x2 & shared->_68))) { // 110 (0 == (0x2 & r12->_68))
				/**
				* check if inline-shared
				*/
				// 128
				if ((Shared*)this->_0 == (Shared*)&this->_88) { // 125 (r14->_0 == rax)
					// inline goto _b50;
					return this->commit();
				}
			} // 130
		} // 130
	} // 130
	return;
}

void CA::Transaction::lock()
{
	// 15
	if (0 == this->_20++) // 13 (0 == eax)
	// inline goto _f19;
		return OSSpinLockLock(this->_18);
	else
		return;
}

void CA::Transaction::init()
{
	// 19 call
	pthread_key_create(&_8, (void(*)(void*))&CA::Transaction::release_thread);
	CA::Transaction::transaction_key = _8;
	char*& env = rax;
	// 42 call
	env = getenv("CA_DEBUG_TRANSACTIONS");
	// 50
	if (!(0 == env)) { // 47 (0 == rax)
		// 55 call
		CA::Transaction::_debug_transactions = (0 != atoi(env));
	} // 69
	return;
}

bool CA::Transaction::get_value(unsigned int hkey, _CAValueType valueType, void* value)
{
	r14 = value;
	r15d = valueType;
	r12d = hkey;
	rbx = this->_28;
	CA::Transaction::Level*& itLevel = rbx;
	itLevel = this->_28;
	// 24 goto _f29;

	for (
		// 29
		; !(0 == itLevel)
		// 26
		; itLevel = itLevel->_0) {
		// 41
		if (0 == itLevel->_10) // 38 (0 == rdi)
			continue;	// goto _b26;
		// 52 call
		// 63
		if (false == ((CA::AttrList*)itLevel->_10)->get((unsigned int)hkey, (_CAValueType)valueType, (void*)value)) // 61 (0 == cl)
			continue;	// goto _b26;
		// 65
		else
			// inline goto _f69;
			return true;
	} // end for (;;)
	// 67
	eax = 0;
	return false;
}

bool CA::Transaction::get_animator(block_pointer& Block) const
{
	// 11
	if (!(0 == this->_30)) { // 8 (0 == rax)
		Block = this->_30->_0;
		al = 0x1;
		// 21
		// inline goto _f25;
		return true;
	} // 23
	else {
		eax = 0;
		return false;
	}
}

CA::Transaction* CA::Transaction::get()
{
	return (CA::Transaction::transaction_key) ? pthread_getspecific(CA::Transaction::transaction_key) : 0;
}

void CA::Transaction::free_command_list(Command* command)
{
	r14 = command;
	// 10 testq %r14, %r14
	// 13
	if (!(0 == command)) { // 10 (0 == r14)
		CA::Transaction::Command*& itCommand = rbx;
		itCommand = command;
		do {
		_b18:	// from 38
			rdi = itCommand->_18;
			// 25
			if (!(0 == itCommand->_18)) { // 22 (0 == rdi)
					 // 27 call
				CFRelease(itCommand->_18);
			} // 32
			itCommand = itCommand->_0;
			// 38
		} while (0 != itCommand); // 35 (0 != rbx) goto _b18;

	} // 40
	return x_mem_dealloc_chain(0x28, command, 0);
}

void CA::Transaction::foreach_root(void(*commit_root)(CA::Layer*, void*), void* context)
{
	rdi = this->_58;
	// 12 testq %rdi, %rdi
	// 15
	if (!(0 == this->_58)) { // 12 (0 == rdi)
		struct callback_context_st {
			void(*_0)(CA::Layer*, void*);
			void* _8;
		} *& callback_context = rdx;
		_10 = commit_root;
		_8 = context;
		callback_context = (callback_context_st*)&_10;
		// 36 call
		x_hash_table_foreach((x_hash_table*)this->_58, (void(*)(CA::Layer*, CA::Layer*, void*))&CA::foreach_callback, callback_context);
	} // 41
	return;
}

void CA::Transaction::foreach_deleted_id(void(*commit_deleted)(unsigned long, unsigned int, void*), void* context)
{
	r14 = context;
	r15 = commit_deleted;
	rbx = this->_40;
	x_chain*& deleted_id_chain = rbx;
	deleted_id_chain = this->_40;
	// 20 goto _f38;

	for (
		// 38
		; 0 != deleted_id_chain
		// 35
		; deleted_id_chain = deleted_id_chain->_0) {
		// 32 call
		(*commit_deleted)(deleted_id_chain->_8, deleted_id_chain->_10, context);
	}
	return;
}

void CA::Transaction::foreach_command(unsigned int flag, void(*commit_command)(int, unsigned long, void const*, void*), void* context)
{
	r14 = context;
	r15 = commit_command;
	r12d = flag;
	rbx = this->_38;
	CA::Transaction::Command*& itCommand = rbx;
	itCommand = this->_38;
	// 24 goto _f29;
	for (
		// 29
		; !(0 == itCommand)
		// 26 then goto 29
		; itCommand = itCommand->_0) {
		// 39
		if (!(0 == itCommand->_20)) { // 37 (0 == eax)
				 // 44
			if (itCommand->_20 != flag) // 41 (eax != r12d)
				continue;	// goto _b26;
		} // 46
		// 60 call
		(*commit_command)(itCommand->_8, itCommand->_10, itCommand->_18, context);
		// 63 goto _b26;
	} // end for (;;)
	// 65
	return;
}

void CA::Transaction::flush_transaction()
{
	// 14
	if (!(0 == CA::Transaction::transaction_key)) { // 11 (0 == rdi)
		CA::Transaction*& transaction = rax;
		CA::Transaction::Shared*& shared = rcx;
		// 16 call
		transaction = pthread_getspecific(CA::Transaction::transaction_key);
		// 24
		if (!(0 == transaction)) { // 21 (0 == rax)
			shared = transaction->_0;
			// 33
			if (!((int32_t&)shared->_10 == 0x0)) { // 29 ((int32_t&)rcx->_10 == 0x0)
				return this->flush();
			} // 44
		} // 44
	} // 44
	return;
}

void CA::Transaction::flush()
{
	CA::Transaction::Shared*& shared = rax;
	shared = this->_0;
	// 13
	if (!(0 == (0x1 & shared->_68))) { // 10 (0 == (0x1 & cl))
			 // 22
		if (!((int32_t&)this->_80 != 0x0)) { // 15 ((int32_t&)rdi->_80 != 0x0)
			// 30
			if (shared->_10 < 0x2) { // 27 (edx < 0x2)
				// inline goto _f40;
				return this->commit();
			}
			(char&)rax->_68 |= 0x2;
		} // 38
	} // 38
	return;
}

unsigned int CA::Transaction::current_state()
{
	// 14
	if (!(0 == CA::Transaction::transaction_key)) { // 11 (0 == rdi)
		CA::Transaction*& transaction = rax;
		CA::Transaction::Shared*& shared = rcx;
		// 16 call
		transaction = pthread_getspecific(CA::Transaction::transaction_key);
		// 24
		if (!(0 == transaction)) { // 21 (0 == rax)
			shared = transaction->_0;
			// 33
			if (!((int32_t&)shared->_10 == 0x0)) { // 29 ((int32_t&)rcx->_10 == 0x0)
				return ((int32_t&)transaction->_80 == 0x0)
					? (shared->_68 & 0x2) * 2 | (0x2 - (shared->_68 & 0x1))
					: ((shared->_68 & 0x2) * 2 | (0x2 - (shared->_68 & 0x1))) + 8;
			} // 75
		} // 75
	} // 75
	return 0;
}

void CA::Transaction::commit_transaction()
{
	// 14
	if (!(0 == CA::Transaction::transaction_key)) { // 11 (0 == rdi)
		CA::Transaction*& transaction = rax;
		CA::Transaction::Shared*& shared = rcx;
		// 16 call
		transaction = pthread_getspecific(CA::Transaction::transaction_key)
		// 24
		if (!(0 == transaction)) { // 21 (0 == rax)
			shared = transaction->_0;
			// 33
			if (!((int32_t&)shared->_10 == 0x0)) { // 29 ((int32_t&)rcx->_10 == 0x0)
				return transaction->pop();
			} // 44
		} // 44
	} // 44
	return;
}

void CA::Transaction::commit()
{
	rbx = this;
	rax = &this->_88;
	if (this->_0 != &this->_88) { // 27 (rbx->_0 != rax)
		// inline
		return;
	} // 865
	// 51
	if (false == OSAtomicCompareAndSwapInt(0, 0x1, (volatile int32_t*)&this->_80)) { // 44 (false == OSAtomicCompareAndSwapInt(eax, ecx, (volatile int32_t*)&rbx->_80))
		// inline
		return;
	} // 865
	_30 = 0x0;
	// 82 call
	// 97
	if (!(false == this->get_value((unsigned int)0xfa, (_CAValueType)0x12, (void*)&_30))) { // 90 (0 == al)
			 // 104 call
		eax = CAHostTimeWithTime((double&)_30);
		r8d = eax;
		rcx = rax >> 0x20;
	}
	else {
		r8d = 0;
		ecx = 0x0;
	} // 119
	r15d = 0;
	// 131 call
	kdebug_trace(0x31ca0005, 0, 0, ecx, r8d);

	CA::Transaction::Shared*& shared = r13;	// &=r13
	r13 = this->_0;
	al = 0x1;
	r14 = &CA::Transaction::roots_lock;
	r12 = &_38;

	for (;;) {
	_b152:	// from 655
	_b152:	// from 642
		_3c = eax;					// save eax (1, for the first time)
		this->_84 = this->_84 & -0x3;


		/**
		* #1 Step
		* pick up the commands added into Shared::_18,
		* reverse the link of commands, and placed into Transaction::_38
		*/
		// 167
		if (!(shared->_18 == 0x0)) { // 162 (r13->_18 == 0x0)
			rcx = shared->_18;
			esi = 0x0;

			CA::Transaction::Command*& reverse_link = rsi;
			CA::Transaction::Command*& link = rcx;
			CA::Transaction::Command*& next = rax;
			// 181
			if (!(0 == link)) { // 173 (0 == rcx)
				do {
				_b183:	// from 198
					next = link->_0;
					link->_0 = reverse_link;
					reverse_link = link;
					link = next;
					// 198
				} while (0 != next) // 189 (0 != rax) goto _b183;
			} // 200
			this->_38 = reverse_link;
			shared->_18 = 0x0;
			// 212
			goto _f222;

		} // 222

		/**
		* #2 Step
		* 1.remove the ones added to CA::Transaction::roots, and put them to Transaction::_58
		* 2.remove the unused ones in Transaction::_58
		* 3.check the CA::Transaction::roots again, if there are new ones.
		*/
		for (;;) {
		_f222:	// from 212
			  // 225 call
			OSSpinLockLock(&CA::Transaction::roots_lock);
			rdi = CA::Transaction::roots;
			// 240
			if (!(0 == CA::Transaction::roots)) { // 237 (0 == rdi)
				rdx = this->_58;
				// 249
				if (!(0 == this->_58)) { // 246 (0 == rdx)
					rsi = &CA::move_root(CA::Layer*, CA::Layer*, void*);
					// 258 call
					x_hash_table_foreach((x_hash_table*)CA::Transaction::roots, (void(*)(CA::Layer*, CA::Layer*, void*))&CA::move_root, this->_58);
					// 270 call
					x_hash_table_remove_all(CA::Transaction::roots);
				} // 277
				else {
					//// 263 extern ent_off__0x52204;	movq 0x520f6(%rip), %rdi;	CA::Transaction::roots
					//// 281 extern ent_off__0x52204;	movq $0x0, 0x520e0(%rip);	CA::Transaction::slot_lock + 4
					this->_58 = CA::Transaction::roots;
					CA::Transaction::roots = 0x0;
				}
			} // 292
			  // 295 call
			OSSpinLockUnlock(&CA::Transaction::roots_lock);

			/***
			* duraing this procedure, some will add_roots
			*
			*/
			rdi = this->_58;
			// 307
			if (!(0 == this->_58)) { // 304 (0 == rdi)
				rsi = &CA::release_root_if_unused(CA::Layer*, CA::Layer*, void*);
				rdx = this;
				// 319 call
				x_hash_table_remove_if((x_hash_table*)this->_58, &CA::release_root_if_unused, (void*)this);
			} // 324

			/***
			* so we need to check again.
			*
			*/
			  // 327 call
			OSSpinLockLock(&CA::Transaction::roots_lock);
			rdi = CA::Transaction::roots;
			// 342
			if (!(0 == CA::Transaction::roots)) { // 339 (0 == rdi)
					 // 344 call
				// 352
				if (0 != x_hash_table_size((x_hash_table*)CA::Transaction::roots)) { // 349 (0 != rax)
					// goto _b214; inline #0
				_b214:	// from 352
						// 217 call
					OSSpinLockUnlock(&CA::Transaction::roots_lock);
					continue;	// goto _b222;
				}
			}
			break;
		}	// end for (;;)


		/**
		* #3 Step
		* pick up the deleted chain added into Shared::_20
		*
		*/

		// 358
		  // 361 call
		OSSpinLockUnlock(&CA::Transaction::roots_lock);
		// 371
		if (!(shared->_20 == 0x0)) { // 366 (r13->_20 == 0x0)
			this->_40 = shared->_20;
			shared->_20 = 0x0;
		} // 389


		/**
		* #4 Step
		* deal with the deleted chains
		*
		*/

		for (;;) {
		_b389:	// from 476
		_b389:	// from 416
			x_list*& old_global_deleted = rcx;							// &=rcx
			old_global_deleted = CA::Transaction::global_deleted;
			// 399
			if (0 == old_global_deleted) { // 396 (0 == rcx)
				break;		// goto _f478;
			}
			rax = old_global_deleted;
			// 404 lock
			// 416
			if (false == OSAtomicCompareAndSwapPtr(old_global_deleted, 0, (void* volatile*)& CA::Transaction::global_deleted)) // 405 (false == OSAtomicCompareAndSwapPtr(rax, r15, (volatile int32_t*)& CA::Transaction::global_deleted))
				continue;	// goto _b389;
			else
				rax = old_global_deleted;


			x_list*& it_old_global_deleted = rax;
			it_old_global_deleted = old_global_deleted;
			do {
			_b418:	// from 466
				rdx = it_old_global_deleted->_0;
				_38 = rdx;					// save rdx (it_old_global_deleted->_0)
				rsi = &_38;					// via r12, r12 is &_38
				x_chain*& it = rdx;
				x_chain**& tail = rsi;
				it = (x_chain*)it_old_global_deleted->_0;
				tail = &(x_chain*)it_old_global_deleted->_0;

				// 431
				if (!(0 == it)) { // 425 (0 == rdx)
					do {
					_b433:	// from 442
						tail = &it->_0;
						it = it->_0;
						// 442
					} while (0 != it); // 439 (0 != rdx) goto _b433;
				} // 444

				*tail = this->_40;
				rdx = _38;					// restore rdx, set to it_old_global_deleted->_0
				this->_40 = (x_chain*)it_old_global_deleted->_0;

				it_old_global_deleted = it_old_global_deleted->_8;
				// 466
			} while (0 != it_old_global_deleted); // 463 (0 != rax) goto _b418;

			// 471 call
			x_list_free(old_global_deleted);
			// 476
			continue;	// goto _b389;

		} //  end for (;;)


		/**
		* #5 Step
		* call the CA::Context::commit_transaction
		* make the CA::Context::commit_transaction handle the commands, the deteled chains and roots.
		*/

		// 478
		  // 481 call
		CA::Context::commit_transaction((CA::Transaction*)this);

		/**
		* #5 Step
		* clean the deleted chains and roots
		*
		*/
		// 493
		if (!(0 == this->_40)) { // 490 (0 == rsi)
				 // 502 call
			x_mem_dealloc_chain(0x18, (x_chain*)this->_40, 0);
			this->_40 = 0x0;
		} // 515
		  // 522
		if (!(0 == this->_58)) { // 519 (0 == rdi)
				 // 534 call
			x_hash_table_foreach((x_hash_table*)this->_58, (void(*)(CA::Layer*, CA::Layer*, void*))&CA::release_root, (void*)this);
			// 543 call
			x_hash_table_free((x_hash_table*)this->_58);
			this->_58 = 0x0;
		} // 556


		/**
		* #6 Step
		* clean the commands
		* 
		*/

		// 563
		if (!(0 == this->_38)) { // 560 (0 == rdi)
				 // 565 call
			CA::Transaction::free_command_list((CA::Transaction::Command*)this->_38);
			this->_38 = 0x0;
		}// 578
		goto _f608;


		/**
		* #7 Step
		* clean the fence
		*
		*/

		CA::Transaction::Fence*& fence = r15;	// &=r15
		for (;;) {
		_b580:	// from 615
			shared->_28 = fence->_0;
			// 590 call
			((CA::Transaction::Fence*)r15)->~Fence();
			// 603 call
			x_mem_dealloc_bucket(0x1, r15);
		_f608:	// from 578
			fence = shared->_28;
			// 615
			if (0 != fence) // 612 (0 != r15)
				continue;	// goto _b580;
			break;
		}

		/**
		* #8 Step
		* free this transaction?
		*
		*/

		// 620 call
		CA::Layer::free_transaction((CA::Transaction*)this);


		/**
		* #9 Step
		* check the Shared again, if needed to commit again in the case that something is added to Shared.
		*
		*/

		r15d = 0;
		eax = _3c;
		// 633
		if (!(0 == (0x1 & al))) { // 631 (0 == (0x1 & al))
			eax = 0;		// will be saved to _3c, break in the end of the next loop
			// 642
			if (shared->_20 != 0x0) // 637 (r13->_20 != 0x0)
				continue; // goto _b152;
			eax = 0;
			// 655
			if (shared->_18 != 0x0) // 650 (r13->_18 != 0x0)
				continue; // goto _b152;
		}
		break;
	}	// end for (;;)
	// 661

	/**
	* #10 Step
	* finalize
	* clean this transaction
	*/

	  // 666
	if (!(this->_10 == 0x0)) { // 661 (rbx->_10 == 0x0)
		/**
		* #10.a Step
		* clean thread flags for CALayer
		*/
		// 672 call
		x_hash_table_free(shared->_8);
		shared->_8 = 0x0;
		this->_10 = 0x0;
	} // 695
	else {
		/**
		* #10.b Step
		* Transaction::_8 is thread flags slot mask
		*/
		r14 = &CA::Transaction::slot_lock;
		// 705 call
		OSSpinLockLock(&CA::Transaction::slot_lock);
		CA::Transaction::slot_mask &= ~(0x1 << (this->_8 & 0xff));
		(uint32_t&)shared->_0 = 0xffffffff;
		(uint32_t&)this->_8 = 0xffffffff;
		// 746 call
		OSSpinLockUnlock(&CA::Transaction::slot_lock);
	}
	// 751
	shared->_10 = 0x0;
	shared->_60 = 0x0;
	// 771 call
	x_heap_free(shared->_50);
	shared->_110 = 0x0;
	r13 = shared + 0x50;
	((x_heap_struct*)shared->_50)->_8 = 0x0;
	((x_heap_struct*)shared->_50)->_0 = 0x0;
	this->_80 = 0x0;
	this->_84 &= -0x7;
	rdi = this->_28;
	// 831
	if (!(0 == this->_28)) { // 828 (0 == rdi)
			 // 841 call
		CA::Transaction::Level::free_levels((CA::Transaction::Level*)this->_28);
		this->_28 = 0x0;
	} // 846
	  // 860 call
	kdebug_trace(0x31ca0006, 0, 0, 0, 0);


	return;
}

void CA::Transaction::cf_release(void const* cf_obj)
{
	rbx = cf_obj;
	// 12
	if (!(0 == cf_obj)) { // 9 (0 == rbx)
		rdi = CA::Transaction::transaction_key;
		// 24
		if (0 == rdi) { // 21 (0 == rdi)
			// goto _f60; inline #0
			return CFRelease(cf_obj);
		}
		CA::Transaction*& transaction = rax;			// &=rax, temporary
		// 26 call
		transaction = pthread_getspecific(CA::Transaction::transaction_key);
		// 34
		if (0 == transaction) { // 31 (0 == rax)
			// goto _f60; inline #0
			return CFRelease(cf_obj);
		}
		return transaction->release_object((void const*)cf_obj);
	} // 53
	return;
}


void CA::Transaction::begin_transaction()
{
	rdi = CA::Transaction::transaction_key;
	CA::Transaction*& transaction = rax;			// &=rax
	// 11 testq %rdi, %rdi
	// 14
	if ((0 == CA::Transaction::transaction_key)  // 11 (0 == rdi)
		|| !(0 != transaction = pthread_getspecific(CA::Transaction::transaction_key))) { // 21 (0 != rax)
	_f26:	 // from 14
			 // 26 call
		// 34
		if (0 == (transaction = CA::Transaction::create())) { // 31 (0 == rax)
			// inline jmp 45
			return;
			// 47 nop
		}
	}
	return CA::Transaction::push(transaction);
}


void CA::Transaction::assert_inactive()
{
	rdi = CA::Transaction::transaction_key;
	// 21
	if (0 == CA::Transaction::transaction_key) { // 18 (0 == rdi)
		return;
	} // 177

	extern bool ent_off__0x50be6;			// global_deleted + 7
	CA::Transaction*& transaction = rax;		// &=rax, temporary
			 // 27 call
	transaction = pthread_getspecific(CA::Transaction::transaction_key);
	// 35
	if (!(0 == transaction)) { // 32 (0 == rax)
		CA::Transaction::Shared*& shared = r15;		// &=r15
		shared = transaction->_0;
		// 49
		if (!((int32_t&)shared->_10 == 0x0)) { // 44 ((int32_t&)r15->_10 == 0x0)
				 // 58
			if (ent_off__0x50be6 == false) { // 51 ((int8_t&)rip->_50bac == 0x0)
				// goto _f186; inline #0
				eax = 0;
				// 195 call
				x_log_warn("CoreAnimation: warning, encountered thread with uncommitted CATransaction; set CA_DEBUG_TRANSACTIONS=1 in environment to log backtraces.\\n");
				// 200 call
				abort();
				// 205 nop
			}
			// 60 call
			x_log_begin();
			eax = 0;
			// 74 call
			x_log("CoreAnimation: warning, encountered thread with uncommitted CATransaction; created by:\\n");
			// 93 call
			SEL*& symbols = r12;						// &=r12;
			symbols = backtrace_symbols(&shared->_90, shared->_110);
			// 104
			if (!(0 == symbols)) { // 101 (0 == r12)
				ebx = 0;
				// 116
				if (!((int32_t&)shared->_110 <= 0x0)) { // 108 ((int32_t&)r15->_110 <= 0x0)
					r14 = "%s\\n";
				_b125:	 // from 152
					eax = 0;
					// 134 call
					x_log("%s\\n", (SEL)((int64_t*)symbols)[rbx]);
					++rbx;
					// 152
					if (rbx < shared->_110) // 149 (rbx < rax)
						goto _b125;
				} // 154
				  // 157 call
				free(symbols);
			} // 162
			  // 167 call
			x_log_end(0x1);
			// 172 call
			abort();
		} // 177
	} // 177
	return;
}


void CA::Transaction::add_root(CA::Layer* rootLayer)
{
	rbx = rootLayer;
	r14 = this;
	rdi = &CA::Transaction::roots_lock;
	// 20 call
	OSSpinLockLock(&CA::Transaction::roots_lock);
#if 0
	rdi = CA::Transaction::roots;
	// 35
	if (!(0 != CA::Transaction::roots)) { // 32 (0 != rdi)
			 // 51 call
		CA::Transaction::roots = rdi = x_hash_table_new_(0, 0, 0, 0, 0, 0);
	} // 66
#else
	CA::Transaction::roots = (CA::Transaction::roots) ? CA::Transaction::roots : x_hash_table_new_(0, 0, 0, 0, 0, 0);
	rdi = CA::Transaction::roots;
#endif
	// 72 call
  // 79
	if (!(false == x_hash_table_insert(CA::Transaction::roots, rootLayer, rootLayer))) { // 77 (0 == al)
			 // 81 lock
		OSAtomicIncrement32((volatile int32_t*)&rootLayer->_0);
		// 84 testb $0x10, 0x84(%r14)
		// 92
		if (!(0 == (0x10 & r14->_84))) { // 84 (0 == (0x10 & r14->_84))
			rax = (int64_t)(int32_t&)this->_8;
			// 101
			if ((0 > this->_8) // 98 (0 > rax)
				|| !((int32_t&)((uint32_t*)&rootLayer->_a8)[this->_8] != 0x0)) { // 103 ((int32_t&)((uint32_t*)&rbx->_a8)[rax] != 0x0)
				// 119 call
				rootLayer->thread_flags_(this);
			}
		} // 124
	} // 124
_f124:	 // from 111
	return OSSpinLockUnlock(&CA::Transaction::roots_lock);
}


void CA::Transaction::add_deleted_id(unsigned long hobj, unsigned int id)
{
	CA::Transaction::Shared*& shared = rbx;
	x_chain*& chain = rbx;
	r14d = id;
	r15 = hobj;
	shared = this->_0; 
	// 24 call
	chain = (x_chain*)x_mem_alloc_bucket(0x1);
	chain->_8 = hobjs;
	chain->_10 = id;

	rbx = &shared->_20;
	x_chain*& old = rax;

	/**
	* insert prepend
	*/
	do {
	_b44:	 // from 55
		old = shared->_20;
		chain->_0 = old;			
		// 50 lock
		// 55
	} while (false == OSAtomicCompareAndSwapPtr(old, chain, (void* volatile*)&shared->_20))); // 51 (rbx->_0 != rcx) goto _b44;
	return;
}


void CA::Transaction::add_deferred_visibility_layer(CA::Layer* deferredLayer)
{
	rbx = deferredLayer;
	r14 = this;
	rdi = this->_78;
	// 17 call
	x_list_find(this->_78, deferredLayer);
	// 22 testq %rax, %rax
	// 25
	if (!(0 != x_list_find(this->_78, deferredLayer))) { // 22 (0 != rax)
			 // 27 lock
		OSAtomicIncrement32((volatile int32_t*)&deferredLayer->_0);
		// 37 call
		this->_78 = x_list_prepend(this->_78, deferredLayer);
	} // 46
	return;
}


void CA::Transaction::add_commit_handler(block_pointer Block, CATransactionPhase phase)
{
	r15d = phase;
	r14 = Block;
	rbx = this;
	// 27
	if (!(0x2 & this->_84)) { // 20 (0x2 & rbx->_84)
		CA::Transaction::Shared*& shared = rax;				// &=rax, temporary
		shared = this->_0;
		// 40
		if (!((int32_t&)shared->_10 != 0x0)) { // 36 ((int32_t&)rax->_10 != 0x0)
				 // 45 call
			this->ensure_implicit();
		} // 50
		eax = this->_20;
		ecx = rax + 1;
		this->_20 = ecx;
		// 61
		if (!(0 != eax)) { // 59 (0 != eax)
				 // 67 call
			OSSpinLockLock(this->_18);
		} // 72
		r12 = this->_0;
		eax = phase;
#if 0
		{
			// 82
			if (!(phase <= 0x3)) { // 78 (r15d <= 0x3)
				eax = 0;
				// 93 call
				x_log("CoreAnimation: invalid commit handler phase! Defaulting to pre-commit.\\n");
				// 98
				goto _f122;
			} // 100
			rcx = &<+196>;
			rax = (int64_t)(int32_t&)((int32_t*)rcx)[rax];
			rax = rax + rcx;
			// 114 jmpq *%rax
			r12 = r12 + 0x30;
			// 120
			goto _f138;
		_f122:	 // from 98
				 // 122	r12 = r12 + 0x38;
				 // 126
			goto _f138;
			// 128	r12 = r12 + 0x40;
			// 132
			goto _f138;
			// 134	r12 = r12 + 0x48;
		}
#else
		switch (phase) {
		case 0:
			r12 = this->_0 + 0x30;
			break;
		case 1:
			r12 = this->_0 + 0x38;
			break;
		case 2:
			r12 = this->_0 + 0x40;
			break;
		case 3:
			r12 = this->_0 + 0x48;
			break;
		default:
			x_log("CoreAnimation: invalid commit handler phase! Defaulting to pre-commit.\\n");
			// 122	
			r12 = this->_0 + 0x38;
			break;
		}
#endif
	_f138:	 // from 132
	_f138:	 // from 126
	_f138:	 // from 120
			 // 138 testq %r14, %r14
			 // 141
		if (!(0 == Block)) { // 138 (0 == r14)
			x_list**& x_list_place = r12;				// &=r12
			_NSMallocBlock*& copiedBlock = rax;			// &=rax
			r15 = *x_list_place;
			// 150 call
			copiedBlock = _Block_copy(Block);
			// 161 call
			x_list_prepend(*x_list_place, copiedBlock);
			*x_list_place = copiedBlock;
		} // 170
		return this->unlock()
	} // 186
	return;
}


CA::Transaction* CA::Transaction::ensure()
{
	// 14
	if (0 == transaction_key)
		return CA::Transaction::create(); // goto _f28; iniline #0

	// 24
	if ((rax = pthread_getspecific(transaction_key)))			// 16 call
		return CA::Transaction::create(); // goto _f28; iniline #0

	return rax;
}

CA::Transaction* CA::Transaction::ensure_compat()
{
	CA::Transaction*& transaction = rbx;					// &=rbx
	// 6 call
	transaction = CA::Transaction::ensure();
	// 21
	if (!(0 == (0x8 & transaction->_84))) {
		// 30
		if (!(0 != transaction->_0->10)) {
			// 35 call
			transaction->ensure_implicit();
		} // 40
	} // 40
	return transaction;

}

void CA::Transaction::ensure_implicit()
{
	r14 = this;
	// 17
	if (!(0 == (CAGetDebugFlags() & 0x80))) {				// 0 == [10 call]
		// 39 call
		// %rsi = $(19 call)
		// %rdi = @"Started implicit transaction for thread %p\\n"
		NSLog(__cfs("Started implicit transaction for thread %p\\n"), pthread_self());
	} // 44
	  // 51
	if (!this->_60) {
		// 53 call
		this->_60 = (__CFRunLoop*) CFRunLoopGetCurrent();
	} // 65
	
	  // 70
	if (!(0 != this->_68)) {
		// 99 call
		// %r8 = CA::Transaction::observer_callback(__CFRunLoopObserver*, unsigned long, void*)
		this->_68 = CFRunLoopObserverCreate(0, 0xa0, 0x1, 0x1e8480, &CA::Transaction::observer_callback, 0);
		// 111
		if (0 == this->_68) {
			// gen jmp 268
			// goto _f268; inline #0
			// 271 
			transaction->push();
			this->_0->_68 |= 1;
			return;
		}

		extern __CFString** NSRunLoopCommonModes;
			// 134 call
			// %rcx = (void *)0x0000000103d2ab68: NSRunLoopCommonModes
			CFRunLoopAddObserver(this->_60, this->_68, *NSRunLoopCommonModes);
		// 144
		if (0 == this->_68) {
			// gen jmp 268
			// goto _f268; inline #0
			// 271 
			transaction->push();
			this->_0->_68 |= 1;
			return;
		}
		else { // 144 next
			rdi = this->_60;
		}
	}// 150
_f150:	// from 70
	  // 150 call
	__CFString*& currentMode = rbx;												// &=rbx
	currentMode = CFRunLoopCopyCurrentMode(this->_60);
	// 161
	if (!(0 == currentMode)) {
		extern __CFString*& NSDefaultRunLoopMode;
		// 173
		if (!(currentMode == NSDefaultRunLoopMode)) {
			static __CFString* tracking_mode = nil;
			extern void* rip_0x5236d; // CA::active_timers + 7
			// 183
			if (!(0 != rip_0x5236d)) {
				boolean& isEqual = al;
				// 195 call
				// %rsi = @"UITrackingRunLoopMode"
				isEqual = CFEqual(currentMode, __cfs("UITrackingRunLoopMode"));
				// 202
				if (!isEqual) {
					// 207 call
					tracking_mode = CFRetain(currentMode);
					// 230 call
					CFRunLoopAddObserver(this->_60, this->_68, currentMode);
				} // 235
			} // 235

			  // 242
			if (!(currentMode == tracking_mode)) {
				// 255 call
				CFRunLoopAddObserver(this->_60, this->_68, currentMode);
			} // 260
		} // 260
		  // 263 call
		CFRelease(currentMode);
	} // 268
_f268:	// from 144
_f268:	// from 111
	// 271 
	transaction->push();
	this->_0->_68 |= 1;
	return;
}

CA::Transaction* CA::Transaction::create()
{
	CA::Transaction*& transaction = rbx;							// &=rbx
	// 6 call
	CA::Render::initialize_memory_warnings();
	// 16 call
	transaction = (CA::Transaction*) malloc(0x1000);
	// 27
	if (!(0 == transaction)) {
		// 43 call
		memset(&transaction, 0, 0x1a0);
		extern int64_t rip_0x5288a; // -[CATiledLayer didChangeValueForKey:]::contentsAreFlipped + 7
		// 56
		if (-0x1 != rip_0x5288a) {
			// goto _f223; inline #0
			static dispatch_once_t once;
			// 239 call
			// %rdx = CA::Transaction::init()
			// %rdi = CA::Transaction::create()::once
			dispatch_once_f(&once, 0, &CA::Transaction::init);
			// 244
			goto _b62:
		}
			
	_b62:	// from 244
			// 72 call
			// %rdi = CA::Transaction::transaction_key
		pthread_setspecific(transaction_key, transaction);
		// 77 call
		al = (pthread_main_np() != 0);
		transaction->_84 = transaction->_84 & 0xfffffffe | al;
		transaction->_0 = (CA::Transaction::Shared) ((uintptr_t)transaction + 0x88);
		transaction->_18 = &transaction_lock;
		// 132 call
		al = (false == _CFExecutableLinkedOnOrAfter(0x3eb));
		transaction->_84 = (transaction->_84 & 0xffffff7) | (al << 0x3);
		// 167 call
		al = (false == _CFExecutableLinkedOnOrAfter(0x3f2));
		transaction->_84 = (transaction->_84 & 0xfffffef) | (al << 0x4);

		// 197
		transaction->_0->_0 = 0xffffffff;
		transaction->_8 = 0xffffffff;
	} // 213
	return transaction;
}

void CA::Transaction::add_command(int arg1, unsigned int arg2, unsigned long arg3, void const* arg4)
{
	// _40 to _30

	CA::Transaction*& transaction = r14;							// &=r14
	CA::Transaction::Command*& command = rbx;						// &=rbx;
	CA::Transaction::Shared*& shared = r13;							// &=r13
	// 30 call
	transaction = CA::Transaction::ensure();
	shared = transaction->_0;
	// 46 call
	command = x_mem_alloc_bucket(0x2);
	command->_8 = arg1;
	command->_20 = arg2;
	command->_10 = arg3;
	eax = 0;
	// 80
	if (!(0 == arg4)) {
		// 85 call
		command->_18 = CFRetain(arg4);
	} // 90
	else {
		command->_18 = 0;
	}

	  // 101
	if (!(0 != shared->_10)) {
		// 106 call
		transaction->ensure_implicit();
	} // 111

	// do {
_b115:	// from 128
	command->_0 = shared->_18;
		// 128
	if (!OSAtomicCompareAndSwapPtr(shared->_18, command, &shared->_18))
		goto _b115;
	// } while();

	return;
}