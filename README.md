# soundcplay
Play SNG(YM) file in Raspberry Pi using SoundCortex<br>
<br>
This program can play SNG(converted YM) file on SoundCortex using Raspberry Pi<br>
compile with "gcc soundcplay.c"
https://github.com/toyoshim/SoundCortex<br>
Please connect with I2C<br>
if you using LPC812, sometime SoundCortex will disappear in i2cdetect<br>
if it happened, pull up Pin 4(SCK) while power on<br>
<br>
How to generate SNG file from YM file?<br>
use this ...<br>
https://github.com/internalregister/AY-3-8910/blob/master/ymConverter.py<br>
<br>
How to Convert AY/PT3/Other format to YM?<br>
use AYEmul<br>

Also, It has PSG-SCC Register redirection feature...<br>
set mode 1 will enable<br>
