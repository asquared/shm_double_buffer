/*
 * Copyright (c) 2016 Andrew H. Armenia.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Test producer for ShmDoubleBuffer. Writes a constantly-incremented
 * integer to the buffer. Intended to be run as a child process of
 * the test consumer (consumer.cpp).
 */

#include "shm_double_buffer.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

int main() {
	/* parent process hands off the buffer on fd 9 */
	ShmDoubleBuffer buf;
	buf.init_from_fd(9);

	void *ptr;
	bool flipped;
	int i = 0;

	for (;;) {
		buf.begin_write(ptr, flipped);
		if (flipped) {
			i++;
			*(int *)(ptr) = i;
		}
		buf.end_write();
		usleep(1000);
	}

}
