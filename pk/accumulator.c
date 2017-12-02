// See LICENSE for license details.

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "include/accumulator.h"
#include "include/translator.h"

int main() {

  uint64_t data [] = {0xdead, 0xbeef, 0x0bad, 0xf00d}, y;

  uint16_t addr = 1;
  printf("[INFO] Write R[%d] = 0x%lx\n", addr, data[0]);
  doWrite(y, addr, data[0]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[0]);
  assert(y == data[0]);

  uint64_t data_accum = -data[0] + data[1];
  printf("[INFO] Accum R[%d] with 0x%lx\n", addr, data_accum);
  doAccum(y, addr, data_accum);
  assert(y == data[0]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[1]);
  assert(y == data[1]);

  uint64_t data_addr;
  doTranslate(data_addr, &data[2]);
  printf("[INFO] Load 0x%lx (virt: 0x%p, phys: 0x%p) via L1 virtual address\n",
         data[2], &data[2], (void *) data_addr);
  doLoad(y, addr, &data[2]);
  assert(y == data[1]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[2]);
  assert(y == data[2]);

  return 0;
}
