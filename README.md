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

## Dependencies

Need the correct radioberry device driver.



https://www.youtube.com/watch?v=ds-n-7sHXl8&t=2s
