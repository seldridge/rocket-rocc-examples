// See LICENSE for license details.

#ifndef SRC_MAIN_C_TRANSLATOR_H
#define SRC_MAIN_C_TRANSLATOR_H

#define XCUSTOM_TRANS 1

#define doTranslate(y, vaddr) {                                         \
    register uint64_t rd asm ("a0");                                    \
    register uint64_t rs1 asm ("a1") = (uint64_t) vaddr;                \
    register uint64_t rs2 asm ("a2") = (uint64_t) 0;                    \
    ROCC_INSTRUCTION_R_R_R(XCUSTOM_TRANS, y, (uint64_t) rs1, rs2, 0);   \
    y = (uint64_t * ) rd;                                               \
  }

#endif  // SRC_MAIN_C_TRANSLATOR_H
