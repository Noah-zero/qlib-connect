#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    void* shm = mmap(
        nullptr,
        4096,
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    if (shm == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    while (true) {
        int value;
        std::memcpy(&value, shm, sizeof(int));
        std::cout << "C++ read: " << value << std::endl;
        sleep(1);
    }
}