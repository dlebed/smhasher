#include "xmsx.h"
#include <string.h>

static uint64_t xmsx32_round(uint64_t h, uint32_t d)
{
    const uint64_t p = 0xcdb32970830fcaa1ULL;

    h = (h ^ d) * p;
    h ^= h >> 32;

    return h;
}

uint32_t xmsx32(const void *buf, size_t len, uint32_t seed)
{
    const unsigned char *data = (const unsigned char *)buf;
    const size_t batch_len = sizeof(uint32_t) * 2;
    uint64_t h = ((uint64_t)seed << 32) | seed;

    h = xmsx32_round(h, len);

    while (len >= batch_len) {
        uint32_t d[2];

        memcpy(d, data, batch_len);

        h = xmsx32_round(h, d[0]);
        h = xmsx32_round(h, d[1]);

        len -= batch_len;
        data += batch_len;
    }

    while (len) {
        uint32_t d;

        memcpy(&d, data, sizeof(d));

        if (len < 4) {
            const size_t bits_to_clear = 8 * (sizeof(d) - len);

            d <<= bits_to_clear;
            d >>= bits_to_clear;
            len = 4;
        }

        h = xmsx32_round(h, d);

        len -= 4;
        data += 4;
    }

    return xmsx32_round(h, h >> 47);
}
