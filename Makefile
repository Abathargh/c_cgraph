CC = gcc
app = corona_graph
inc = -I /usr/include/python3.8 -I /usr/lib/x86_64-linux-gnu -I /home/mar/json.h/
incjson = -I /home/mar/json.h/
link = -lpython3.8 -lcurl
objects = data.o json_helpers.o

all : $(objects)
	cc -g $(app).c $(objects) $(inc) -o $(app) $(link)
	rm $(objects)

json_helpers.o :
	cc -c $(incjson) json_helpers.c 

data.o :
	cc -c $(incjson) data.c

clean :
	-rm $(app) *.png *.json

.PHONY : clean