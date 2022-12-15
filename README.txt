

This is release 1.2 of the toolchain source and binaries for bcm63xx Linux

It is required to compile all releases from 4.14 and beyond.

The complete source is contained in
crosstools-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-sources.tar.bz2
and this file should be posted along with binaries whenever the binaries
are distributed.  There will be no independent source and binary releases
provided.


The three files
crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21.Rel1.2.tar.bz2-NPTL
crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21.Rel1.2.tar.bz2
crosstools-mipsel-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21.Rel1.2.tar.bz2
contain the toolchain for the ARM and MIPS CPUs.  They must be installed
at the /opt/toolchains/...  location specified in the files.

To install....

Be sure that /opt/toolchains/ is writeable by you (or you are root)
remove or move aside any previous
  /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/
or
  /opt/toolchains/crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21/
  /opt/toolchains/crosstools-mipsel-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21/

Then...
cd /
tar xjf crosstools-mips-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21.Rel1.2.tar.bz2
tar xjf crosstools-mipsel-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21.Rel1.2.tar.bz2
tar xjf crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21.Rel1.2.tar.bz2


Changes:
====================
1.2
====================
   Changed pthreads library to use the "NPTL" for ARM.  This includes a 
change to the install location 
  /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/
  instead of 
  /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21/
   so both versions can coexist on a build server.


   GCC fix (http://gcc.gnu.org/bugzilla/show_bug.cgi?id=48308) to permit 
OpenSSL to compile properly.

   Added UCLIBC_BSD_SPECIFIC and UCLIBC_NTP_LEGACY functionality

   Backported SFD_CLOEXEC fixes from uClibc 0.9.33


====================
1.1
====================
   Added support for MIPSEL

