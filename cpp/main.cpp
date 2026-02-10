#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "order_intent.h"

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
        OrderIntent oi;
        std::memcpy(&oi, shm, sizeof(OrderIntent));

        std::cout<< "C++ read OrderIntend: "
            << "ts=" << oi.ts_ns
            << ", inst=" << oi.insrument
            << ", qty=" << oi.qty
            << ", price= " << oi.price
            << ", side=" << (oi.side == Side::BUY ? "BUY" : "SELL")
            << std::endl;
        
        sleep(1);
    }
}