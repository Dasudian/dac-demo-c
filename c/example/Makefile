CC= gcc
INCLUDE_DIR= /home/sea/SDK/dasudian_cloud-1.0.0/
LIB_DIR= /home/sea/SDK/dasudian_cloud-1.0.0/
CFLAGS= -I$(INCLUDE_DIR) -g -O0 -fexceptions
LDFLAGS= -L$(LIB_DIR) -ldsdcloud

hello: *.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 

.PHONY: clean

clean:
	rm -rf *.o core
