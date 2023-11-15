BRANCH=$${CI_COMMIT_BRANCH:-jal}
ENVS=xiao
PROG=clock
REPO=pharmdata.ddns.net
MQTTHOST=pharmdata.ddns.net

all: push

.build : src/main.cpp platformio.ini Makefile
	pio run
	touch .build

upload.xiao: .build
	pio run -e xiao --target upload

push: .build
	for ENV in $(ENVS) ; do \
        ssh lamb@$(REPO) mkdir -p /var/www/html/firmware/$(BRANCH)/$$ENV/$(PROG) ; \
	    scp .pio/build/$$ENV/firmware.bin lamb@$(REPO):/var/www/html/firmware/$(BRANCH)/$$ENV/$(PROG)/firmware.bin ; \
	    done
	mosquitto_pub -h ${MQTTHOST} -p 1883 -t "/$(PROG)/CONTROL" -m "reboot"

monitor:
	pio device monitor

mu: upload.xiao monitor

um.xiao: upload.xiao monitor



