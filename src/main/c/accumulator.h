// See LICENSE for license details.

#ifndef SRC_MAIN_C_ACCUMULATOR_H
#define SRC_MAIN_C_ACCUMULATOR_H

#include <stdio.h>
#include <stdint.h>
#include "rocc.h"

#define k_DO_WRITE 0
#define k_DO_READ 1
#define k_DO_LOAD 2
#define k_DO_ACCUM 3

#define XCUSTOM_ACC 0

#define doWrite(y, rocc_rd, data) {                                     \
    register uint64_t rd asm ("a0");                                    \
    register uint64_t rs1 asm ("a1") = data;                            \
    register uint64_t rs2 asm ("a2") = (uint64_t) rocc_rd;              \
    ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, rs1, rs2, k_DO_WRITE);       \
    y = rd;                                                             \
  }
#define doRead(y, rocc_rd) {                                            \
    register uint64_t rd asm ("a0");                                    \
    register uint64_t rs1 asm ("a1") = 0;                               \
    register uint64_t rs2 asm ("a2") = rocc_rd;                         \
    ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, rs1, rs2, k_DO_READ);        \
    y = rd;                                                             \
  }
#define doLoad(y, rocc_rd, mem_addr) {                                  \
    register uint64_t rd asm ("a0");                                    \
    register uint64_t rs1 asm ("a1") = (uint64_t) mem_addr;             \
    register uint64_t rs2 asm ("a2") = rocc_rd;                         \
    ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, rs1, rs2, k_DO_LOAD);        \
    y = rd;                                                             \
  }
#define doAccum(y, rocc_rd, data) {                                     \
    register uint64_t rd asm ("a0");                                    \
    register uint64_t rs1 asm ("a1") = data;                            \
    register uint64_t rs2 asm ("a2") = rocc_rd;                         \
    ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, rs1, rs2, k_DO_ACCUM);       \
    y = rd;                                                             \
  }

#endif  // SRC_MAIN_C_ACCUMULATOR_H
