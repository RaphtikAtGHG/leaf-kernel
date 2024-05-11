#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <stdint.h>

void bitmap_set(uint8_t *bitmap, uint64_t bit);
void bitmap_clear(uint8_t *bitmap, uint64_t bit);
uint8_t bitmap_get(uint8_t *bitmap, uint64_t bit);

#endif	// __BITMAP_H__