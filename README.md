# SoapyRadioberry
SoapyRadioberry driver, this repo is an effort to extend the SoapyRadioberry driver of Johan PA0GSB.
I use the pluto SDR driver as an example, goal is to use this driver in my sdrberry project and be able to have 
both Adalm pluto and Radioberry connected to a raspberry pi to create a tranceiver. 


This source code is still in development.  

To install you need to configure rasberry pi OS in text only mode, (switch of the GUI)
Compiled using VisualGDB

ToDo:
- Test transmittion with update of radioberry gateware

Done:
- Bug fix for dev version of Radioberry
- added multiple samplerates
- Transmitter part


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
```

## Dependencies

Need the radioberry device driver.

https://www.youtube.com/watch?v=ds-n-7sHXl8&t=2s
