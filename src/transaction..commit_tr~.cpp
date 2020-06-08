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
#include "CA.oc.h"
#include "CA.ops.h"
#include "OSAtomic.h"

void CA::Context::commit_transaction(CA::Transaction* transaction)
{
	/****
	* actions:
	* transaction->run_commit_handlers((CATransactionPhase)0);
	* loop deal with layer's display_layout_if_needed in contexts.
	* transaction->run_commit_handlers((CATransactionPhase)0x3);
	* loop deal with Fences in contexts.
	* transaction->run_commit_handlers((CATransactionPhase)1);
	* loop deal with contexts in transaction and use encoder to ipc.
	* transaction->run_deferred_visibility_layer_calls();
	* transaction->run_commit_handlers((CATransactionPhase)0x3);
	* transaction->run_commit_handlers((CATransactionPhase)1);
	* transaction->run_commit_handlers((CATransactionPhase)2);
	* set_next_animation_time; 
	*/
	CA::Context* _168;
	int64 _178 = 10;			// count of contexts
	int64 _180 = 10;
	int64 _170 = transaction;
	unsigned long& contextBufferLength = _178;
	unsigned long& retainedContextsLength = contextBufferLength;
	CA::Context*& contextBuffer = _b0; // _b0;
	CA::Context**& retainedContexts = r14;
	r14 = CA::Context::retain_all_contexts(YES, &contextBuffer, /**unsigned long&*/contextBufferLength);
	// _160 may be type of struct {CGFloat, CGFloat, ...}, typically CGRect, size of 16 bytes.
	if (NO == transaction->get_value(0x5d, /**_CAValueType*/0x12, (void*)&_160))	
	{
		_160 = NULL;
	}
	// +<133>
	int64 _158 = abs(0x7ff0000000000000);
	transaction->run_commit_handlers((CATransactionPhase)0);
	int64 _1c0 = retainedContextsLength;
	if (retainedContextsLength != 0)
	{
		_198 = objc_autoreleasePoolPush(transaction);

		/****
		* variables:
		* _178 is the count retrieved by CA::Context::retain_all_contexts;
		* _b0 is the local locations (stack-based) for buffer to retrievie context pointers. 
		* r14 is set to the actual returned buffer, may be allocated by `CA::Context::retain_all_contexts`,
		*        if _b0 is not large enough. In that case, it is needed to free by hand.
		* rbx is likely an acc-couter in a loop.
		* _168 is a temporary to current context in contexts.
		* _r15 is a Layer got from current context.
		*
		* actions:
		* 1.get layer out from context;
		* 2.call layout_and_display_if_needed
		* 3.call prepare_commit
		* 4.release the layer.
		*/
		
		rbx = 0;
		// <+197>, do { ... } while (++rbx < _178);
		CA::Context*& curContext = _168;
		do 
		{
			_168 = (CA::Context*) retainedContexts[rbx]; // *(int64*)(r14 + rbx * 8);		// location to a object.
			transaction->_50 = curContext;
			pthread_mutex_lock((pthread_mutex_t*)&curContext->_10);	// the pthread_mutex_t may be an inline mutex offset 0x10 of some object;
			if ((CALayer*)curContext->_68 != NULL)
			{
				CA::Layer*& underlyingLayer = r15;
				r15 = (CA::Layer*)CALayerGetLayer(curContext->_68);
				underlyingLayer->_0++;
				pthread_mutex_unlock((pthread_mutex_t*)&curContext->_10);
				if (underlyingLayer != NULL)
				{
					underlyingLayer->layout_and_display_if_needed(transaction);
					underlyingLayer->prepare_commit(transaction);
					// release the layer;
					if (1 == OSAtomicAdd32((int32_t)-1, (volatile int32_t*)&underlyingLayer->_0))
					{
						underlyingLayer->~layer();
						x_mem_dealloc_bucket(0xb, (uintptr_t)underlyingLayer);
						// jmp <+334>
					}
				}
			}
			else //<+326>, branch from <+239>
			{
				pthread_mutex_unlock((pthread_mutex_t*)&curContext->_10);
			}

			// <+334>
			rbx++;
		} while (rbx < retainedContextsLength); // loop <+347> to <+197>
		
		objc_autoreleasePoolPop(_198);

		/** from now on
		* _198 is reused for CA::Context**, but not used at once until all contexts of r14 are unreffed.
		*
		* actions:
		* 1. retrieve contexts second time, just after the first retrieved contexts are dealed with their layer.
		*/
		unsigned long& contextBufferLength2 = _180;
		unsigned long& retainedContextsLength2 = contextBufferLength2;
		CA::Context*& contextBuffer2 = _130; // _b0;
		CA::Context**& retainedContexts2 = _198;

		_198 = CA::Context::retain_all_contexts(YES, (CA::context**)&contextBuffer2, /**unsigned long&*/contextBufferLength2);


		/***
		* actions:
		* 1. unref all the contexts which are retrieved at first time.
		* 2. free the buffer of r14 if needed.
		*/
		r13 = &_b0;
		rbx = 0;
		if (retainedContextsLength != 0)
		{
			do
			{
				CA::Context* ctx = (CA::Context*) retainedContexts[rbx];	// (CA::Context*) r14 + rbx;
				ctx->unref()
			} while (++rbx < retainedContextsLength);
			rbx = retainedContextsLength;
		}
		if (&contextBuffer != retainedContexts)		// _b0 is a buffer specified from caller, r14 is a returned buffer.
		{
			rbx <<= 3;
			if (rbx < 0x190)
			{
				rbx += 0xfffffffff;
				rbx >>= 4;
				x_mem_dealloc_bucket(0xfffffffff & rbx, (uintptr_t)retainedContexts);
				// jmp <+493>
			}
			else // <+482>
			{
				x_mem_dealloc_size((size_t)rbx, (uintptr_t)retainedContexts);
			}
		}
		// <+493>
		*(char*)&transaction->_84 |= 2;
		transaction->run_commit_handlers((CATransactionPhase)0x3);

		/****
		* varialbes:
		* _198 is buffer for second time retrieved contexts, now work on it.
		*/
		rbx = autoreleasePoolPush(transaction);
		CA::Transaction::Shared*& shared = transaction->_0;
		CA::Transaction::Fence*& firstFence = r15;									// &=r15
		firstFence = shared->_28;
		if (firstFence != NULL)
		{
			_1a0 = rbx;								// save rbx;
			_1a8 = transaction;
			CA::Transaction::Fence*& curFence = rbx;								// &=rbx, as an iterator for traversing
			curFence = firstFence;					// via rbx = r15;
			
			/***
			* a loop for walking through the Fence link to run callbacks of each Fence.
			*/
			// <+557>
			do
			{
				((CA::Transaction::Fence*)curFence)->run_callbacks();		// Fence : Î§Ç½; Õ¤À¸£¬Àé°Ê; ·À»¤Îï; ½£Êõ
				curFence = curFence->_0;		// Fence::_0 is a next pointer.
			} while (curFence);		// loop <+571> to <+557>
			
			// <+573>
			mach_port _184 = 0;
			r12d = 0;
			rbx = retainedContextsLength2;
			/**
			* <<DUAL LOOP>>
			* outer loop : every fence
			* inner loop : every retained context
			*
			*/
		_b593:		// from _932, a loop of do { ...; r15 = r15->next; } while(r15);
			if ((0 != firstFence->_c && firstFence->_10 >= 2 && retainedContextsLength2 != 0)
				|| (0 == firstFence->_c && retainedContextsLength2 != 0))
			{
				// <+620>
				r13d = 0;
			_b623:		// from _920, condition is while(++r13 < rbx)
				do
				{
					rdi = retainedContexts2[r13]; // (void**)((char*)_198 + r13 * 8);
					if (retainedContexts2[r13]->_5c == firstFence->_8)
					{
						// <+647>
						if (_184 == 0)
						{
							extern common_obj_layout* mach_task_self_;
							edi = mach_task_self_->_0;
							mach_port_allocate((mach_port)mach_task_self_->_0, 1, (mach_port*)&_184);
							mach_port_insert_right((mach_port)mach_task_self_->_0, _184, _184, 0x14);
						}
						// <+720>
						CA::Render::Context*& renderContext = r14;					// &=r14
						renderContext = retainedContexts2[r13]->retain_render_ctx();
						if (renderContext)
						{
#if 0
							if (r15->_c != 0)
							{
								((CA::Render::Context*)r14)->set_fence((unsigned int)_184,
									false,
									(unsigned int)r15->_c,
									(unsigned int)r15->_10);
							_b761:	// from _872
								r12 += 0xffffffff000000ff & rax;
							_b767:	// from _842, _862
								((const CA::Render::Object*)r14)->unref();
								// jmp <+914>

							}
							else // <+836> somewhere a loop condition.
							{
								// piece between <+836> to <+872>.
								if (0 != (int32_t)((CA::Render::Context*)r14)->_14
									&& NO == ((CA::Render::Context*)r14)->set_fence((unsigned int)_184,
										false,
										(unsigned int)((CA::Render::Context*)r14)->_14))
								{
									rax = ((CA::Transaction::Fence*)r15)->release_port();
									goto _b761;
								}
								else
								{
									goto _b767;
								}
							}
#else
							if (firstFence->_c != 0)
							{
								((CA::Render::Context*)r14)->set_fence((mach_port)_184,
									false,
									(unsigned int)firstFence->_c,
									(unsigned int)firstFence->_10);
								r12 += 0xffffffff000000ff & rax;
							}
							else // <+836> somewhere a loop condition.
							{
								// piece between <+836> to <+872>.
								if (0 != (int32_t)((CA::Render::Context*)renderContext)->_14
									&& NO == ((CA::Render::Context*)renderContext)->set_fence((mach_port)_184,
										false,
										(unsigned int)((CA::Render::Context*)renderContext)->_14))
								{
									rax = ((CA::Transaction::Fence*)firstFence)->release_port();
									r12 += 0xffffffff000000ff & rax;
								}
							}
							((const CA::Render::Object*)renderContext)->unref();
#endif
						}
						else // <+780>
						{
							CA::Context* context = retainedContexts2[r13];
							if (0 != (int32_t)context->_90)
							{
								// <+801>
								if (0 != (int32_t)firstFence->_c)
								{
									if (1 < _CASSetFence((int32_t)context->_90, (int32_t)context->_58, (mach_port)_184, (int32_t)firstFence->_c, firstFence->_10))
									{
										r12 += 1;
									}
									// <+834>: jmp <+914>
									// piece between <+836> to <+872> is not in this flow.
								}
								else // <+874>
								{
									if (0 != firstFence->_14
										&& 0 == _CASSetFenceWithPort((mach_port)_184, context->_58))
									{
										((CA::Transaction::Fence*)firstFence)->release_port();
										// <+908>, <+911>
										r12 += 0xffffffff000000ff & rax;
									}
								}
							} // forwards to <+914>
						}
					}
					// <+914>
					++r13;
				}  while (r13 < retainedContextsLength2); // goto _b623;
			}
			// <+926>
			firstFence = firstFence->_0;				// via r15
			if (firstFence)
				goto _b593;	// a loop of do { ...; r15 = r15->next; } while(r15);

			// <+938> to <+1049>
			*(int32_t*)&_1ac = 1;		// _1ac may be type of bool, alignment with 4 bytes size.
			if ((mach_port)_184 != 0)
			{
				rbx = _1a0;						// restore rbx, set to transaction
				CA::Render::Fence::wait((mach_port)_184, (unsigned long)r12);
				r12 = _1a8;
				if (_160 == CGRectZero)
				{
					_160 = xmm0; // xmm0 returned by CA::Render::Fence::wait, some timeinterval.
				}
				extern common_obj_layout* mach_task_self_;
				mach_port_mod_refs((mach_port)mach_task_self_->_0, (mach_port)_184, 1, 0xffffffff);
				mach_port_deallocate((mach_port)mach_task_self_->_0, (mach_port)_184);
			}
			else // <+1063>
			{
				r12 = _1a8;		// transaction is saved to _1a8;
				rbx = _1a0;		// transaction which pushed to autoreleasepool;
				// next instruction is <+1077>
			}
		}
		else //<+1051> branch from <+534>
		{
			*(int32_t*)&_1ac = 0;
		}

		// <+1077>
		transaction->run_commit_handlers((CATransactionPhase)1);
		objc_autoreleasePoolPop(transaction);		// objc_autoreleasePoolPop(rbx);

		/** from now on
		* r12 is transaction
		*/

		// <+1098>
		if (_160 == 0.f)
		{
			(double&)_160 = CACurrentMediaTime();
		}

		edi = 0;
		if (0 != retainedContexts2)
		{
			// _1b8, _1a0 as int32_t
			_1b8 = eax = 0;
			_1a0 = ecx = 0;
			/***
			* loop:
			* do { ... } while(_180 > ++_1a0);
			*
			* variables:
			* _1a0 is an acc-counter for walking through the contexts.
			* _170 is an error for foreach_x functions.
			* _168 is a temporary to current context in contexts (CA::Context).
			* _150 is CA::Render::Encoder, newed in each looping if needed.
			* _148 is CA::Render::Context of current context.
			* r14 is unused except get pthread_mutex of context at the beginnig of the loop.
			* r15 is as transaction for the whole loop.
			* r12 is for things else after r15 set to r12. r12 is used to move rax to rdi in subsequence calls.
			*
			* actions:
			* 1.use CA::Context's functions deal with each context in transaction: commit_deleted, commit_command,  commit_layer, commit_root.
			* 2.CA::Render::Encoder, send msg to reply_port 
			* 3.CA::Render::Context, did_commit.
			* 4.CA::Render::Encoder, then receive msg from reply_port.
			*/
			CA::Context*& curContext = _168;
			CA::Render::Encoder*& renderEncoder = _150;
			CA::Render::Context*& renderContext = _148;
			// <+1152>
		_b1152:			// from <+2334>, do { ... } while(_180 > ++_1a0); ++_1a0 via rcx;
			r14 = retainedContexts2[_1a0];
			_168 = r14;
			bool _138 = false;
			(&_150)[1] = 0;		// _150 is a struct, sizeof 16 bytes, constructure; _148
			(&_150)[0] = 0;
			pthread_mutex_lock((pthread_mutex_t*)&curContext->_10);		// pthread_mutex_t is inline in r14, offset 0x10.
			transaction->_50 = retainedContexts2[_1a0];	// r12->_50 = _168;
			curContext->_b0 = &_170;
			r15 = r12;

			transaction->lock();
			if (0 != curContext->_70)
			{
				_148 = (CA::Render::Context*) curContext->_70;
				((CA::Render::Context*)renderContext)->will_commit();
			}
			// <+1290>
			if (0 != curContext->_90
				&& 0 == (1 & curContext->_c8))
			{
				rax = _1b8;
				if (0 == _1b8)
				{
					// <+1328>
					/**
					* alloc 0x8000 bytes from stack:
					*
					* <+1328>: movq   %rsp, %rax
					* <+1331> : addq   $ - 0x8000, %rax
					* <+1337> : movq   %rax, %rsp
					*/
					
					rax = _alloca(0x8000);		// i just borrow _alloca from windows crt.
				}
				// <+1340>
				_1b8 = rax;
				r12 = x_heap_new_with_ptr(0x1000, rsp, 0x8000);
				rbx = x_heap_malloc(r12, 0x68);
				r13 = r12;
				// constructure of Encoder;
				(CA::Render::Encoder*)rbx)->Encoder((x_heap_struct*)r12,	// r12 is a heap or zone
											(unsigned int)0,
											(void*)curContext,				// via _168
											(unsigned int)curContext->_58,
											(double)_160);
				_150 = rbx;

				// <+1426>
				if (0 == (r12 = curContext->_98))
				{
#if 0
					r12 = x_mem_alloc_bucket(1);
					((CA::Render::Encoder::ObjectCache*)r12)->ObjectCache();
					_168->_98 = r12;
#else
					curContext->_98 = r12 = new (x_mem_alloc_bucket(0x1))CA::Render::Encoder::ObjectCache;
#endif
				}
				// <+1487>
				_1a8 = r13;
				((CA::Render::Encoder*)renderEncoder)->set_object_cache((CA::Render::Encoder::ObjectCache*)r12);
				// jmp <+1516>
			}
			else // <+1507>
			{
				_1a8 = rax & 0xffffffff00000000;
			}

			// <+1516>
			((CA::Transaction*)r15)->foreach_deleted_id((void(*)(unsigned long, unsigned int, void*))&CA::Context::commit_deleted, (void*)&_dd2);
			((CA::Transaction*)r15)->foreach_command((unsigned int)curContext->_5c,
				(void(*)(int, unsigned long, void const*, void*))&CA::Context::commit_command,
				(void*)&_170);
			r13d = 0;
			r12d = 0;
			if (0 != curContext->_68)
			{
				CA::Layer*& underlyingLayer = rbx;
				rbx = CALayerGetLayer(curContext->_68);
				r13d = 0;
				if (underlyingLayer)
				{
					r13b = true;
					underlyingLayer->commit_if_needed((CA::Transaction*)r15,
						(void(*)(CA::Layer*, unsigned int, unsigned int, void*))&CA::Context::commit_layer,
						(void*)&_170);
					r12 = underlyingLayer;
				}
			}
			// <+1648>
			((CA::Transaction*)r15)->foreach_root((void(*)(CA::Layer*, void*))&CA::Context::commit_root, (void*)&_170);
			if (true == r13b)
			{
				// <+1675>
				((CA::Layer*)r12)->collect_animations((CA::Transaction*)r15, (double)_160, (double*)&_158);
			}
			// <+1701>
			if (0 != renderEncoder && (renderEncoder->_18 - renderEncoder->_10) != renderEncoder->_50)
			{
				bool _185 = true;		// _188, _187, _186, _185. 4 bytes alignment. ?? _185 is the highest octer.
				((CA::Transaction*)r15)->get_value((unsigned int)0x124, (_CAValueType)0x7, (void*)_185);
				// <+1759>
				al = 0 == pthread_main_np();
				if (!((bool)_1ac | al)
					&& x_cpu_has_64bit())
				{
					if (true == _185)
					{
						CA::Render::encode_set_low_latency((CA::Render::Encoder*)renderEncoder);
					}
				}
				else // <+1811>
				{
					_185 = false;
				}
			}
			// <+1818>
			// todo:
			if (YES == ((CA::Transaction*)r15)->get_value((unsigned int)0xfa, (_CAValueType)0x12, (void*)&_190))
			{
				if (0 != renderContext)				// via _148
				{
					((CA::Render::Context*)renderContext)->add_input_time((double)_190);
				}
				if (0 != _150 && (_150->_18 - _150->_10) != _150->_50)
				{
					CA::Render::encode_add_input_time((CA::Render::Encoder*)_150, (double)_190);
				}
			}
			// <+1911>
			transaction->unlock();

			// <+1919>
			if (0 != renderContext)
			{
				OSAtomicAnd32(0xfffeffff, (volatile int32_t*)&renderContext->_8);
			}
			r13d = 0;
			if (0 != renderEncoder)
			{
				if ((((renderEncoder->_18 - renderEncoder->_10) != renderEncoder->_50) | (bool)_1ac) == false)
				{
					r13d = 0;
					if (true == renderEncoder->_58)
					{
						r13d = (mach_port) CA::Render::get_reply_port();		// r13d is a mach_port;
						rdi = renderEncoder;		// the last function may use it and replace it.
					}
					// <+2015>
					// send message to a reply port.
					r12d = ((CA::Render::Encoder*)renderEncoder)->send_message((unsigned int)curContext->_90, (mach_port)r13d);
					if (0x10000003 == r12d)
					{
						curContext->_c8 |= 1;
					}
					// <+2062>
					++*(int32_t*)&curContext->_88;
				}
			}
			else // <+2077>
			{
				r12d = 0;
			}
			// <+2080>
			transaction->_50 = (CA::Context*) 0;
			curContext->_b0 = 0;
			if (0 != renderContext)
			{
				curContext->_88 = ++*(int32_t*)&renderContext->_1c;
				((CA::Render::Context*)renderContext)->did_commit((bool)_138, (bool)false);
			}
			// <+2153>
			*(char*)&curContext->_c8 &= 0xf7; // -0x5;
			if (8 & *(char*)&curContext->_c8)
			{
				((CA::Context*)curContext)->destroy();
			}
			// <+2181>
			pthread_mutex_unlock(r14);		// ??r14->_10
			rbx = _1a8;						// save _1a8
			if (0 != renderEncoder)			// via _150
			{
				if (0 != (mach_port)r13d)
				{
					if (0 == r12d)
					{
						r12d = ((CA::Render::Encoder*)renderEncoder)->receive_reply((mach_port)r13d); // a reply port.
						if (0x10000003 == r12d)
						{
							*(char*)&curContext->_c8 |= 1;
							r12d = 0x10000003;
						}
					}
					// <+2258>
					CA::Render::dispose_reply_port((mach_port)r13d, (int)r12d);
				}
				// <+2276>
				((CA::Render::Encoder*)renderEncoder)->~Encoder();
			}
			// <+2281>
			if (0 != rbx)
			{
				x_heap_free(rbx);
			}
			((CA::Context*)curContext)->unref(true);
			++_1a0;		// via rcx;

			// <+2334>
			if (retainedContextsLength2 > _1a0)
			{
				goto _b1152;		// a loop; do { if(!_180) break; ... } while(_180 > ++_1a0);
			}
			rdi <<= 3;
		}
		// <+2344>
		if (&contextBuffer2 != retainedContexts2)
		{
			if (rdi <= retainedContexts2)
			{
				rdi += 0xffffffff;
				rdi >>= 4;
				x_mem_dealloc_bucket((size_t)rdi, retainedContexts2);
			}
			else // <+2400>
			{
				x_mem_dealloc_size((size_t)rdi, retainedContexts2);
			}
		}
	}
	// <+2412>
	transaction->lock();
	transaction->run_deferred_visibility_layer_calls();
	transaction->unlock();

	if (0 == _1c0)
	{
		transaction->run_commit_handlers((CATransactionPhase)3);
		transaction->run_commit_handlers((CATransactionPhase)1);
	}
	// <+2472>
	transaction->run_commit_handlers((CATransactionPhase)2);
	if ((double)_160 == 0.f)
	{
		_160 = CACurrentMediaTime();
	}
	CA::Layer::set_next_animation_time(transaction, (double)_160, (double)_158);
	CARecordTransaction((double)_160);
	CABackingStoreCollectAsync((double)_160);
	CA::CG::Queue::collect((double)_160);

	if (__stack_chk_guard->_0 == _30)
	{
		return;
	}
	else
	{
		__stack_chk_fail();
	}
}


void CA::Transaction::observer_callback(__CFRunLoopObserver* observer, unsigned long, void*)
{
	// _0: rbp, _8: r15, _10: r14, _18: rbx, _20: rax
	// r15 as CA::Transaction
	CA::Transaction*& transaction = r15;							// &=r15
	rbx = rdi;	// observer
	if (CA::Transaction::transaction_key != 0)
	{
		transaction = pthread_getspecific(CA::Transaction::transaction_key);
		if (transaction != 0
			&& observer == transaction->_68)
		{
			CA::Transaction::Shared*& shared = transaction->_0;
			if (shared != 0
				&& shared->_10 != 0
				&& (shared->_68 & 0xff & 0x1))
			{
				r14 = objc_autoreleasePoolPush(CA::Transaction::transaction_key);
				((CA::Transaction*)r15)->commit();
				((CA::Transaction*)r15)->reset_animators();
				objc_autoreleasePoolPop(r14);
			}
			// <+108>
			if ((transaction->_84 & 0xff & 0x1)
				&& CA::callback_timer != 0
				&& x_list_find(CA::active_timers, CA::callback_timer) != 0)
			{
				CFRunLoopTimerInvalidate(CA::callback_timer);
				CFRelease(CA::callback_timer);
				*(int64) (((char*)&CA::Transaction::create()::onceet) + 4) = 0;
				retrun CA::update_timer();
			}
		}
	}
	// <+197>
}


void CA::Transaction::commit()
{
	// _0: rbp, _8: r15, _10: r14, _18: r13, _20: r12, _28: rbx
	// local variables from _40 to _30; total 0x18;
	rbx = rdi;	// this;
	if (&this->_88 == this->_0)
	{
		if (OSAtomicCompareAndSwapInt(0, 1, &this->_80))	// flag e is set 1, means the oldvalue is equled.
		{
			_30 = 0.f;
			ecx = 0;
			r8d = 0;
			if (YES == this->get_value((unsigned int)0xfa, (_CAValueType)0x12, (void*)&_30))
			{
				rcx = CAHostTimeWithTime((double)_30);
				r8d = rcx & 0xffffffff;
				rcx >>= 0x20;
			}
			// <+119>
			r15d = 0;
			kdebug_trace(0x31ca0005, 0, 0, ecx, r8d);
	
			al = ture;
			CA::Transaction::Shared*& shared = r13;					// &=r13
			shared = this->_0;
			r14 = &CA::Transaction::roots_lock;
			r12 = &_38;
		_b152:		// <+642>, <+655>
			_3c = eax; 
			*(char*)&this->_84 &= 0xfd;
			if (shared->_18 != 0)
			{
				rsi = 0;
				if (shared->_18 != 0)
				{
					rcx = shared->_18;
				/***
				* reverse the link
				* finally, rsi is the head.
				*/
				_b183:		// <+198>
					do
					{
						rax = rcx->_0;
						rcx->_0 = rsi;
						rsi = rcx;
						rcx = rax;
					} while (rax != 0);
				}
				// <+200>
				this->_38 = (CA::Transaction::Command*)rsi;		// a reserved link or null.
				// <+212>: jmp <+222>
			_b214:		// <+352>
				OSSpinLockUnlock(&roots_lock);
			}
			// <+222>
			while (1)
			{
				OSSpinLockLock(&roots_lock);
				if (CA::Transaction::roots != 0)
				{
					if (this->_58 != 0)
					{
						x_hash_table_foreach(CA::Transaction::roots,
							(void(CA::*)(CA::Layer*, CA::Layer*, void*))&CA::move_root);
						x_hash_table_remove_all(CA::Transaction::roots);
					}
					else
					{
						this->_58 = CA::Transaction::roots;
						CA::Transaction::roots = 0;
					}
				}
				// <+292>
				OSSpinLockUnlock(&roots_lock);
				if (this->_58 != 0)
				{
					x_hash_table_remove_if(this->_58,
						(void(CA::*)(CA::Layer*, CA::Layer*, void*))&release_root_if_unused);
				}
				OSSpinLockLock(&roots_lock);
#if 0
				if (CA::Transaction::roots != 0)
				{
					if (x_hash_table_size(CA::Transaction::roots) != 0)
						goto _b214;
				}
#else
				if (CA::Transaction::roots == 0
					|| x_hash_table_size(CA::Transaction::roots) == 0)
				{
					break;
				}
				OSSpinLockUnlock(&roots_lock);
#endif
			} 

			// <+358>
			OSSpinLockUnlock(&roots_lock);
			if (shared->_20 != 0)
			{
				this->_40 = shared->_20;
				shared->20 = 0;
			}

		_b389:	// <+416>, <+476>
			while (CA::Transaction::global_deleted != 0)
			{
				void* old = CA::Transaction::global_deleted;
				if (!OSAtomicCompareAndSwapPtr(CA::Transaction::global_deleted,
					r15,
					&CA::Transaction::global_deleted))
					continue;
			_b418:	// <+466>
				_38 = old->_0;
				rdx = old->_0;
				rsi = r12;
				if (old->_0 != 0)
				{
				_b433:	// 442
#if 0
					rsi = rdx;
					rdx = rdx->_0;
					if (rdx != 0)
						goto _b433;
#else 
					do
					{
						rsi = rdx;
					} while (rdx = rdx->_0);
#endif
				}
				// <+444>
				rsi->_0 = this->_40;
				this->_40 = _38;
				if (old->_8 != 0)		//????? dead loop
					goto _b418;
				x_list_free(rcx);
			}
			// <+478> out of the loop
			CA::Context::commit_transaction((CA::Transaction*)this);
			if (this->_40 != 0)
			{
				x_mem_dealloc_chain(0x18, this->_40, 0);
				this->_40 = 0;
			}
			if (this->_58 != 0)
			{
				x_hash_table_foreach(this->_58,
					(void(CA::*)(CA::Layer*, CA::Layer*, void*))&release_root,
					this);
				x_hash_table_free(this->_58);
				this->_58 = 0;
			}
			if (this->_38 != 0)
			{
				CA::Transaction::free_command_list((CA::Transaction::Command*)this->_38);
				this->_38 = 0;
			}
#if 0
			else
			{
				r13->_28 = r15->_0;
				((CA::Transaction::Fence*)r15)->~Fence();
				x_mem_dealloc_bucket(1, r15);
			}
#endif

			// <+608>, loop between <+580> to <+615>
			while (shared->_28 != 0)
			{
				r15 = shared->_28;
				shared->_28 = r15->_0;
				((CA::Transaction::Fence*)r15)->~Fence();
				x_mem_dealloc_bucket(1, r15);
			}  
			CA::Layer::free_transaction((CA::Transaction*)this);
			r15d = 0;
			if (_3c == true)
			{
				goto _f661;		// break;
			}
			if (r13->_20 != 0
				|| r13->_18 != 0)
				goto _b152;		// continue;

			// break;
			
		_f661:

		}
	}
	// <+865>
	
}

620	callq	
672	callq	x_hash_table_free
705	callq	symbol stub for: OSSpinLockLock
746	callq	symbol stub for : OSSpinLockUnlock
771	callq	x_heap_free
841	callq	CA::Transaction::Level::free_levels(CA::Transaction::Level*)
860	callq	symbol stub for : kdebug_trace
892	callq	symbol stub for : OSSpinLockUnlock
920	callq	symbol stub for : kdebug_trace
928	callq	symbol stub for : _Unwind_Resume

