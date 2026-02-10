import mmap
import time
import struct

with open("/tmp/qlib_shm", "wb") as f:
    f.write(b"\x00" * 4096)

with open("/tmp/qlib_shm", "r+b") as f:
    mm = mmap.mmap(f.fileno(), 4096)

    counter = 0
    while True:
        mm.seek(0)
        mm.write(struct.pack("i", counter))
        print("Python wrote:", counter)
        counter += 1
        time.sleep(1)