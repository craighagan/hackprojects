# HDM Z2 Auto

I like to hike and camp, but have sleep apnea. Since I find I'm much better if I get a full night's sleep, I purchased a system that I could travel with and use a standard phone power bank to run. I'm fortunate in that my settings are only about 5mmHg, so I don't use that much power.

My machine is an [HDM Z2 Auto](https://breas.us/products/cpaps-for-travel/z2-auto/),
I've made two power cables for it. I've used multiple power banks with it:
1. A 97Wh (20,000mAh) battery pack (omni20+) is about 40% used after an 7.5hr night
1. A 114Wh (30,000mAh) Baseus battery pack](https://www.amazon.com/gp/product/B08JV4W4NY), it uses about 25% per night (7.5hrs) with my settings
1. A 297Wh (80000mAh) EnginStar Portable Power Station https://www.amazon.com/gp/product/B07WQN41V9 with a [65w car USB-C adapter](https://www.amazon.com/gp/product/B08QZ7RTSW)

My favorite is the omnicharge 20+, but that is big for backpacking, the other  "cheapo generic" with more actual capacity that I use. A catch is that it can't run cpap and charge phone at the same time due to how it regulates power.

The EnginStar and the OmniCharge can both hook up to a solar cell for recharging. The Omnicharge can't provide USB-C power while charging via solar (it can provide USB-A)

### Picture of My Kit, 9v Battery for Scale
![Picture of my kit](images/cpap-image.png "Picture of my kit, 9v battery is for scale")


## Trigger Cable Option (Easiest)

A USB-C Trigger table connects and produces a fixed, preset voltage if the USB-C charger can supply the requested voltage. This is the easiest way to run an HDM Z2 from a phone power pack.

If you use a USB trigger cable make *_SURE_* you get a 15v part and check the specs on your power bank. I tested with a multimeter, and a PD power brick good for 45+w which support 15v output (most that do 20v will do 15v).  That isn't a big deal to me. As with everything, you're not using your CPAP with the expected cables/power, so caveat emptor; be careful, check your final power and polarity many times.

## USB-A Cable with Voltage Regulator (Most Powerbank Choices)

An alternative path, which requires some soldering, is to sacrifice a USB cable, and connect the 5v (red) and Ground (black) cable to the input side of a  [Polulu 15v regulator](https://www.pololu.com/product/2896). Connect the output side to a 5.5mm x 2.1mm barrel connector. Make sure the 15v is connected to the center, and the ground to the outside. Validate that it is center positive and is 15v with a multimeter.

I started building this because my USB-C cable didn't sit as tight as a USB-A cable does, and I wanted to have some choices for power banks.

The advantage of this cable is that nearly any USB power bank will work, depending upon your settings. With my settings, the draw is about 0.9-1.2amps (4-6w), but spikes to a touch over 2.5amps when starting up. Many power banks provide up to 2.4amps (12w), and some support quite a bit more (e.g. my Baseus will provide over 3amps, as did an old Anker that I tried).

If your power bank can't handle the device, you'll usually find out as soon as you start breathing, the Z2 will power off when it can't draw enough power.

Note: the cable is not Quick-Charge compatible, some QC ports won't give you more than an amp without talking quickcharge.

### Picture of the finished cable.
![Picture of the finished cable.](images/cpap-usb-a-cable.jpg "Picture of the finished cable.")

