# All Pair Short Path Algorithm Comparison
Compare the performance of shortest path algorithms below.
- SPFA
- Dijstra with priority queue
- Dijstra Dial implementation
- PAPE (Bellman Ford with dequeue)
- Graphical Floyd Warshall
- Algebracial Floyd Warshall

# USAGE
### build
```
make
```

### run
```
./bin/SPSPComparison.out "sp file" [iteration number]
```

- sp file: Path of input sp file
- iteration number: Iteration to run these algorithm. The result will be averaged.

### generate test case
```
make gen
```
Generate 32 sample test case in input/test_case/

### test all case 
```
make run_all_test_case
```
Test all the case in input/test_case/

# AUTHORS
[Lee-W](https://github.com/Lee-W/)

# LICENSE
MIT

