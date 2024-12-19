# Bmp2JascPal
<img src="https://github.com/RezWaki/Bmp2JascPal/blob/main/logo.png" width=256 height=256>

Use it to convert an image to a JASC 256-color palette.
You can feed it all common image formats:
	bitmap, png, gif, jpeg, etc

The image you supply has to be 16x16 and be pixel-precise.
So I would advise against using anything other than bitmap/png for best accuracy.
Each pixel is taken as an individual color for the palette.
The color layout of the palette-sketch will be preserved.

Run it with the win cmd:
bmp2jascpal -in \<input\> -out \<output\>
where input is the input palette-sketch image & output is the .pal file that will be generated.
