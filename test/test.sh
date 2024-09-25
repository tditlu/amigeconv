#!/bin/bash
test () {
	if diff $1 $2 > /dev/null 2>&1
	then
		printf "\033[0;32mResult:\033[0m Binary files $1 and $2 is the same\n\n"
	else
		printf "\033[0;31mError:\033[0m Binary files $1 and $2 differ\n\n"
		exit 1
	fi
}

cd ..
make clean
make
cd test/

printf "\033[0;33mCommand:\033[0m amigeconv -f chunky data/random8.png output/amigeconv/random8.chk\n"
../bin/amigeconv -f chunky data/random8.png output/amigeconv/random8.chk
test output/amigeconv/random8.chk data/piccon/random8.chk

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -m -d 8 data/random8.png output/amigeconv/random8_mask.raw\n"
../bin/amigeconv -f bitplane -m -d 8 data/random8.png output/amigeconv/random8_mask.raw
test output/amigeconv/random8_mask.raw data/piccon/random8_mask.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -m inverted -d 8 data/random8.png output/amigeconv/random8_mask_inv.raw\n"
../bin/amigeconv -f bitplane -m inverted -d 8 data/random8.png output/amigeconv/random8_mask_inv.raw
test output/amigeconv/random8_mask_inv.raw data/piccon/random8_mask_inv.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -m -d 8 data/random8.png output/amigeconv/random8_mask_i.raw\n"
../bin/amigeconv -l -f bitplane -m -d 8 data/random8.png output/amigeconv/random8_mask_i.raw
test output/amigeconv/random8_mask_i.raw data/piccon/random8_mask_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -m inverted -d 8 data/random8.png output/amigeconv/random8_mask_inv_i.raw\n"
../bin/amigeconv -l -f bitplane -m inverted -d 8 data/random8.png output/amigeconv/random8_mask_inv_i.raw
test output/amigeconv/random8_mask_inv_i.raw data/piccon/random8_mask_inv_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 8 data/random8.png output/amigeconv/random8.raw\n"
../bin/amigeconv -f bitplane -d 8 data/random8.png output/amigeconv/random8.raw
test output/amigeconv/random8.raw data/piccon/random8.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 8 data/random8.png output/amigeconv/random8_i.raw\n"
../bin/amigeconv -l -f bitplane -d 8 data/random8.png output/amigeconv/random8_i.raw
test output/amigeconv/random8_i.raw data/piccon/random8_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 7 data/random7.png output/amigeconv/random7.raw\n"
../bin/amigeconv -f bitplane -d 7 data/random7.png output/amigeconv/random7.raw
test output/amigeconv/random7.raw data/piccon/random7.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 7 data/random7.png output/amigeconv/random7_i.raw\n"
../bin/amigeconv -l -f bitplane -d 7 data/random7.png output/amigeconv/random7_i.raw
test output/amigeconv/random7_i.raw data/piccon/random7_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 6 data/random6.png output/amigeconv/random6.raw\n"
../bin/amigeconv -f bitplane -d 6 data/random6.png output/amigeconv/random6.raw
test output/amigeconv/random6.raw data/piccon/random6.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 6 data/random6.png output/amigeconv/random6_i.raw\n"
../bin/amigeconv -l -f bitplane -d 6 data/random6.png output/amigeconv/random6_i.raw
test output/amigeconv/random6_i.raw data/piccon/random6_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 5 data/random5.png output/amigeconv/random5.raw\n"
../bin/amigeconv -f bitplane -d 5 data/random5.png output/amigeconv/random5.raw
test output/amigeconv/random5.raw data/piccon/random5.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 5 data/random5.png output/amigeconv/random5_i.raw\n"
../bin/amigeconv -l -f bitplane -d 5 data/random5.png output/amigeconv/random5_i.raw
test output/amigeconv/random5_i.raw data/piccon/random5_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 4 data/random4.png output/amigeconv/random4.raw\n"
../bin/amigeconv -f bitplane -d 4 data/random4.png output/amigeconv/random4.raw
test output/amigeconv/random4.raw data/piccon/random4.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 4 data/random4.png output/amigeconv/random4_i.raw\n"
../bin/amigeconv -l -f bitplane -d 4 data/random4.png output/amigeconv/random4_i.raw
test output/amigeconv/random4_i.raw data/piccon/random4_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 3 data/random3.png output/amigeconv/random3.raw\n"
../bin/amigeconv -f bitplane -d 3 data/random3.png output/amigeconv/random3.raw
test output/amigeconv/random3.raw data/piccon/random3.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 3 data/random3.png output/amigeconv/random3_i.raw\n"
../bin/amigeconv -l -f bitplane -d 3 data/random3.png output/amigeconv/random3_i.raw
test output/amigeconv/random3_i.raw data/piccon/random3_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 2 data/random2.png output/amigeconv/random2.raw\n"
../bin/amigeconv -f bitplane -d 2 data/random2.png output/amigeconv/random2.raw
test output/amigeconv/random2.raw data/piccon/random2.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 2 data/random2.png output/amigeconv/random2_i.raw\n"
../bin/amigeconv -l -f bitplane -d 2 data/random2.png output/amigeconv/random2_i.raw
test output/amigeconv/random2_i.raw data/piccon/random2_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -f bitplane -d 1 data/random1.png output/amigeconv/random1.raw\n"
../bin/amigeconv -f bitplane -d 1 data/random1.png output/amigeconv/random1.raw
test output/amigeconv/random1.raw data/piccon/random1.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 1 data/random1.png output/amigeconv/random1_i.raw\n"
../bin/amigeconv -l -f bitplane -d 1 data/random1.png output/amigeconv/random1_i.raw
test output/amigeconv/random1_i.raw data/piccon/random1_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -l -f bitplane -d 1 data/random1.png output/amigeconv/random1_i.raw\n"
../bin/amigeconv -l -f bitplane -d 1 data/random1.png output/amigeconv/random1_i.raw
test output/amigeconv/random1_i.raw data/piccon/random1_i.raw

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random1.png output/amigeconv/random1.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random1.png output/amigeconv/random1.pal4
test output/amigeconv/random1.pal4 data/piccon/random1.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random1.png output/amigeconv/random1.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random1.png output/amigeconv/random1.pal4
test output/amigeconv/random1.pal4 data/piccon/random1.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random2.png output/amigeconv/random2.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random2.png output/amigeconv/random2.pal4
test output/amigeconv/random2.pal4 data/piccon/random2.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random3.png output/amigeconv/random3.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random3.png output/amigeconv/random3.pal4
test output/amigeconv/random3.pal4 data/piccon/random3.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random4.png output/amigeconv/random4.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random4.png output/amigeconv/random4.pal4
test output/amigeconv/random4.pal4 data/piccon/random4.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random5.png output/amigeconv/random5.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random5.png output/amigeconv/random5.pal4
test output/amigeconv/random5.pal4 data/piccon/random5.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random6.png output/amigeconv/random6.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random6.png output/amigeconv/random6.pal4
test output/amigeconv/random6.pal4 data/piccon/random6.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random7.png output/amigeconv/random7.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random7.png output/amigeconv/random7.pal4
test output/amigeconv/random7.pal4 data/piccon/random7.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 data/random8.png output/amigeconv/random8.pal4\n"
../bin/amigeconv -n -f palette -p pal4 data/random8.png output/amigeconv/random8.pal4
test output/amigeconv/random8.pal4 data/piccon/random8.pal4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 -x data/random1.png output/amigeconv/random1.pal4_copper\n"
../bin/amigeconv -n -f palette -p pal4 -x data/random1.png output/amigeconv/random1.pal4_copper
test output/amigeconv/random1.pal4_copper data/piccon/random1.pal4_copper

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 -x data/random1.png output/amigeconv/random1.pal4_copper\n"
../bin/amigeconv -n -f palette -p pal4 -x data/random1.png output/amigeconv/random1.pal4_copper
test output/amigeconv/random1.pal4_copper data/piccon/random1.pal4_copper

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 -x data/random2.png output/amigeconv/random2.pal4_copper\n"
../bin/amigeconv -n -f palette -p pal4 -x data/random2.png output/amigeconv/random2.pal4_copper
test output/amigeconv/random2.pal4_copper data/piccon/random2.pal4_copper

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 -x data/random3.png output/amigeconv/random3.pal4_copper\n"
../bin/amigeconv -n -f palette -p pal4 -x data/random3.png output/amigeconv/random3.pal4_copper
test output/amigeconv/random3.pal4_copper data/piccon/random3.pal4_copper

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 -x data/random4.png output/amigeconv/random4.pal4_copper\n"
../bin/amigeconv -n -f palette -p pal4 -x data/random4.png output/amigeconv/random4.pal4_copper
test output/amigeconv/random4.pal4_copper data/piccon/random4.pal4_copper

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p pal4 -x data/random5.png output/amigeconv/random5.pal4_copper\n"
../bin/amigeconv -n -f palette -p pal4 -x data/random5.png output/amigeconv/random5.pal4_copper
test output/amigeconv/random5.pal4_copper data/piccon/random5.pal4_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random2.png output/amigeconv/random2.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random2.png output/amigeconv/random2.pal8
test output/amigeconv/random2.pal8 data/piccon/random2.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random3.png output/amigeconv/random3.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random3.png output/amigeconv/random3.pal8
test output/amigeconv/random3.pal8 data/piccon/random3.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random4.png output/amigeconv/random4.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random4.png output/amigeconv/random4.pal8
test output/amigeconv/random4.pal8 data/piccon/random4.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random5.png output/amigeconv/random5.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random5.png output/amigeconv/random5.pal8
test output/amigeconv/random5.pal8 data/piccon/random5.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random6.png output/amigeconv/random6.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random6.png output/amigeconv/random6.pal8
test output/amigeconv/random6.pal8 data/piccon/random6.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random7.png output/amigeconv/random7.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random7.png output/amigeconv/random7.pal8
test output/amigeconv/random7.pal8 data/piccon/random7.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 data/random8.png output/amigeconv/random8.pal8\n"
../bin/amigeconv -f palette -p pal8 data/random8.png output/amigeconv/random8.pal8
test output/amigeconv/random8.pal8 data/piccon/random8.pal8

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random2.png output/amigeconv/random2.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random2.png output/amigeconv/random2.pal8_copper
test output/amigeconv/random2.pal8_copper data/piccon/random2.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random3.png output/amigeconv/random3.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random3.png output/amigeconv/random3.pal8_copper
test output/amigeconv/random3.pal8_copper data/piccon/random3.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random4.png output/amigeconv/random4.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random4.png output/amigeconv/random4.pal8_copper
test output/amigeconv/random4.pal8_copper data/piccon/random4.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random5.png output/amigeconv/random5.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random5.png output/amigeconv/random5.pal8_copper
test output/amigeconv/random5.pal8_copper data/piccon/random5.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random6.png output/amigeconv/random6.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random6.png output/amigeconv/random6.pal8_copper
test output/amigeconv/random6.pal8_copper data/piccon/random6.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random7.png output/amigeconv/random7.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random7.png output/amigeconv/random7.pal8_copper
test output/amigeconv/random7.pal8_copper data/piccon/random7.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal8 -x data/random8.png output/amigeconv/random8.pal8_copper\n"
../bin/amigeconv -f palette -p pal8 -x data/random8.png output/amigeconv/random8.pal8_copper
test output/amigeconv/random8.pal8_copper data/piccon/random8.pal8_copper

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random2.png output/amigeconv/random2.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random2.png output/amigeconv/random2.pal32
test output/amigeconv/random2.pal32 data/piccon/random2.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random3.png output/amigeconv/random3.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random3.png output/amigeconv/random3.pal32
test output/amigeconv/random3.pal32 data/piccon/random3.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random4.png output/amigeconv/random4.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random4.png output/amigeconv/random4.pal32
test output/amigeconv/random4.pal32 data/piccon/random4.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random5.png output/amigeconv/random5.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random5.png output/amigeconv/random5.pal32
test output/amigeconv/random5.pal32 data/piccon/random5.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random6.png output/amigeconv/random6.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random6.png output/amigeconv/random6.pal32
test output/amigeconv/random6.pal32 data/piccon/random6.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random7.png output/amigeconv/random7.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random7.png output/amigeconv/random7.pal32
test output/amigeconv/random7.pal32 data/piccon/random7.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p pal32 data/random8.png output/amigeconv/random8.pal32\n"
../bin/amigeconv -f palette -p pal32 data/random8.png output/amigeconv/random8.pal32
test output/amigeconv/random8.pal32 data/piccon/random8.pal32

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random1.png output/amigeconv/random1.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random1.png output/amigeconv/random1.loadrgb4
test output/amigeconv/random1.loadrgb4 data/piccon/random1.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random2.png output/amigeconv/random2.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random2.png output/amigeconv/random2.loadrgb4
test output/amigeconv/random2.loadrgb4 data/piccon/random2.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random3.png output/amigeconv/random3.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random3.png output/amigeconv/random3.loadrgb4
test output/amigeconv/random3.loadrgb4 data/piccon/random3.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random4.png output/amigeconv/random4.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random4.png output/amigeconv/random4.loadrgb4
test output/amigeconv/random4.loadrgb4 data/piccon/random4.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random5.png output/amigeconv/random5.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random5.png output/amigeconv/random5.loadrgb4
test output/amigeconv/random5.loadrgb4 data/piccon/random5.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random6.png output/amigeconv/random6.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random6.png output/amigeconv/random6.loadrgb4
test output/amigeconv/random6.loadrgb4 data/piccon/random6.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random7.png output/amigeconv/random7.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random7.png output/amigeconv/random7.loadrgb4
test output/amigeconv/random7.loadrgb4 data/piccon/random7.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -n -f palette -p loadrgb4 data/random8.png output/amigeconv/random8.loadrgb4\n"
../bin/amigeconv -n -f palette -p loadrgb4 data/random8.png output/amigeconv/random8.loadrgb4
test output/amigeconv/random8.loadrgb4 data/piccon/random8.loadrgb4

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random1.png output/amigeconv/random1.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random1.png output/amigeconv/random1.loadrgb32
test output/amigeconv/random1.loadrgb32 data/piccon/random1.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random1.png output/amigeconv/random1.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random1.png output/amigeconv/random1.loadrgb32
test output/amigeconv/random1.loadrgb32 data/piccon/random1.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random2.png output/amigeconv/random2.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random2.png output/amigeconv/random2.loadrgb32
test output/amigeconv/random2.loadrgb32 data/piccon/random2.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random3.png output/amigeconv/random3.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random3.png output/amigeconv/random3.loadrgb32
test output/amigeconv/random3.loadrgb32 data/piccon/random3.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random4.png output/amigeconv/random4.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random4.png output/amigeconv/random4.loadrgb32
test output/amigeconv/random4.loadrgb32 data/piccon/random4.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random5.png output/amigeconv/random5.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random5.png output/amigeconv/random5.loadrgb32
test output/amigeconv/random5.loadrgb32 data/piccon/random5.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random6.png output/amigeconv/random6.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random6.png output/amigeconv/random6.loadrgb32
test output/amigeconv/random6.loadrgb32 data/piccon/random6.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random7.png output/amigeconv/random7.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random7.png output/amigeconv/random7.loadrgb32
test output/amigeconv/random7.loadrgb32 data/piccon/random7.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f palette -p loadrgb32 data/random8.png output/amigeconv/random8.loadrgb32\n"
../bin/amigeconv -f palette -p loadrgb32 data/random8.png output/amigeconv/random8.loadrgb32
test output/amigeconv/random8.loadrgb32 data/piccon/random8.loadrgb32

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 16 data/random2.png output/amigeconv/random2_16.spr\n"
../bin/amigeconv -f sprite -w 16 data/random2.png output/amigeconv/random2_16.spr
test output/amigeconv/random2_16.spr data/piccon/random2_16.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 32 data/random2.png output/amigeconv/random2_32.spr\n"
../bin/amigeconv -f sprite -w 32 data/random2.png output/amigeconv/random2_32.spr
test output/amigeconv/random2_32.spr data/piccon/random2_32.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 64 data/random2.png output/amigeconv/random2_64.spr\n"
../bin/amigeconv -f sprite -w 64 data/random2.png output/amigeconv/random2_64.spr
test output/amigeconv/random2_64.spr data/piccon/random2_64.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 16 -t data/random2.png output/amigeconv/random2_16_c.spr\n"
../bin/amigeconv -f sprite -w 16 -t data/random2.png output/amigeconv/random2_16_c.spr
test output/amigeconv/random2_16_c.spr data/piccon/random2_16_c.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 32 -t data/random2.png output/amigeconv/random2_32_c.spr\n"
../bin/amigeconv -f sprite -w 32 -t data/random2.png output/amigeconv/random2_32_c.spr
test output/amigeconv/random2_32_c.spr data/piccon/random2_32_c.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 64 -t data/random2.png output/amigeconv/random2_64_c.spr\n"
../bin/amigeconv -f sprite -w 64 -t data/random2.png output/amigeconv/random2_64_c.spr
test output/amigeconv/random2_64_c.spr data/piccon/random2_64_c.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 16 -a data/random4.png output/amigeconv/random4_16_a.spr\n"
../bin/amigeconv -f sprite -w 16 -a data/random4.png output/amigeconv/random4_16_a.spr
test output/amigeconv/random4_16_a.spr data/piccon/random4_16_a.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 32 -a data/random4.png output/amigeconv/random4_32_a.spr\n"
../bin/amigeconv -f sprite -w 32 -a data/random4.png output/amigeconv/random4_32_a.spr
test output/amigeconv/random4_32_a.spr data/piccon/random4_32_a.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 64 -a data/random4.png output/amigeconv/random4_64_a.spr\n"
../bin/amigeconv -f sprite -w 64 -a data/random4.png output/amigeconv/random4_64_a.spr
test output/amigeconv/random4_64_a.spr data/piccon/random4_64_a.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 16 -t -a data/random4.png output/amigeconv/random4_16_a_c.spr\n"
../bin/amigeconv -f sprite -w 16 -t -a data/random4.png output/amigeconv/random4_16_a_c.spr
test output/amigeconv/random4_16_a_c.spr data/piccon/random4_16_a_c.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 32 -t -a data/random4.png output/amigeconv/random4_32_a_c.spr\n"
../bin/amigeconv -f sprite -w 32 -t -a data/random4.png output/amigeconv/random4_32_a_c.spr
test output/amigeconv/random4_32_a_c.spr data/piccon/random4_32_a_c.spr

printf "\033[0;33mCommand:\033[0m amigeconv -f sprite -w 64 -t -a data/random4.png output/amigeconv/random4_64_a_c.spr\n"
../bin/amigeconv -f sprite -w 64 -t -a data/random4.png output/amigeconv/random4_64_a_c.spr
test output/amigeconv/random4_64_a_c.spr data/piccon/random4_64_a_c.spr

printf "\033[0;32mResult:\033[0m All test passed!\n\n"
