Collection of example libraries and test programs for the existing Rocket Custom Coprocessor (RoCC) accelerators for [Rocket Chip](https://github.com/ucb-bar/rocket-chip).

## Usage

This has been verified as working [`rocket-chip:44eb4d12`](https://github.com/ucb-bar/rocket-chip/tree/44eb4d12).

Install the RISC-V toolchain and make sure that it's on your path. You need to build a patched Proxy Kernel that will set the `XS` bits to allow access to the "extension", i.e., some RoCC accelerator. You can change this manually or use the provided patch ([`patches/riscv-pk.patch`](patches/riscv-pk.patch)):
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
> time $ROCKETCHIP_DIR/emulator-freechips.rocketchip.system-RoccExampleConfig -c pk ./build/test-accumulator
[INFO] Write R[1] = 0xdead
[INFO] Read R[1]
[INFO]   Received 0xdead (expected 0xdead)
[INFO] Accum R[1] with 0xffffffffffffe042
[INFO] Read R[1]
[INFO]   Received 0xbeef (expected 0xbeef)
[INFO] Load 0xbad (virt: 0x0xfee9ac0, phys: 0x0x8ffffac0) via L1 virtual address
[INFO] Read R[1]
[INFO]   Received 0xbad (expected 0xbad)
Completed after 3278954 cycles

real	5m2.738s
user	5m0.262s
sys	0m1.179s
```
