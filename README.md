# Summary

* This is a simple matrix multiplication
* Use the ARM neon SIMD instrinsics
* Understand the impact of pipeline flush`


# Build
* `$ make`

# Result
```
// pipeline flush
output:  6248098.000000
spend:  61549 us

// pipeline w/o flush
output:  6248098.000000
spend:  15326 us
```

# License
`NCTU_embedded_pipeline-flush` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found
in the `LICENSE` file.
