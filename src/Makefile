CC = g++ -std=gnu++20
CFLAGS = -Wall -g
EXECUTABLE_NAME = main

main: main.o data/Data.o image/Image.o volume/Volume.o filter/Filter.o filter/ImageFilter.o filter/VolumeFilter.o slice/Slice.o unittest/Unittest.o projection/Projection.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) main.o data/Data.o image/Image.o volume/Volume.o filter/Filter.o filter/ImageFilter.o filter/VolumeFilter.o slice/Slice.o unittest/Unittest.o projection/Projection.o 

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

image/Image.o: image/Image.h data/Data.h 
	$(CC) $(CFLAGS) -c image/Image.cpp -o image/Image.o

volume/Volume.o: volume/Volume.h data/Data.h image/Image.h 
	$(CC) $(CFLAGS) -c volume/Volume.cpp -o volume/Volume.o

data/Data.o: data/Data.h stb/stb_image.h
	$(CC) $(CFLAGS) -c data/Data.cpp -o data/Data.o

filter/Filter.o: filter/Filter.h data/Data.h
	$(CC) $(CFLAGS) -c filter/Filter.cpp -o filter/Filter.o

filter/ImageFilter.o: filter/ImageFilter.h data/Data.h image/Image.h
	$(CC) $(CFLAGS) -c filter/ImageFilter.cpp -o filter/ImageFilter.o

filter/VolumeFilter.o: filter/VolumeFilter.h data/Data.h volume/Volume.h
	$(CC) $(CFLAGS) -c filter/VolumeFilter.cpp -o filter/VolumeFilter.o

slice/Slice.o: slice/Slice.h data/Data.h volume/Volume.h
	$(CC) $(CFLAGS) -c slice/Slice.cpp -o slice/Slice.o

projection/Projection.o: projection/Projection.h filter/Filter.h data/Data.h volume/Volume.h
	$(CC) $(CFLAGS) -c projection/Projection.cpp -o projection/Projection.o

unittest/Unittest.o: unittest/Unittest.h data/Data.h volume/Volume.h
	$(CC) $(CFLAGS) -c unittest/Unittest.cpp -o unittest/Unittest.o

clean:
	$(RM) ./*.o ./*/*.o $(EXECUTABLE_NAME)
