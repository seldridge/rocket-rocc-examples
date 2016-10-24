// See LICENSE for license details.

#ifndef SRC_MAIN_C_ACCUMULATOR_H
#define SRC_MAIN_C_ACCUMULATOR_H

#include <stdio.h>
#include <stdint.h>
#include "rocc.h"

typedef enum {
  k_DO_WRITE = 0,
  k_DO_READ,
  k_DO_LOAD,
  k_DO_ACCUM
} funct_accumulator_t;

#define XCUSTOM_ACC "custom0"

uint64_t doWrite(uint16_t rocc_rd, uint64_t data);
uint64_t doRead(uint16_t rocc_rd);
uint64_t doLoad(uint16_t rocc_rd, void * addr);
uint64_t doAccum(uint16_t rocc_rd, uint64_t data);

#endif  // SRC_MAIN_C_ACCUMULATOR_H
