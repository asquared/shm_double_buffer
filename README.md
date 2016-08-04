# ShmDoubleBuffer
A simple class for shoveling asynchronously-updated data from one process
to another. Probably most useful for framebuffer-type data where one process
is rendering and another is consuming the data.

## Usage
One process needs to create the buffer:

```
ShmDoubleBuffer buf(buf_size);
```

Then it can fork a child process:
```
pid_t pid = fork();
if (pid == 0) {
	dup2(buf.get_fd(), 9);
	execl("child_binary", "child_binary", NULL);
} else if (...) { 
 ...
}
```

and read from the buffer:
```
void *ptr;
buf.begin_read(ptr);
cout << *(int *)ptr << endl;	/* for example - do what you want with ptr */
buf.end_read();
```

The child process instantiates the buffer using the fd:
```
ShmDoubleBuffer buf;
buf.init_from_fd(9);
```

After that's done, it can write to the buffer:
```
void *ptr;
bool flipped;

buf.begin_write(ptr, flipped);
if (flipped) {
	/* write all new data */
} else {
	/* update what's already in the buffer */
}
buf.end_write();
```

That's all there is to it!

The consumer will always see the most recent *fully written* buffer - that 
is, it will either see the buffer contents as they were before begin_write
was called, or it will see them as they were at the time end_write was called.
That is, from the consumer's perspective, everything between begin_write and
end_write appears as one atomic write.

## Portability
This code makes use of the Linux-specific syscall `memfd_create`. If you want 
to port it, some systems provide similar functionality via the `shm_open()` 
syscall with an empty string for the name. 

## License
MIT - see LICENSE file.
