// See LICENSE for license details.

#ifndef SRC_MAIN_C_ROCC_H
#define SRC_MAIN_C_ROCC_H

#define STR1(x) #x
#define STR(x) STR1(x)
#define EXTRACT(a, size, offset) (((~(~0 << size) << offset) & a) >> offset)

#define CUSTOMX_OPCODE(x) CUSTOM_ ## x
#define CUSTOM_0 0b0001011
#define CUSTOM_1 0b0101011
#define CUSTOM_2 0b1011011
#define CUSTOM_3 0b1111011

#define CUSTOMX(X, rd, rs1, rs2, funct)         \
  CUSTOMX_OPCODE(X)                   |         \
  (rd                   << (7))       |         \
  (0x7                  << (7+5))     |         \
  (rs1                  << (7+5+3))   |         \
  (rs2                  << (7+5+3+5)) |         \
  (EXTRACT(funct, 7, 0) << (7+5+3+5+5))

// Standard macro that passes rd, rs1, and rs2 via registers
#define ROCC_INSTRUCTION(X, rd, rs1, rs2, funct)                \
  ROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct, 10, 11, 12)

// rd, rs1, and rs2 are data
// rd_n, rs_1, and rs2_n are the register numbers to use
#define ROCC_INSTRUCTION_R_R_R(X, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) { \
    register uint64_t rd_  asm ("x" # rd_n);                            \
    register uint64_t rs1_ asm ("x" # rs1_n) = (uint64_t) rs1;          \
    register uint64_t rs2_ asm ("x" # rs2_n) = (uint64_t) rs2;          \
    asm volatile (                                                      \
        ".word " STR(CUSTOMX(X, rd_n, rs1_n, rs2_n, funct)) "\n\t"      \
        : "=r" (rd_)                                                    \
        : [_rs1] "r" (rs1_), [_rs2] "r" (rs2_));                        \
    rd = rd_;                                                           \
  }

#define ROCC_INSTRUCTION_R_R_R_REGF(X, fd, fs1, fs2, funct) {           \
    register uint64_t rd_  asm ("x27");                                 \
    register uint64_t rs1_ asm ("x28");                                 \
    register uint64_t rs2_ asm ("x29");                                 \
    asm volatile ("fmv.x.s x28, f28");                                  \
    asm volatile ("fmv.x.s x29, f29");                                  \
    asm volatile (                                                      \
        " fmv.x.s x28, %[fs1] \n\t"                                     \
        " fmv.x.s x29, %[fs2] \n\t"                                     \
        ".word " STR(CUSTOMX(X, 27, 28, 29, funct)) "\n\t"              \
        " fmv.x.s %[fd], x27 \n\t"                                      \
        : "=r" (rd_)                                                    \
        : [_rs1] "r" (rs1_), [_rs2] "r" (rs2_));                        \
    asm volatile ("fmv.s.x f27, x27");                                  \
    rd = rd_;                                                           \
  }

// [TODO] fix these to align with the above approach
// Macro to pass rs2_ as an immediate
/*
#define ROCC_INSTRUCTION_R_R_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "r" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))

// Macro to pass rs1_ and rs2_ as immediates
#define ROCC_INSTRUCTION_R_I_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "i" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))
*/

#endif  // SRC_MAIN_C_ACCUMULATOR_H
