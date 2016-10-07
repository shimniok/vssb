A Vehicle Speed Sensor Buffer (VSSB) for GM Throttle Body Injection (TBI) ECM on my 86 Jeep
Grand Wagoneer.

The Jeep GW uses a VSS for cruise control that outputs 8-pulse (8000 pulses/mile) sine wave
This circuit and firmware convert the OEM VSS signal to a 2-pulse square wave 5V signal
compatible with the GM TBI ECM ('7747) that I'm using.

It also outputs a 4-pulse signal which would be used (I think) by electronic GM speedos. 
The GW speedo, of course, is mechanical.

So what's the advantage of having a working speed sensor? At least a couple of TBI features
are enabled. The ECM is able to distinguish between idle mode (vehicle speed < 4mph) and
throttle-off coasting.  Additionally, Deceleration Fuel Cut-Off (DCFO) mode is enabled in
part based on speed.  And, if enabled, lean highway cruise is based on speed as well.

