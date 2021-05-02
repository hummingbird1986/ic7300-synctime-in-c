synctime: synctime.o serial_config.o num_hex.o

	cc -o synctime synctime.o  serial_config.o num_hex.o

synctime.o: synctime.c
	cc -c synctime.c

serial_config.o: serial_config.c
	cc -c serial_config.c serial_config.h

num_hex.o: num_hex.c
	cc -c  num_hex.c num_hex.h

clean:
	rm -f synctime synctime.o serial_config.o num_hex.o serial_config.h.gch num_hex.h.gch
