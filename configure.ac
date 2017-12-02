AC_INIT([rocket-rocc-examples], [0.1], [schuyler.eldridge@gmail.com])

cross_compiling=yes
AC_PROG_CC

AC_ARG_WITH(xlen,
        [AS_HELP_STRING([--with-xlen=XLEN],
                [Set XLEN, the X-register bit width (default is 64)])],
        AC_SUBST(XLEN, $withval),
        AC_SUBST(XLEN, 64)
        )

AC_ARG_WITH(riscvtools,
        [AS_HELP_STRING([--with-riscvtools=RISCVTOOLS],
                [Set the path to an instanllation of riscv-tools])],
        AC_SUBST(RISCVTOOLS, $withval),
        AC_MSG_ERROR("You must specify a path to a riscv-tools repo (--with-riscvtools)", 1)
        )

AC_OUTPUT(
  Makefile
)
