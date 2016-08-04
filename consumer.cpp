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
 * Test consumer for ShmDoubleBuffer. Prints the integer value stored
 * in the buffer.
 */
#include "shm_double_buffer.h"
#include <unistd.h>
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

int main() {
	/* create buffer */
	ShmDoubleBuffer buf(sizeof(int) * 9999);
	const void *ptr;

	/* fork producer process */
	int pid = fork();
	if (pid == -1) {
		perror("fork");
		return 1;
	} else if (pid == 0) {
		dup2(buf.get_fd(), 9);
		execl("./producer", "./producer", NULL);
		_exit(1);	/* if we fall through here just kill it */
	}

	for (;;) {
		buf.begin_read(ptr);
		cout << "got " << *(int *)(ptr) << endl;
		buf.end_read();

		/* sleep a bit rather than spinning */
		usleep(100);
	}

}