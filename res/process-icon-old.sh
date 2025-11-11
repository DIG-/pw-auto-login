#!/usr/bin/env bash
MAGICK=${MAGICK:-magick}
FOLDER="按钮"
OUTPUT="tmp"
rm -r "$OUTPUT"
mkdir "$OUTPUT"
for FILE in "$FOLDER"/*.tga; do
  FILENAME=$(basename "$FILE" .tga)
  echo "Resizing $FILE"
  "$MAGICK" "$FILE" -filter Robidoux -resize 48x48 "PNG:$OUTPUT/${FILENAME}_48.png"
  "$MAGICK" "$FILE" -filter Robidoux -resize 32x32 "PNG:$OUTPUT/${FILENAME}_32.png"
  "$MAGICK" "$FILE" -filter Robidoux -resize 24x24 "PNG:$OUTPUT/${FILENAME}_24.png"
  "$MAGICK" "$FILE" -filter Robidoux -resize 16x16 "PNG:$OUTPUT/${FILENAME}_16.png"
  echo "Iconifying $FILE"
  "$MAGICK" -background transparent "$OUTPUT/${FILENAME}_48.png" "PNG:$OUTPUT/${FILENAME}_32.png" "PNG:$OUTPUT/${FILENAME}_24.png" "PNG:$OUTPUT/${FILENAME}_16.png" "$OUTPUT/${FILENAME}_icon.ico"
done