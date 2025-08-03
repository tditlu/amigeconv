#!/bin/bash

options=(
    # Chunky tests
    "-f chunky %s %s|data/random8.png|output/amigeconv/random8.chk|data/piccon/random8.chk"
    "-f chunky -d 8 %s %s|data/random8.png|output/amigeconv/random8_d.chk|data/extra/random8.chk"
    "-f chunky -d 4 %s %s|data/random4.png|output/amigeconv/random4.chk|data/extra/random4.chk"
    "-f chunky -d 2 %s %s|data/random2.png|output/amigeconv/random2.chk|data/extra/random2.chk"

    # Bitplane depth 8 tests
    "-f bitplane -d 8 %s %s|data/random8.png|output/amigeconv/random8.raw|data/piccon/random8.raw"
    "-l -f bitplane -d 8 %s %s|data/random8.png|output/amigeconv/random8_i.raw|data/piccon/random8_i.raw"
    "-f bitplane -m -d 8 %s %s|data/random8.png|output/amigeconv/random8_mask.raw|data/piccon/random8_mask.raw"
    "-f bitplane -m inverted -d 8 %s %s|data/random8.png|output/amigeconv/random8_mask_inv.raw|data/piccon/random8_mask_inv.raw"
    "-l -f bitplane -m -d 8 %s %s|data/random8.png|output/amigeconv/random8_mask_i.raw|data/piccon/random8_mask_i.raw"
    "-l -f bitplane -m inverted -d 8 %s %s|data/random8.png|output/amigeconv/random8_mask_inv_i.raw|data/piccon/random8_mask_inv_i.raw"

    # Bitplane depth 7 tests
    "-f bitplane -d 7 %s %s|data/random7.png|output/amigeconv/random7.raw|data/piccon/random7.raw"
    "-l -f bitplane -d 7 %s %s|data/random7.png|output/amigeconv/random7_i.raw|data/piccon/random7_i.raw"
    "-f bitplane -m -d 7 %s %s|data/random7.png|output/amigeconv/random7_mask.raw|data/piccon/random7_mask.raw"
    "-f bitplane -m inverted -d 7 %s %s|data/random7.png|output/amigeconv/random7_mask_inv.raw|data/piccon/random7_mask_inv.raw"
    "-l -f bitplane -m -d 7 %s %s|data/random7.png|output/amigeconv/random7_mask_i.raw|data/piccon/random7_mask_i.raw"
    "-l -f bitplane -m inverted -d 7 %s %s|data/random7.png|output/amigeconv/random7_mask_inv_i.raw|data/piccon/random7_mask_inv_i.raw"

    # Bitplane depth 6 tests
    "-f bitplane -d 6 %s %s|data/random6.png|output/amigeconv/random6.raw|data/piccon/random6.raw"
    "-l -f bitplane -d 6 %s %s|data/random6.png|output/amigeconv/random6_i.raw|data/piccon/random6_i.raw"
    "-f bitplane -m -d 6 %s %s|data/random6.png|output/amigeconv/random6_mask.raw|data/piccon/random6_mask.raw"
    "-f bitplane -m inverted -d 6 %s %s|data/random6.png|output/amigeconv/random6_mask_inv.raw|data/piccon/random6_mask_inv.raw"
    "-l -f bitplane -m -d 6 %s %s|data/random6.png|output/amigeconv/random6_mask_i.raw|data/piccon/random6_mask_i.raw"
    "-l -f bitplane -m inverted -d 6 %s %s|data/random6.png|output/amigeconv/random6_mask_inv_i.raw|data/piccon/random6_mask_inv_i.raw"

    # Bitplane depth 5 tests
    "-f bitplane -d 5 %s %s|data/random5.png|output/amigeconv/random5.raw|data/piccon/random5.raw"
    "-l -f bitplane -d 5 %s %s|data/random5.png|output/amigeconv/random5_i.raw|data/piccon/random5_i.raw"
    "-f bitplane -m -d 5 %s %s|data/random5.png|output/amigeconv/random5_mask.raw|data/piccon/random5_mask.raw"
    "-f bitplane -m inverted -d 5 %s %s|data/random5.png|output/amigeconv/random5_mask_inv.raw|data/piccon/random5_mask_inv.raw"
    "-l -f bitplane -m -d 5 %s %s|data/random5.png|output/amigeconv/random5_mask_i.raw|data/piccon/random5_mask_i.raw"
    "-l -f bitplane -m inverted -d 5 %s %s|data/random5.png|output/amigeconv/random5_mask_inv_i.raw|data/piccon/random5_mask_inv_i.raw"

    # Bitplane depth 4 tests
    "-f bitplane -d 4 %s %s|data/random4.png|output/amigeconv/random4.raw|data/piccon/random4.raw"
    "-l -f bitplane -d 4 %s %s|data/random4.png|output/amigeconv/random4_i.raw|data/piccon/random4_i.raw"
    "-f bitplane -m -d 4 %s %s|data/random4.png|output/amigeconv/random4_mask.raw|data/piccon/random4_mask.raw"
    "-f bitplane -m inverted -d 4 %s %s|data/random4.png|output/amigeconv/random4_mask_inv.raw|data/piccon/random4_mask_inv.raw"
    "-l -f bitplane -m -d 4 %s %s|data/random4.png|output/amigeconv/random4_mask_i.raw|data/piccon/random4_mask_i.raw"
    "-l -f bitplane -m inverted -d 4 %s %s|data/random4.png|output/amigeconv/random4_mask_inv_i.raw|data/piccon/random4_mask_inv_i.raw"

    # Bitplane depth 3 tests
    "-f bitplane -d 3 %s %s|data/random3.png|output/amigeconv/random3.raw|data/piccon/random3.raw"
    "-l -f bitplane -d 3 %s %s|data/random3.png|output/amigeconv/random3_i.raw|data/piccon/random3_i.raw"
    "-f bitplane -m -d 3 %s %s|data/random3.png|output/amigeconv/random3_mask.raw|data/piccon/random3_mask.raw"
    "-f bitplane -m inverted -d 3 %s %s|data/random3.png|output/amigeconv/random3_mask_inv.raw|data/piccon/random3_mask_inv.raw"
    "-l -f bitplane -m -d 3 %s %s|data/random3.png|output/amigeconv/random3_mask_i.raw|data/piccon/random3_mask_i.raw"
    "-l -f bitplane -m inverted -d 3 %s %s|data/random3.png|output/amigeconv/random3_mask_inv_i.raw|data/piccon/random3_mask_inv_i.raw"

    # Bitplane depth 2 tests
    "-f bitplane -d 2 %s %s|data/random2.png|output/amigeconv/random2.raw|data/piccon/random2.raw"
    "-l -f bitplane -d 2 %s %s|data/random2.png|output/amigeconv/random2_i.raw|data/piccon/random2_i.raw"
    "-f bitplane -m -d 2 %s %s|data/random2.png|output/amigeconv/random2_mask.raw|data/piccon/random2_mask.raw"
    "-f bitplane -m inverted -d 2 %s %s|data/random2.png|output/amigeconv/random2_mask_inv.raw|data/piccon/random2_mask_inv.raw"
    "-l -f bitplane -m -d 2 %s %s|data/random2.png|output/amigeconv/random2_mask_i.raw|data/piccon/random2_mask_i.raw"
    "-l -f bitplane -m inverted -d 2 %s %s|data/random2.png|output/amigeconv/random2_mask_inv_i.raw|data/piccon/random2_mask_inv_i.raw"

    # Bitplane depth 1 tests
    "-f bitplane -d 1 %s %s|data/random1.png|output/amigeconv/random1.raw|data/piccon/random1.raw"
    "-l -f bitplane -d 1 %s %s|data/random1.png|output/amigeconv/random1_i.raw|data/piccon/random1_i.raw"
    "-f bitplane -m -d 1 %s %s|data/random1.png|output/amigeconv/random1_mask.raw|data/piccon/random1_mask.raw"
    "-f bitplane -m inverted -d 1 %s %s|data/random1.png|output/amigeconv/random1_mask_inv.raw|data/piccon/random1_mask_inv.raw"
    "-l -f bitplane -m -d 1 %s %s|data/random1.png|output/amigeconv/random1_mask_i.raw|data/piccon/random1_mask_i.raw"
    "-l -f bitplane -m inverted -d 1 %s %s|data/random1.png|output/amigeconv/random1_mask_inv_i.raw|data/piccon/random1_mask_inv_i.raw"

    # Palette pal4 tests
    "-n -f palette -p pal4 %s %s|data/random1.png|output/amigeconv/random1.pal4|data/piccon/random1.pal4"
    "-n -f palette -p pal4 %s %s|data/random2.png|output/amigeconv/random2.pal4|data/piccon/random2.pal4"
    "-n -f palette -p pal4 %s %s|data/random3.png|output/amigeconv/random3.pal4|data/piccon/random3.pal4"
    "-n -f palette -p pal4 %s %s|data/random4.png|output/amigeconv/random4.pal4|data/piccon/random4.pal4"
    "-n -f palette -p pal4 %s %s|data/random5.png|output/amigeconv/random5.pal4|data/piccon/random5.pal4"
    "-n -f palette -p pal4 %s %s|data/random6.png|output/amigeconv/random6.pal4|data/piccon/random6.pal4"
    "-n -f palette -p pal4 %s %s|data/random7.png|output/amigeconv/random7.pal4|data/piccon/random7.pal4"
    "-n -f palette -p pal4 %s %s|data/random8.png|output/amigeconv/random8.pal4|data/piccon/random8.pal4"

    # Palette pal4 copper tests
    "-n -f palette -p pal4 -x %s %s|data/random1.png|output/amigeconv/random1.pal4_copper|data/piccon/random1.pal4_copper"
    "-n -f palette -p pal4 -x %s %s|data/random2.png|output/amigeconv/random2.pal4_copper|data/piccon/random2.pal4_copper"
    "-n -f palette -p pal4 -x %s %s|data/random3.png|output/amigeconv/random3.pal4_copper|data/piccon/random3.pal4_copper"
    "-n -f palette -p pal4 -x %s %s|data/random4.png|output/amigeconv/random4.pal4_copper|data/piccon/random4.pal4_copper"
    "-n -f palette -p pal4 -x %s %s|data/random5.png|output/amigeconv/random5.pal4_copper|data/piccon/random5.pal4_copper"

    # Palette pal8 tests
    " -f palette -p pal8 %s %s|data/random1.png|output/amigeconv/random1.pal8|data/piccon/random1.pal8"
    " -f palette -p pal8 %s %s|data/random2.png|output/amigeconv/random2.pal8|data/piccon/random2.pal8"
    " -f palette -p pal8 %s %s|data/random3.png|output/amigeconv/random3.pal8|data/piccon/random3.pal8"
    " -f palette -p pal8 %s %s|data/random4.png|output/amigeconv/random4.pal8|data/piccon/random4.pal8"
    " -f palette -p pal8 %s %s|data/random5.png|output/amigeconv/random5.pal8|data/piccon/random5.pal8"
    " -f palette -p pal8 %s %s|data/random6.png|output/amigeconv/random6.pal8|data/piccon/random6.pal8"
    " -f palette -p pal8 %s %s|data/random7.png|output/amigeconv/random7.pal8|data/piccon/random7.pal8"
    " -f palette -p pal8 %s %s|data/random8.png|output/amigeconv/random8.pal8|data/piccon/random8.pal8"

    # Palette pal8 copper tests
    " -f palette -p pal8 -x %s %s|data/random1.png|output/amigeconv/random1.pal8_copper|data/piccon/random1.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random2.png|output/amigeconv/random2.pal8_copper|data/piccon/random2.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random3.png|output/amigeconv/random3.pal8_copper|data/piccon/random3.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random4.png|output/amigeconv/random4.pal8_copper|data/piccon/random4.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random5.png|output/amigeconv/random5.pal8_copper|data/piccon/random5.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random6.png|output/amigeconv/random6.pal8_copper|data/piccon/random6.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random7.png|output/amigeconv/random7.pal8_copper|data/piccon/random7.pal8_copper"
    " -f palette -p pal8 -x %s %s|data/random8.png|output/amigeconv/random8.pal8_copper|data/piccon/random8.pal8_copper"

    # Palette pal32 tests
    " -f palette -p pal32 %s %s|data/random1.png|output/amigeconv/random1.pal32|data/piccon/random1.pal32"
    " -f palette -p pal32 %s %s|data/random2.png|output/amigeconv/random2.pal32|data/piccon/random2.pal32"
    " -f palette -p pal32 %s %s|data/random3.png|output/amigeconv/random3.pal32|data/piccon/random3.pal32"
    " -f palette -p pal32 %s %s|data/random4.png|output/amigeconv/random4.pal32|data/piccon/random4.pal32"
    " -f palette -p pal32 %s %s|data/random5.png|output/amigeconv/random5.pal32|data/piccon/random5.pal32"
    " -f palette -p pal32 %s %s|data/random6.png|output/amigeconv/random6.pal32|data/piccon/random6.pal32"
    " -f palette -p pal32 %s %s|data/random7.png|output/amigeconv/random7.pal32|data/piccon/random7.pal32"
    " -f palette -p pal32 %s %s|data/random8.png|output/amigeconv/random8.pal32|data/piccon/random8.pal32"

    # LoadRGB4 and LoadRGB32 tests
    "-n -f palette -p loadrgb4 %s %s|data/random1.png|output/amigeconv/random1.loadrgb4|data/piccon/random1.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random1.png|output/amigeconv/random1.loadrgb32|data/piccon/random1.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random2.png|output/amigeconv/random2.loadrgb4|data/piccon/random2.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random2.png|output/amigeconv/random2.loadrgb32|data/piccon/random2.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random3.png|output/amigeconv/random3.loadrgb4|data/piccon/random3.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random3.png|output/amigeconv/random3.loadrgb32|data/piccon/random3.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random4.png|output/amigeconv/random4.loadrgb4|data/piccon/random4.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random4.png|output/amigeconv/random4.loadrgb32|data/piccon/random4.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random5.png|output/amigeconv/random5.loadrgb4|data/piccon/random5.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random5.png|output/amigeconv/random5.loadrgb32|data/piccon/random5.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random6.png|output/amigeconv/random6.loadrgb4|data/piccon/random6.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random6.png|output/amigeconv/random6.loadrgb32|data/piccon/random6.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random7.png|output/amigeconv/random7.loadrgb4|data/piccon/random7.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random7.png|output/amigeconv/random7.loadrgb32|data/piccon/random7.loadrgb32"
    "-n -f palette -p loadrgb4 %s %s|data/random8.png|output/amigeconv/random8.loadrgb4|data/piccon/random8.loadrgb4"
    "-f palette -p loadrgb32 %s %s|data/random8.png|output/amigeconv/random8.loadrgb32|data/piccon/random8.loadrgb32"

    # Sprite tests
    "-f sprite -w 16 %s %s|data/random2.png|output/amigeconv/random2_16.spr|data/piccon/random2_16.spr"
    "-f sprite -w 32 %s %s|data/random2.png|output/amigeconv/random2_32.spr|data/piccon/random2_32.spr"
    "-f sprite -w 64 %s %s|data/random2.png|output/amigeconv/random2_64.spr|data/piccon/random2_64.spr"
    "-f sprite -w 16 -t %s %s|data/random2.png|output/amigeconv/random2_16_c.spr|data/piccon/random2_16_c.spr"
    "-f sprite -w 32 -t %s %s|data/random2.png|output/amigeconv/random2_32_c.spr|data/piccon/random2_32_c.spr"
    "-f sprite -w 64 -t %s %s|data/random2.png|output/amigeconv/random2_64_c.spr|data/piccon/random2_64_c.spr"
    "-f sprite -w 16 -a %s %s|data/random4.png|output/amigeconv/random4_16_a.spr|data/piccon/random4_16_a.spr"
    "-f sprite -w 32 -a %s %s|data/random4.png|output/amigeconv/random4_32_a.spr|data/piccon/random4_32_a.spr"
    "-f sprite -w 64 -a %s %s|data/random4.png|output/amigeconv/random4_64_a.spr|data/piccon/random4_64_a.spr"
    "-f sprite -w 16 -t -a %s %s|data/random4.png|output/amigeconv/random4_16_a_c.spr|data/piccon/random4_16_a_c.spr"
    "-f sprite -w 32 -t -a %s %s|data/random4.png|output/amigeconv/random4_32_a_c.spr|data/piccon/random4_32_a_c.spr"
    "-f sprite -w 64 -t -a %s %s|data/random4.png|output/amigeconv/random4_64_a_c.spr|data/piccon/random4_64_a_c.spr"
)

compare_files() {
    local out=$1 ref=$2
    if diff "$out" "$ref" > /dev/null 2>&1; then
        printf "\033[0;32mResult:\033[0m Binary files %s and %s are the same\n\n" "$out" "$ref"
    else
        printf "\033[0;31mError:\033[0m Binary files %s and %s differ\n\n" "$out" "$ref"
        exit 1
    fi
}

run_test() {
    local template="$1" in="$2" out="$3" ref="$4"
    local args
    args=$(printf -- "$template" "$in" "$out")
    local cmd="../bin/amigeconv $args"
    printf "\033[0;33mCommand:\033[0m %s\n" "$cmd"
    $cmd
    compare_files "$out" "$ref"
}

cd ..
make clean && make || exit 1
cd test/ || exit 1

for opt in "${options[@]}"; do
    IFS="|" read -r tmpl input out ref <<< "$opt"
    run_test "$tmpl" "$input" "$out" "$ref"
done

printf "\033[0;32mResult:\033[0m All tests passed!\n\n"
