Collection of example libraries and test programs for the existing Rocket Custom Coprocessor (RoCC) accelerators for [Rocket Chip](https://github.com/ucb-bar/rocket-chip).

## Usage

This has been verified as working [`rocket-chip:44eb4d12`](https://github.com/ucb-bar/rocket-chip/tree/44eb4d12).

Install the RISC-V toolchain and make sure that it's on your path.
You need to pass the path to `riscv-tools` in as an argument to configure `--with-riscvtools=$PATH_TO_RISCV_TOOLS`.

```
autoconf
mkdir build && cd build
../configure --with-riscvtools=$PATH_TO_RISCV_TOOLS
make
```

This creates two classes of tests:
* `bareMetal` -- Bare metal tests like [RISCV Tests](https://github.com/riscv/riscv-tests)
* `pk` -- Tests that use the [Proxy Kernel](https://github.com/riscv/riscv-pk)

Bare Metal tests can be run directly on the emulator (for instructions on how to build this see the following section), e.g.:

```
emulator-freechips.rocketchip.system-RoccExampleConfig bareMetal/examples-bareMetal-p-accumulator
```

Proxy Kernel tests are ELFs and need the Proxy Kernel (or Linux).
You must first patch the Proxy Kernel so that the `XS` bits allow access to the "extension" (the RoCC).
You can change this manually or use the provided patch ([`patches/riscv-pk.patch`](patches/riscv-pk.patch)):
```
cd $RISCV_PK_DIR
git apply $THIS_REPO_DIR/patches/riscv-pk.patch

mkdir build
cd build
../configure --prefix=$RISCV/riscv64-unknown-elf --host=riscv64-unknown-elf
make
make install
```

Following that, you can run Proxy Kernel tests, e.g., :

```
emulator-freechips.rocketchip.system-RoccExampleConfig pk pk/examples-pk-accumulator
```

## Building a Rocket Chip Emulator

Build a rocket-chip emulator with the RoCC examples baked in and run the provided test program:
```
cd $ROCKETCHIP_DIR/emulator
make CONFIG=RoccExampleConfig
```

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
