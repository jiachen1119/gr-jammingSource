# gr-jammingSource

A gnuradio module for jamming signal generation.

The block is used to produce some kind of GNSS jamming source to test GNSS software receiver.

Based on the Gnuradio manual and ready-made C++ code by my fellow graduate brother Teng Hua, this block had been improved.

The block is for experimentation and belongs to **Southeast University** from Nanjing only.


## Requirements

This module is compatible with **gnuradio 3.10**.

Besides, C++ and gcc environment is required.

## Blocks

**TDMSingle**

A block that produce continuous wave (CW) jamming signal with TDM center frequency. 

***Data Type:*** gr-complex(complex in float)

#### ***Three parameters:***

- ***Sampling Rate:*** sampling rate. in Hz

- ***Frequencies:*** the center dopplers you want to jam around the center frequency of authentic signal. in Hz

- ***Period:*** the length of every loop. in seconds.

***

**AperiodicSpectrumMatched**

A block produce aperiodic spectrum matched jamming signals. This block produce sequence of -1 and 1.

#### ***Two parameters:***

- ***Sample Rate:*** sampling frequency

- ***Chip Rate:*** Chip rate

**known issue:** this block sometimes causes sudden exit with (code -11). This problem happens randomly. 
***
**Chirp**

This block generates chrip signals.

#### ***Four parameters:***

- ***Sample Rate:*** sampling frequency

- ***min frequency:*** the minimum frequency in the chirp

- ***max frequency:*** the maximum frequency in the chirp

- ***period:*** the length of one loop

## Install
This section describes how to install the OOT block of Gnuradio  in Linux.

### Build and install gr-jamming source

create the build folder:
```
$ mkdir build
```
Go to the build directory:

```
$ cd build
```

Configure and build the application:

```
$ cmake ..
$ make -j8
```

Different from general c++ program, gnuradio block must be installed into your system.
Do:
```
$ sudo make install
$ sudo ldconfig
```

**Notice:** If the yaml file is not configure correctly, the block cannot show in the interface of Gnuradio program.