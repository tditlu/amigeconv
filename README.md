# Amigeconv
`Ami`ga Ima`ge` `Conv`erter

Developed by Daniel Gerdgren and distributed under the terms of the [MIT license](./LICENSE).


## Building

In a Unix-like environment simply `make` the binary.

## Usage

	amigeconv <options> <input> <output>

Available options are:
	-i, --interleaved                  Data in output file is stored
	                                   in interleaved format.

	-d, --depth [1-8]                  Number of bitplanes to be saved
	                                   in output file, only valid for
	                                   bitplanes & sprites format.

	-f, --format [bitplanes|chunky]    Desired output file format.

Example:

	amigeconv -f bitplanes -d 8 font.png font.raw

## Planned features
* Sprites
* Palette

## Acknowledgments
Amigeconv uses the following libraries:

* [LodePNG](http://lodev.org/lodepng/) by Lode Vandevenne

Amigeconv is inspired by:

* [SuperFamiconv](https://github.com/Optiroc/SuperFamiconv) by David Lindecrantz
