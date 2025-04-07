LIBS=-framework ApplicationServices \
	 -F /System/Library/PrivateFrameworks \
	 -framework DisplayServices \
	 -Wl,-U,_DisplayServicesGetBrightness \
	 -lm

brightme: main.c
	$(CC) -o $@ $^ $(LIBS)
