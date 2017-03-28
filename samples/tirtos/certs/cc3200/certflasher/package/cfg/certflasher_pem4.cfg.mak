# invoke SourceDir generated makefile for certflasher.pem4
certflasher.pem4: .libraries,certflasher.pem4
.libraries,certflasher.pem4: package/cfg/certflasher_pem4.xdl
	$(MAKE) -f package/cfg/certflasher_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/certflasher_pem4.src/makefile.libs clean

