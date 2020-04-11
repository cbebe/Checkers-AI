# Makefile to call make on both desktop and arduino 
all: arduino desktop

desktop:
	cd ./desktop_ai && $(MAKE) && ./checkersai
	
arduino:
	cd ./arduino_ui && $(MAKE) upload

clean:
	cd ./desktop_ai && $(MAKE) clean
	cd ./arduino_ui && $(MAKE) clean