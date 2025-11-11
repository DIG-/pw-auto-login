#!/usr/bin/env bash
MAGICK=${MAGICK:-magick}
FILE="gray.tga"
OUTPUT="gray"
rm -r "$OUTPUT"
mkdir "$OUTPUT"
for I in {17..33}; do
  echo "Processing $I"
  "$MAGICK" "$FILE" -crop 48x48+1+$(($((I*50))+1)) "PNG:$OUTPUT/$I.png"
  #"$MAGICK" "$FILE" -crop 50x50+0+$(($((I*50))+0)) "PNG:$OUTPUT/$I.png"
done

for I in {17..33}; do
  echo "Resizing $I"
  "$MAGICK" "$OUTPUT/$I.png" -filter Robidoux -resize 32x32 "PNG:$OUTPUT/${I}_32.png"
  "$MAGICK" "$OUTPUT/$I.png" -filter Robidoux -resize 24x24 "PNG:$OUTPUT/${I}_24.png"
  "$MAGICK" "$OUTPUT/$I.png" -filter Robidoux -resize 16x16 "PNG:$OUTPUT/${I}_16.png"
done

for I in {17..33}; do
  echo "Iconifying $I"
  "$MAGICK" -background transparent "$OUTPUT/$I.png" "PNG:$OUTPUT/${I}_32.png" "PNG:$OUTPUT/${I}_24.png" "PNG:$OUTPUT/${I}_16.png" "$OUTPUT/${I}_icon.ico"
done