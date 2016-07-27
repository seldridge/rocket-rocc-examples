Collection of example libraries and test programs for the existing Rocket Custom Coprocessor (RoCC) accelerators for [Rocket Chip](https://github.com/ucb-bar/rocket-chip).

## Usage

Install the RISC-V toolchain and make sure that it's on your path. You need to build a patched Proxy Kernel that will set the `XS` bits to allow access to the "extension", i.e., some RoCC accelerator.

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
