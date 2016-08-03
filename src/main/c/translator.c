#include <stdint.h>
#include "translator.h"
#include "rocc.h"

uint64_t doTranslate(void *vaddr) {
  uint64_t y;
  ROCC_INSTRUCTION_R_R_R(XCUSTOM_TRANS, y, (uint64_t) vaddr, 0, 0);
  return y;
}
