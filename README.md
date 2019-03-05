# FESControl

## Modify and Test
To modify this module, create a new branch on your computer (locally). Edit the code as you want but make sure to test it with unit tests. Make sure that your modificiations are not breaking previous features. To do so, follow these steps.

```cpp
cmake -DCMAKE_BUILD_TYPE=Coverage .
make -j 4
./build/testfesjson
lcov --capture --directory CMakeFiles/fescontrol.dir/ --output-file coverage.info
genhtml coverage.info --output-directory out
```
To visualize the report, go to the directory `out` and then open `index.html` with your preferred web-browser. You will be able to see where are the lines of code that are or not tested by your unit tests.
