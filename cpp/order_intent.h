#pragma once
#include <cstdint>

enum class Side : uint8_t {
    BUY = 0,
    SELL = 1
};

struct OrderIntent {
    /* data */
    uint64_t ts_ns; // timestamp(ns)
    uint32_t insrument; // contract id
    uint32_t qty; // volume
    double price;
    Side side;
};
