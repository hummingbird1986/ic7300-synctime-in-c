synctime: synctime.o serial_config.o hr_min.o

	cc -o synctime synctime.o  serial_config.o hr_min.o

synctime.o: synctime.c
	cc -c synctime.c

serial_config.o: serial_config.c
	cc -c serial_config.c serial_config.h

hr_min.o: hr_min.c
	cc -c  hr_min.c hr_min.h

clean:
	rm -f synctime synctime.o serial_config.o hr_min.o serial_config.h.gch hr_min.h.gch
