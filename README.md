# soundcplay
Play SNG(YM) file in Raspberry Pi using SoundCortex

This program can play SNG(converted YM) file on SoundCortex using Raspberry Pi
https://github.com/toyoshim/SoundCortex
Please connect with I2C
if you using LPC812, sometime SoundCortex will disappear in i2cdetect
if it happened, pull up Pin 4(SCK) while power on

How to generate SNG file from YM file?
use this ...
https://github.com/internalregister/AY-3-8910/blob/master/ymConverter.py

How to Convert AY/PT3/Other format to YM?
use AYEmul

Also, It has PSG-SCC Register redirection function...
set mode to 1 will enable
