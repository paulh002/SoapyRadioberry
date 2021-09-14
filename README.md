# SoapyRadioberry
SoapyRadioberry driver, this repo is an effort to extend the SoapyRadioberry driver of Johan PA0GSB.
I use the pluto SDR driver as an example, goal is to use this driver in my sdrberry project and be able to have 
both Adalm pluto and Radioberry connected to a raspberry pi to create a tranceiver. 
Currently the supported radioberry gateware is included in this repository, to make sure the right supported version is used.
This is a customized version from the dev branch of Johan PA0GSB


This source code is still in development.  

To install you need to configure rasberry pi OS in text only mode, (switch of the GUI)
Compiled using VisualGDB

ToDo:
- Test transmittion with update of radioberry gateware
- Align with latest radioberry gateware version 

Done:
- Bug fix for dev version of Radioberry
- added multiple samplerates
- Transmitter part
- Support for CF32 and CS16

Installation of libraries is necessary:
- SoapySDR


## Installation instructions

```
git clone <>
cd <sub folder>
mkdir build
cd build
cmake ..
make -j4
sudo make install

To install correct radioberry drivers for this SoapySDR library:
cd <sub folder>
cd radioberry
./install.sh
```

## Dependencies

Need the correct radioberry device driver.



![sdrberry](https://github.com/paulh002/sdrberry/blob/master/IMG_20210909_183113.jpg)

[![Radioberry demo](https://img.youtube.com/vi/BMJiv3YGv-k/0.jpg)](https://youtu.be/PQ_Np5SfcxA)
