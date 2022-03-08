# Power Cable Options for running the HDM Z2 Auto from a powerbank

## 15V Trigger Cable  (easiest)

| :warning: WARNING: making mistakes, wrong, or faulty parts could damage your CPAP machine! |
| --- |

A USB-C Trigger table connects and produces a fixed, preset voltage if the USB-C charger can supply the requested voltage. This is the easiest way to run an HDM Z2 from a phone power pack, and what I use most often. I've also found that with my power banks, this cable tends to provide the most power the most quickly, so my CPAP has a touch more airflow using this cable than the other options (this may be in my head, so...).

If you use a USB trigger cable make *_SURE_* you get a 15v part and check the specs on your power bank. I tested with a multimeter, and a PD power brick good for 45+w which support 15v output (most that do 20v will do 15v).  That isn't a big deal to me. As with everything, you're not using your CPAP with the expected cables/power, so caveat emptor; be careful, check your final power and polarity many times.

I first made my own cable, then bought [this one](https://www.amazon.com/gp/product/B08NTTK8S9) If you buy the premade, make _SURE_ to test it with a multimeter in case you accidentally received the wrong part.

## 12v USB-C Cable with 15V Voltage Regulator (More Powerbank Choices)

| :warning: WARNING: making mistakes, wrong, or faulty parts could damage your CPAP machine! |
| --- |

I build this cable to work with a few extra phone power banks to give me more options, and to try things out since I had extra parts. It works, but I've found that most power banks which can handle 12v with enough amps to run the Z2 usually can also provide 15v, which is a touch more efficient since there isn't an extra voltage conversion.

(2020) Many phones/power banks only provide power for quick charging phones like pixels/iphones which charge at 18w requesting 12v @ 1.5amps from the USB-C source. These power banks and chargers do not supply the 15v required for the above cable. By adding a [voltage regulator](https://www.pololu.com/product/2896), you can use a 12v trigger cable and still supply 15v to the device. 18w should supply enough power to run the Z2 at nearly all pressures.

Note: I've found at least one power brick which supports 18w/12v PD and quickcharges my phone, but seems to have trouble with the sudden power surge to start the motor.

### Parts

To build, get the following:
1. 12v Trigger cable to 5.5 x 2.1mm barrell connector](https://www.amazon.com/gp/product/B08NTVLZH7)
1. 15v Polulu voltage regulator](https://www.pololu.com/product/2896)

### Building
1. Cut the cable about midway through, strip the wires on both sides
1. Tin the tips of the wires
1. Solder the wires into the voltage regulator.
   1. Red on USB-C side to VIN, black to GND
   1. Red on barrel connector to VOUT, black to GND
1. Make a box, or otherwise secure the voltage regulator
1. Plug into a power bank and test with a multimeter, ensure that the device is 15v, center positive

Note: the HDM Z2 will power up with a 12v supply, it will not be able to run the motor, and should power back down. If you have the HDM battery pack, that charges from 12v, which is why you can find 12v car plugs for the HDM Z2, but they're unable to run the device. You can use the same technique here on the car cable to run your Z2 from a car adaptor. Being that I charge my phone from my car, I don't see the point of making a second cable.

## USB-A Cable with Voltage Regulator (Most Powerbank Choices)

| :warning: WARNING: making mistakes, wrong, or faulty parts could damage your CPAP machine! |
| --- |

An alternative path, which requires some soldering, is to sacrifice a USB cable, and connect the 5v (red) and Ground (black) cable to the input side of a  [Polulu 15v regulator](https://www.pololu.com/product/2896). Connect the output side to a [5.5mm x 2.1mm barrel connector](https://www.amazon.com/gp/product/B083J24LTZ). Make sure the 15v is connected to the center, and the ground to the outside. Validate that it is center positive and is 15v with a multimeter.

I started building this because my USB-C cable didn't sit as tight on my backpacking powerbank a USB-A cable does, and I wanted to have some choices for power banks. In addition my Baseus power bank doesn't like providing multiple voltages -- if I plug something into a 5v port, the USB-C port drops to 5v. By using this cable, I can charge my phone and run my CPAP.

The advantage of this cable is that nearly any USB power bank will work, depending upon your settings. With my settings, the draw is about 0.9-1.2amps (4-6w), but spikes to a touch over 2.5amps when starting up. Many power banks provide up to 2.4amps (12w), and some support quite a bit more (e.g. my Baseus will provide over 3amps, as did an old Anker that I tried).

If your power bank can't handle the device, you'll usually find out as soon as you start breathing, the Z2 will power off when it can't draw enough power.

Note: the cable is not Quick-Charge compatible, some QC ports won't give you more than an amp (5w) without talking quickcharge.


To build, get the following:
1. USB A Serial Cable, any should do, end doesn't matter. I'd suggest using a good one.
1. [5.5mm x 2.1mm male barrel connector](https://www.amazon.com/gp/product/B083J24LTZ)
1. [15v Polulu voltage regulator](https://www.pololu.com/product/2896)

### Building
1. Cut the cable about midway through, and cut the non-USB-A tip off
1. Strip cable exposing wires.
1. If data lines are present (not red/black), cut them, you don't need them
1. You should now have two cables:
   1. USB-A to wire
   1. wire to wire
1. Strip and tight twist all wire ends
1. Tin the tips of the wires
1. Solder one end of the wire to wire cable to the 5.5x2.1mm barrel
   1. Red to center
   1. Black to outside
1. Solder the wires cables to the voltage regulator
   1. Red on USB-A side to VIN, black to GND
   1. Red on barrel connector to VOUT, black to GND
1. Make a box, or otherwise secure the voltage regulator
1. Plug into a power bank and test with a multi-meter, ensure that the device is producing 15v, center positive from the barrel connector.


### Picture of the finished cable.
![Picture of the finished cable without my plastic box so you can see the wires.](images/cpap-usb-a-cable.jpg "Picture of the finished cable.")