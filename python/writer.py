import mmap
import time
import struct

# Create an anonymous memory-mapped region of 4096 bytes (4 KB).
# -1 means no file backing; the mapping exists only in memory.
# This memory can be shared between processes if they inherit or
# are given access to the same mmap handle.
mm = mmap.mmap(-1, 4096)

counter = 0

while True:
    # Move the mmap internal pointer back to the beginning (offset 0).
    # Required before re-writing or re-reading from the start of
    # the shared memory region.
    mm.seek(0)
    # Pack the integer `counter` into 4 bytes using C int format
    # and write it to the current mmap file pointer position.
    # This effectively stores the counter value in shared memory.
    mm.write(struct.pack("i", counter))
    print("Python wrote:", counter)
    counter += 1
    time.sleep(1)