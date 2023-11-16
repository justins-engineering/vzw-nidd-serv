CC ?= gcc
CFLAGS ?= -g -O2 -fstack-protector-strong -Wall -Wextra -Wformat -Werror=format-security -D_FORTIFY_SOURCE=2 -fPIC
LDFLAGS ?= -Wl,-z,relro -Wl,-z,now -Wl,--as-needed -pie -L. -lc -lpthread -lcurl -lunit -ltb64

VPATH = src

objects = main.o jsmn.o json_helpers.o http_get_stop.o curl_callbacks.o parse_stop_json.o nidd_client.o

all: jsmn.h libtb64.a app

app: $(objects)
	$(CC) $(CFLAGS) $(objects) -o app $(LDFLAGS)
	chmod +x app

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

libtb64.a:
	$(MAKE) -C ./Turbo-Base64 libtb64.a
	cp ./Turbo-Base64/libtb64.a /usr/lib
	cp ./Turbo-Base64/turbob64.h /usr/include

jsmn.h:
	cp ./jsmn/jsmn.h /usr/include

.PHONY: clean libtb64.a jsmn.h install
clean:
	rm app $(objects)
