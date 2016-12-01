// See LICENSE for license details.

#ifndef SRC_MAIN_C_TRANSLATOR_H
#define SRC_MAIN_C_TRANSLATOR_H

#define XCUSTOM_TRANS 1

#define doTranslate(y, vaddr)                                \
    ROCC_INSTRUCTION_R_R_R(XCUSTOM_TRANS, y, vaddr, 0, 0);

#endif  // SRC_MAIN_C_TRANSLATOR_H
