#!/bin/bash

ERROR=0

make clean stegano

echo -e "\nTesting your stegano implementation..."
./stegano < test/input.txt > output.txt

echo "step 1"
diff -q output.txt test/correct.txt
if [[ $? -ne 0 ]]
then
    ERROR=1
fi
echo "step 2"
diff -q TextFontys.txt demux_TextFontys.txt
if [[ $? -ne 0 ]]
then
    ERROR=1
fi
echo "step 3"
cmp -b ImageTrabant.bmp demux_ImageTrabant_0.bmp
if [[ $? -ne 0 ]]
then
    ERROR=1
fi
echo "step 4"
cmp -b ImageRedFerrari.bmp demux_ImageRedFerrari_8.bmp
if [[ $? -ne 0 ]]
then
    ERROR=1
fi

if [[ $ERROR -eq 0 ]]
then
    echo -e "\nAs far as tested in this script, SteganoC is completely correct!"
    rm -f demux_ImageCitroen2Cv.bmp
    rm -f demux_TextFontys.txt
    rm -f demux_ImageRedFerrari_0.bmp
    rm -f demux_ImageRedFerrari_1.bmp
    rm -f demux_ImageRedFerrari_4.bmp
    rm -f demux_ImageRedFerrari_7.bmp
    rm -f demux_ImageRedFerrari_8.bmp
    rm -f demux_ImageTrabant_0.bmp
    rm -f demux_ImageTrabant_1.bmp
    rm -f demux_ImageTrabant_4.bmp
    rm -f demux_ImageTrabant_7.bmp
    rm -f demux_ImageTrabant_8.bmp
    rm -f mux_ImageCitroen2Cv.bmp_TextFontys.txt.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_0.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_1.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_2.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_3.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_4.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_5.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_6.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_7.bmp
    rm -f mux_ImageTrabant.bmp_ImageRedFerrari.bmp_8.bmp
    rm -f output.txt
fi
