cd frames
mogrify -flip -format jpg frame_*.ppm
ffmpeg -f image2 -i frame_%04d.jpg ../video.mpg

