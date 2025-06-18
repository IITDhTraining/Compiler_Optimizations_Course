# llvm-transformation-pass
Build:

    $ cd pass-plugin
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -fpass-plugin=`echo build/src/mypass.*` something.c
