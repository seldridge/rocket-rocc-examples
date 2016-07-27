#ifndef SRC_ROCC_H
#define SRC_ROCC_H

// Standard macro that passes rd_, rs1_, and rs2_ via registers
#define ROCC_INSTRUCTION(XCUSTOM_, rd_, rs1_, rs2_, funct_)       \
  ROCC_INSTRUCTION_R_R_R(rd_, rs1_, rs2_, funct_)
#define ROCC_INSTRUCTION_R_R_R(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "r" (rs1_), [rs2] "r" (rs2_), [funct] "i" (funct_))

// Macro to pass rs2_ as an immediate
#define ROCC_INSTRUCTION_R_R_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "r" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))

// Macro to pass rs1_ and rs2_ as immediates
#define ROCC_INSTRUCTION_R_I_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "i" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))

#endif  // SRC_ACCUMULATOR_H
