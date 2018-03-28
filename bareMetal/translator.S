#include "riscv_test.h"
#include "riscv-tests/isa/macros/scalar/test_macros.h"
#include "include/translator.h"
#include "rocc-software/src/riscv_test_rocc.h"

#ifdef _ENV_VIRTUAL_SINGLE_CORE_H
  RVTEST_RV64U
#else
  RVTEST_WITH_ROCC
#endif
  RVTEST_CODE_BEGIN

  la a1, data
  ROCC_INSTRUCTION_RAW_R_R_R(XCUSTOM_TRANS, 10, 11, 0, 0)
  xor a2, a2, a2
  beq a0, a1, 1f
  addi a2, a2, 1
1:
  TEST_CASE( 2, a0, 0, )

  TEST_PASSFAIL

  RVTEST_CODE_END

  .data
  RVTEST_DATA_BEGIN

  TEST_DATA
data:
  .dword 0xdead

  RVTEST_DATA_END
