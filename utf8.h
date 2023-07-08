#ifndef BOB_DECRYPTOR_UTF8_H
#define BOB_DECRYPTOR_UTF8_H

#include <stdint.h>
#include <sys/types.h>

__attribute__((externally_visible))
size_t UTF8(const uint8_t* utf8, size_t n);

#endif //BOB_DECRYPTOR_UTF8_H
