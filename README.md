# soundcplay
Play SNG(YM) file in Raspberry Pi using SoundCortex<br>
<br>
This program can play SNG(converted YM) file on SoundCortex using Raspberry Pi<br>
compile with "gcc soundcplay.c"<br>
https://github.com/toyoshim/SoundCortex<br>
Please connect with I2C<br>
if you using LPC812, sometime SoundCortex will disappear in i2cdetect<br>
if it happened, pull up Pin 04(SCK) while power on<br>
<br>
<br>
Wiring in LPC812<br>
RPi Pin01(3v3) 03(SDA) 05(SCL) 06(GND)<br>
to<br>
LPC Pin15(3v3) 19(SDA) 04(SCL) 16(GND) and 5(SoundOut, connect 3k3 and 10uf)<br>
<br>
How to generate SNG file from YM file?<br>
use this ...<br>
https://github.com/internalregister/AY-3-8910/blob/master/ymConverter.py<br>
<br>
How to Convert AY/PT3/Other format to YM?<br>
use AYEmul<br>
<br>
Also, It has PSG-SCC Register redirection feature...<br>
set mode 1 will enable<br>
<br>
Problem: Timing is very inaccurate, PSGSCC has no noise, PSGSCC has freq limit(narrower than AY?)<br>
         Also SoundCortex doesn't support Envelope, so Lot of YM will sound quirk
