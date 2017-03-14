Collection of example libraries and test programs for the existing Rocket Custom Coprocessor (RoCC) accelerators for [Rocket Chip](https://github.com/ucb-bar/rocket-chip).

## Usage

This has been verified as working with the following commits:
  * [`rocket-chip:c5310938`](https://github.com/ucb-bar/rocket-chip/tree/c531093898f1f4ff22d1c2cf9d5bb2310d05fc31)
  * [`riscv-tools:cd78e37`](https://github.com/riscv/riscv-tools/tree/cd78e37f72cfc2a452a0c11744586084fbae1dcd)
Note: this `riscv-tools` is ahead of what is pointed at by `rocket-chip`.

Install the RISC-V toolchain and make sure that it's on your path. You need to build a patched Proxy Kernel that will set the `XS` bits to allow access to the "extension", i.e., some RoCC accelerator. Additionally, with Rocket's config string specification in flux, you need to hard-code the memory size that the proxy kernel reads. You can change this manually or use the provided patch ([`patches/riscv-pk.patch`](patches/riscv-pk.patch)):
```
cd $RISCV_PK_DIR
git apply $THIS_REPO_DIR/patches/riscv-pk.patch

mkdir build
cd build
../configure --prefix=$RISCV/riscv64-unknown-elf --host=riscv64-unknown-elf
make
make install
```

Build everything in this repository (`librocc.a` and `test-accumulator`):
```
cd $THIS_REPO_DIR
make
```

Build a rocket-chip emulator with the RoCC examples baked in and run the provided test program:
```
cd $ROCKETCHIP_DIR/emulator
make CONFIG=RoccExampleConfig
./emulator-Top-RoccExampleConfig $RISCV_PK_DIR/build/pk $THIS_REPO_DIR/build/test-accumulator
```
Note: `make install` in `$RISCV_PK_DIR/build` should install the patched proxy kernel in `$RISCV/riscv64-unknown-elf/bin/` and the emulator should find this correctly by just specifying `./emulator-Top-RoccExampleConfig pk [binary]`. However, I'm being explicit in referencing the patched proxy kernel with a full path in the command above.

### Expected Run Time

The included test should run for ~5 million cycles over a wall clock time of ~5 minutes.

```
> time $ROCKETCHIP_DIR/emulator-rocketchip-RoccExampleConfig -c pk ./build/test-accumulator
[INFO] Write R[1] = 0xdead
[INFO] Read R[1]
[INFO]   Received 0xdead
[INFO] Accum R[1] with 0xffffffffffffe042
[INFO] Read R[1]
[INFO]   Received 0xbeef
[INFO] Load 0xbad (virt: 0x0xfeefac0, phys: 0x0x8ffffac0) via L1 data cache
[INFO] Read R[1]
[INFO]   Received 0xbad
Completed after 5614110 cycles

real	5m32.001s
user	5m30.534s
sys	0m0.461s
```
