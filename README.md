# Amigeconv
**Ami***ga* *Ima***ge** **Conv***erter*

A graphics converter for Amiga bitplanes & chunky format.

Developed by Daniel Gerdgren and distributed under the terms of the [MIT license](./LICENSE).

## Attention

**This tool is currently in beta develompment phase, input parameters will change!**

## Building

In a Unix-like environment simply `make` the binary.

## Usage

	amigeconv <options> <input> <output>

Available options are:

	-i, --interleaved                                Data in output file is
	                                                 stored in interleaved format.

	-d, --depth [1-8]                                Number of bitplanes saved
	                                                 in the output file, only valid
	                                                 for bitplanes & sprites.

	-c, --colors [1-256]                             Number of colors saved
	                                                 in the output file, only valid
	                                                 for palette.

	-f, --format [bitplanes|chunky|palette]          Desired output file format,
                                                     palette only supports pal8
                                                     at the moment.


Example:

	amigeconv -f bitplanes -d 8 font.png font.raw
	amigeconv -f chunky font.png font.chk
	amigeconv -f palette font.png font.pal8

## Planned features
* Sprites
* Palette

## Acknowledgments
Amigeconv uses the following libraries:

* [LodePNG](http://lodev.org/lodepng/) by Lode Vandevenne

Amigeconv is inspired by:

* [SuperFamiconv](https://github.com/Optiroc/SuperFamiconv) by David Lindecrantz
