# licm module pass
- `make build` builds the pass plugin `LICMPass.so`. This is loaded into the pass pipeline using `opt` and  is used for transforming (i.e. performing LICM) on a test program `licm.c` in the `test` directory. 

- `make run` loads the pass plugin and runs the transformation on a default program, `licm.c`, in the `test` directory