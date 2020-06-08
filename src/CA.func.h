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
#ifndef _CA_func__H_
#define _CA_func__H_

#include "CA.namespace.h"
#include "CA.struct.h"
void CABackingStoreUpdate_(CABackingStore* content, unsigned int width, unsigned int height,
	unsigned int flag1, unsigned int flag2,
	void(*backing_callback)(CGContext*, void*),
	CA::Layer* layer, CA::GenericContext* context);
void async_collect_callback(void*);
void backing_store_callback(double, void*);
void CABackingStoreCollect(double);
void CABackingStoreCollect_(double, bool);

namespace CA
{
	void CA::call_at_time(void(*backing_store_callback)(double, void*), double curMediaTime, void* unknown);
}

0xc010000000000000; -4.;
0xc000000000000000; -2.;
0xbff0000000000000; -1.;
0x3fe0000000000000; .5;
0x3ff0000000000000; 1.;
0x4000000000000000; 2.;
0x4008000000000000; 3.;
0x4010000000000000; 4.;
0x4014000000000000; 5.;
0x4020000000000000;	8.;
0x4030000000000000; 16.;

double inf;
double FLT_MAX;

#endif // _CA_func__H_