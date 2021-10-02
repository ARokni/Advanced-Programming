CC = g++
CFLAGS  = -g -Wall

default: main




main:	my_server.o main.o handlers.o response.o request.o utilities.o server.o route.o main_.o Ap_Drive.o File.o Folder.o User.o Group.o Ap_Exception.o Utility.o
	$(CC) $(CFLAGS) -o main my_server.o main.o handlers.o response.o request.o utilities.o server.o route.o Ap_Drive.o File.o Folder.o User.o Group.o Ap_Exception.o



main_.o:  examples/main.cpp Ap_Exception.o
	$(CC) $(CFLAGS) -c examples/main.cpp


response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c utils/response.cpp

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CFLAGS) -c utils/request.cpp

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CFLAGS) -c utils/utilities.cpp

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp server/Ap_Drive.h
	$(CC) $(CFLAGS) -c server/server.cpp

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c server/route.cpp

handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c examples/handlers.cpp

my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c examples/my_server.cpp


main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c examples/main.cpp



Ap_Drive.o:  server/Ap_Drive.cpp server/Ap_Drive.h Ap_Exception.o User.o Group.o File.o Folder.o Utility.o
	$(CC) $(CFLAGS) -c server/Ap_Drive.cpp

Utility.o:  server/Utility.cpp server/Utility.h Ap_Exception.o
	$(CC) $(CFLAGS) -c server/Utility.cpp

Folder.o:  server/Folder.cpp server/Folder.h File.o
	$(CC) $(CFLAGS) -c server/Folder.cpp

File.o:  server/File.cpp server/File.h
	$(CC) $(CFLAGS) -c server/File.cpp

Group.o:  server/Group.cpp server/Group.h User.o
	$(CC) $(CFLAGS) -c server/Group.cpp

User.o:  server/User.cpp server/User.h
	$(CC) $(CFLAGS) -c server/User.cpp

Ap_Exception.o:  server/Ap_Exception.cpp server/Ap_Exception.h
	$(CC) $(CFLAGS) -c server/Ap_Exception.cpp






clean: 
	$(RM) count *.o *~