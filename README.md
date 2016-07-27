Collection of example libraries and test programs for the existing Rocket Custom Coprocessor (RoCC) accelerators for [Rocket Chip](https://github.com/ucb-bar/rocket-chip).

## Usage

Install the RISC-V toolchain and make sure that it's on your path. You need to build a patched Proxy Kernel that will set the `XS` bits to allow access to the "extension", i.e., some RoCC accelerator. You can change this manually or use the provided patch (patches/riscv-pk.patch):
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
cd $ROCKET_CHIP_DIR/emulator
make CONFIG=RoccExampleConfig
./emulator-Top-RoccExampleConfig pk $THIS_REPO_DIR/build/test-accumulator
```
