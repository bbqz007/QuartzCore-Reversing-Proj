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


#pragma once
#ifndef _OSAtomic__H_
#define _OSAtomic__H_

struct OSSpinLock;
struct OSQueueHead;
int32_t
OSAtomicAdd32(int32_t theAmount, volatile int32_t *theValue);

int32_t
OSAtomicAdd32Barrier(int32_t theAmount, volatile int32_t *theValue);

int32_t
OSAtomicIncrement32(volatile int32_t *theValue);

int32_t
OSAtomicIncrement32Barrier(volatile int32_t *theValue);

int32_t
OSAtomicDecrement32(volatile int32_t *theValue);

int32_t
OSAtomicDecrement32Barrier(volatile int32_t *theValue);

int32_t
OSAtomicOr32(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicOr32Barrier(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicAnd32(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicAnd32Barrier(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicXor32(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicXor32Barrier(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicOr32Orig(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicOr32OrigBarrier(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicAnd32Orig(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicAnd32OrigBarrier(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicXor32Orig(uint32_t theMask, volatile uint32_t *theValue);

int32_t
OSAtomicXor32OrigBarrier(uint32_t theMask, volatile uint32_t *theValue);

int64_t
OSAtomicAdd64(int64_t theAmount, volatile int64_t *theValue);

int64_t
OSAtomicAdd64Barrier(int64_t theAmount, volatile int64_t *theValue);

int64_t
OSAtomicIncrement64(volatile int64_t *theValue);

int64_t
OSAtomicIncrement64Barrier(volatile int64_t *theValue);

int64_t
OSAtomicDecrement64(volatile int64_t *theValue);

int64_t
OSAtomicDecrement64Barrier(volatile int64_t *theValue);

bool
OSAtomicCompareAndSwapInt(int oldValue, int newValue,
	volatile int *theValue);

bool
OSAtomicCompareAndSwapIntBarrier(int oldValue, int newValue,
	volatile int *theValue);

bool
OSAtomicCompareAndSwapLong(long oldValue, long newValue,
	volatile long *theValue);

bool
OSAtomicCompareAndSwapLongBarrier(long oldValue, long newValue,
	volatile long *theValue);

bool
OSAtomicCompareAndSwapPtr(void* oldValue, void* newValue,
	void* volatile *theValue);

bool
OSAtomicCompareAndSwapPtrBarrier(void* oldValue, void* newValue,
	void* volatile *theValue);

bool
OSAtomicCompareAndSwap32(int32_t oldValue, int32_t newValue,
	volatile int32_t *theValue);

bool
OSAtomicCompareAndSwap32Barrier(int32_t oldValue, int32_t newValue,
	volatile int32_t *theValue);

bool
OSAtomicCompareAndSwap64(int64_t oldValue, int64_t newValue,
	volatile int64_t *theValue);

bool
OSAtomicCompareAndSwap64Barrier(int64_t oldValue, int64_t newValue,
	volatile int64_t *theValue);

bool
OSAtomicTestAndSet(uint32_t n, volatile void *theAddress);

bool
OSAtomicTestAndSetBarrier(uint32_t n, volatile void *theAddress);

bool
OSAtomicTestAndClear(uint32_t n, volatile void *theAddress);

bool
OSAtomicTestAndClearBarrier(uint32_t n, volatile void *theAddress);

bool
OSSpinLockTry(OSSpinLock *lock);

void
OSSpinLockLock(OSSpinLock *lock);

void
OSSpinLockUnlock(OSSpinLock *lock);

void
OSAtomicEnqueue(OSQueueHead *list, void *new, size_t offset);

void*
OSAtomicDequeue(OSQueueHead *list, size_t offset);

#endif // _OSAtomic__H_