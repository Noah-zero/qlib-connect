#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    int fd = open("/tmp/qlib_shm", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    void* shm = mmap(
        nullptr, 4096,
        PROT_READ | PROT_WRITE,
        MAP_SHARED, fd, 0
    );
    
    if (shm == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    while (true) {
        int value;
        std::memcpy(&value, shm, sizeof(int));
        std::cout << "C++ read:" << value << std::endl;
        sleep(1);
    }
}