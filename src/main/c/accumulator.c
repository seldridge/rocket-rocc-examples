#include "src/main/c/accumulator.h"

uint64_t doWrite(uint16_t rocc_rd, uint64_t data) {
  uint64_t y;
  ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, data, (uint64_t) rocc_rd, k_DO_WRITE);
  return y;
}

uint64_t doRead(uint16_t rocc_rd) {
  uint64_t y;
  ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, 0, (uint64_t) rocc_rd, k_DO_READ);
  return y;
}

uint64_t doLoad(uint16_t rocc_rd, uint64_t * mem_addr) {
  uint64_t y;
  ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, mem_addr, rocc_rd, k_DO_LOAD);
  return y;
}

uint64_t doAccum(uint16_t rocc_rd, uint64_t data) {
  uint64_t y;
  ROCC_INSTRUCTION_R_R_R(XCUSTOM_ACC, y, data, (uint64_t) rocc_rd, k_DO_ACCUM);
  return y;
}
