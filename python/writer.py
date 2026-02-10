import mmap
import time
import struct

# Q = uint64
# I = uint32
# I = uint32
# d = double
# B = uint8
fmt = "QIIdB"

size = struct.calcsize(fmt)

with open("/tmp/qlib_shm", "wb") as f:
    f.write(b"\x00" * 4096)

with open("/tmp/qlib_shm", "r+b") as f:
    mm = mmap.mmap(f.fileno(), 4096)

    while True:
        order = (
            int(time.time_ns()),
            1,
            10,
            99.5,
            0
        )

        mm.seek(0)
        mm.write(struct.pack(fmt, *order))
        print("Python wrote OrderIntent:", order)
        time.sleep(1)
