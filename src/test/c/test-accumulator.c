#include <assert.h>
#include "src/main/c/accumulator.h"

int main() {

  uint64_t data = 0xdead;
  uint16_t addr = 1;
  printf("[INFO] Write R[%d] = %lx\n", addr, data);
  doWrite(addr, data);

  printf("[INFO] Read R[%d]\n", addr);
  uint64_t y = doRead(addr);
  printf("[INFO]   Received %lx\n", y);
  assert(y == data);

  uint64_t data_accum = -0x1fbe;
  printf("[INFO] Accum R[%d] with %lx\n", addr, data_accum);
  y = doAccum(addr, data_accum);
  printf("[INFO]   Received %lx\n", y);
  assert(y == data);

  printf("[INFO] Read R[%d]\n", addr);
  y = doRead(addr);
  printf("[INFO]   Received %lx\n", y);
  assert(y == data + data_accum);

  // doLoad appears to be currently broken with the Accumulator
  // example in rocc.scala (an assertion is firing in the
  // SimpleHellaCacheIF). The commented-out skeleton below should be
  // the right approach:

  // data = 0xbeef;
  // uint64_t * data_addr = &data;
  // printf("[INFO] Load %lx (0x%lx) via L1 data cache\n",
  //        data, (uint64_t) data_addr);
  // printf("[INFO]   Reading back in software [0x%lx] = %lx\n",
  //        (uint64_t) data_addr, *data_addr);
  // y = doLoad(addr, data_addr);
  // printf("[INFO] y = %lx\n", y);

  return 0;
}
