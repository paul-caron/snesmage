In progress, currently works to output 16x16 but will make that size a variable option soon.

# Snes Mage
Converts any images into series of sprites (as grayscale, 4 bitplanes) for the SNES (super nintendo)

## Requirements
This program need imagemagick with Magick++ C++ API. So install imagemagick any way you like. Then try use the makefile included in the repo with the "make" command and maybe it is going to work for you too.

## How to use
From the command line:
```
./snesmage myimage.jpg.png.gif.bmp
```
Then you should have a binary file appear in the folder. That file can then be put into an assembly program as pure data for making sprites : assuming you are using a "grayscale" palette to go along with it. I include in this repo a red-grayscale palette which should work also.
