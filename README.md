# FESControl
## Requirements and installation
We recommend installing it with the script `installSinergiaPackages` located in https://github.com/millanlaboratory/launcherscripts. If you want to install this module independently, please follow these instructions.

Required packages:
* cnbiloop
* jsoncpp
* feslanguage
* cnbicore
* tobiid
* python2.7
* lcov
* gcov

To install the module:
```shell
cmake .
make -j 4
sudo make install
```

## How to use it
The system works in two ways. You can either start it to test a stimulation pattern or as an independent application.
To test a stimulation pattern:
```shell
fesControl -t /path/to/stimulationPatternFiles
```
The stimulation pattern file should be written in JSON and should follow this format:

## Modify and Test
To modify this module, create a new branch on your computer (locally). Edit the code as you want but make sure to test it with unit tests. Make sure that your modificiations are not breaking previous features. To do so, follow these steps.

```shell
cmake -DCMAKE_BUILD_TYPE=Coverage .
make -j 4
./build/testfesjson
lcov --capture --directory CMakeFiles/fescontrol.dir/ --output-file coverage.info
genhtml coverage.info --output-directory out
```
To visualize the report, go to the directory `out` and then open `index.html` with your preferred web-browser. You will be able to see where are the lines of code that are or not tested by your unit tests.
