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
To run as an independent application you need to specify the movement authorizer file that associates event ID to movements:
```shell
fesControl -f /path/to/authorizerFile
```
Usage: fesControl [OPTION]
* -d       display information: verbose, gui or silent (default)
* -f       movement authorizer file in .json (resources/AuthorizedMovements.json default)
* -t       test movement file in .json 
* -n       iD bus name for event receiver (/dev default)
* -h       display this help and exit
```shell
fesControl -d verbose -n /dev -f $movements
```
 
## Stimulation pattern file
The stimulation pattern file should be written in JSON. You need to specify the frequency of stimulation and a sequence of stimulations for a specific channel. Mandatory fields for a stimulation are:
* `actionType` which can be either `setter` or `limited`
* `channel` a integer representing which channel to apply the stimulation on from 1 to 8
* `current` a float in mA
* `pulseWidth` a float in ms

Optional fields can be added:
* `delay` which is the delay before stimulation starts in seconds
* `name` a string that describes the stimulation action

### Setter
Here is an example of simple setter stimulation. It will stimulate on channel 1 with a current of 4 mA and a pulse width o 500 us immediately after sending the command.

```json
{
    "frequency": 35,
    "sequence": [
        {
            "name": "sensory",
            "actionType": "setter",
            "delay": 0,
            "channel": 1,
            "current": 4.0,
            "pulseWidth": 0.5
        }
    ]
}
```
Here is the same stimulation but on two channels:
```json
{
    "frequency": 35,
    "sequence": [
        {
            "actionType": "setter",
            "channel": 1,
            "current": 4.0,
            "pulseWidth": 1.0
        },
        {
            "actionType": "setter",
            "channel": 2,
            "current": 4.0,
            "pulseWidth": 1.0
        }
    ]
}
```

### Limited
Stimulation can be also limited in time by setting the keyword `limited` to the `actionType` field. It is then possible to set up a ramp of stimulation up and down. The following example show how to generate a stimulation on two channels with a linear increment on channel 1 from 0 to 10 mA in 2 s. It stays then at the maximum value for 1 s and then decreases from 10 to 0 mA in 1.5 s. The same stimulation pattern will occur on channel 2 with a delay of 500 ms to a maximum current of 25 mA.

```json
{
    "frequency": 35,
    "sequence": [
        {
            "name": "shoulder_flexion",
            "actionType": "limited",
            "delay": 0,
            "duration": 4500,
            "channel": 1,
            "currentIncrementMode": "linear",
            "pulseWidthIncrementMode": "linear",
            "currentIncrementerParameters": [
                0,
                10.0,
                2000
            ],
            "pulseWidthIncrementerParameters": [
                0,
                1,
                0
            ],
            "currentDecrementMode": "linear",
            "pulseWidthDecrementMode": "linear",
            "currentDecrementerParameters": [
                0,
                10.0,
                1500
            ],
            "pulseWidthDecrementerParameters": [
                0,
                1,
                0
            ]
        },
        {
            "name": "extension_wrist",
            "actionType": "limited",
            "delay": 500,
            "duration": 4500,
            "channel": 2,
            "currentIncrementMode": "linear",
            "pulseWidthIncrementMode": "linear",
            "currentIncrementerParameters": [
                0,
                25.0,
                2000
            ],
            "pulseWidthIncrementerParameters": [
                0,
                1,
                0
            ],
            "currentDecrementMode": "linear",
            "pulseWidthDecrementMode": "linear",
            "currentDecrementerParameters": [
                0,
                25.0,
                1500
            ],
            "pulseWidthDecrementerParameters": [
                0,
                1,
                0
            ]
        }
    ]
}
```
## Authorizer file
For each stimulation pattern, an event ID listened on the bus specified by parameter will be associated. Every time the event ID appears, it will trigger the stimulation pattern.

```json
{
	"Movements" : [
		{
			"Name" : "flexion",
			"EventId" : 1000,
			"MovementFile" : "/path/to/stimulationPattern.json"
		},
		{
			"Name" : "reaching",
			"EventId" : 1001,
			"MovementFile" : "/path/to/stimulationPattern1.json"
		},
		{
			"Name" : "lowstimSingle",
			"EventId" : 14,
			"MovementFile" : "/path/to/stimulationPattern2.json"
		},
		{
			"Name" : "lowstimDouble",
			"EventId" : 13,
			"MovementFile" : "/path/to/stimulationPattern3.json"
		},
		{
			"Name" : "reset",
			"EventId" : 15,
			"MovementFile" : "/path/to/stimulationPattern4.json"
		}
	]
}

```

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

## Known bugs
Using the module with a gui display might generate unexpected interruption. It is recommended to use the module with verbose or silent options.
