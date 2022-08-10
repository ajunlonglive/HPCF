objects = $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS = -g
LIBS = -lpthread -ldl ./libhttp/libhttp.a
DEFINES = -HPCF_DEBUG

all: libjson libhttp modules crypto_cloud

libjson: none
	# build libjson
	$(MAKE) -C libjson

libhttp: none
	# build libhttp
	$(MAKE) -C libhttp

# 所有的子模块在这里编译
modules: none
	# build modules
	$(MAKE) -C modules/login_authentication
	cp -f modules/login_authentication/*.so plugins/

crypto_cloud: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects) $(LIBS)

none:
	# build

.PHONY: clean
clean:
	rm -f crypto_cloud
	rm -f $(objects)
	rm -f plugins/*.so

	# clean libjson
	$(MAKE) -C libjson clean

	# clean libhttp
	$(MAKE) -C libhttp clean

	# clean modules
	$(MAKE) -C modules/login_authentication clean