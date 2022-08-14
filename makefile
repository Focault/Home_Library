TARGET= HomeLibrary.out
CC= g++
CFLAGS= -g -I $(UI) -I $(MEDIA) -I $(CD) -I $(BOOK) -I $(LIBRARY) -I $(LIST) -I $(NAME) -I $(UTIL)
OBJS= main.o library.o media.o ui.o book.o name.o list.o disk.o libraryutilities.o
UI= UI/
MEDIA= Media/
CD= Media/CD/
BOOK= Media/Book/
LIBRARY= Library/
LIST= Data/List/
NAME= Data/Name/
UTIL= Library/Utilities/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	rm -f $(OBJS)

main.o: main.cpp $(LIBRARY)library.hpp
	$(CC) $(CFLAGS) -c main.cpp

library.o: $(LIBRARY)library.cpp $(LIBRARY)library.hpp $(LIST)list.hpp $(MEDIA)media.hpp $(UI)ui.hpp $(UTIL)libraryutilities.hpp
	$(CC) $(CFLAGS) -c $(LIBRARY)library.cpp

list.o: $(LIST)list.cpp $(LIST)list.hpp
	$(CC) $(CFLAGS) -c $(LIST)list.cpp

media.o: $(MEDIA)media.cpp $(MEDIA)media.hpp $(BOOK)book.hpp $(CD)disk.hpp
	$(CC) $(CFLAGS) -c $(MEDIA)media.cpp

ui.o: $(UI)ui.cpp $(UI)ui.hpp
	$(CC) $(CFLAGS) -c $(UI)ui.cpp

book.o: $(BOOK)book.cpp $(BOOK)book.hpp $(NAME)name.hpp
	$(CC) $(CFLAGS) -c $(BOOK)book.cpp

name.o: $(NAME)name.cpp $(NAME)name.hpp
	$(CC) $(CFLAGS) -c $(NAME)name.cpp

disk.o: $(CD)disk.cpp $(CD)disk.hpp $(UI)ui.hpp $(NAME)name.hpp
	$(CC) $(CFLAGS) -c $(CD)disk.cpp

libraryutilities.o: $(UTIL)libraryutilities.cpp $(UTIL)libraryutilities.hpp
	$(CC) $(CFLAGS) -c $(UTIL)libraryutilities.cpp

clean:
	rm -f $(TARGET) $(OBJS)