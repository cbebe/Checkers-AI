# Makefile to call make on both desktop and arduino 
all: arduino desktop

# compiles and runs the AI
desktop:
	cd ./desktop_ai && $(MAKE) && ./checkersai

# uploads the firmware on the Arduino
arduino:
	cd ./arduino_ui && $(MAKE) upload

# runs the clean target on each directory
clean:
	cd ./desktop_ai && $(MAKE) clean
	cd ./arduino_ui && $(MAKE) clean