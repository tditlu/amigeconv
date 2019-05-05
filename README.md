# Amigeconv
**Ami**_ga_ _Ima_**ge** **Conv**_erter_ by Todi / Tulou.

A graphics converter for different Amiga bitplanes, chunky & palette formats.

Developed and distributed under the terms of the [MIT license](./LICENSE).

## Building

In a Unix-like environment simply `make` the binary.

## Usage

	amigeconv <options> <input> <output>

Available options are:

	-f, --format [bitplane|chunky|palette|sprite]         Desired output file format.

	-p, --palette [pal8|pal4|pal32|loadrgb4|loadrgb32]    Desired palette file format.

	-l, --interleaved                                     Data in output file is stored in interleaved format, only valid for bitplane.

	-d, --depth [1-8]                                     Number of bitplane saved in the output file, only valid for bitplane & sprite.

	-c, --colors [1-256]                                  Number of colors saved in the output file, only valid for palette.

	-x, --copper                                          Generate copper list, only valid for palette.

	-w, --width [16|32|64]                                Width, only valid for sprite.

	-t, --controlword                                     Write control word, only valid for sprite.

	-a, --attached                                        Attach sprites, only valid for sprite.

Examples:

	amigeconv -f bitplanes -d 8 font.png font.raw
	amigeconv -f chunky font.png font.chk
	amigeconv -f palette -p pal8 font.png font.pal8
	amigeconv -f sprite -t font.png font.spr

## Acknowledgments
Amigeconv uses the following libraries:

* [LodePNG](http://lodev.org/lodepng/) by Lode Vandevenne

Amigeconv is inspired by:

* [SuperFamiconv](https://github.com/Optiroc/SuperFamiconv) by David Lindecrantz
