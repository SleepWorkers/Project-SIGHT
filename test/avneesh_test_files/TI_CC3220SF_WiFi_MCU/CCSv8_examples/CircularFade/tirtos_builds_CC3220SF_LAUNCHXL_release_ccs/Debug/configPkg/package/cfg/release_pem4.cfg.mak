# invoke SourceDir generated makefile for release.pem4
release.pem4: .libraries,release.pem4
.libraries,release.pem4: package/cfg/release_pem4.xdl
	$(MAKE) -f /home/stark/ccsv8_ws/CC3220SF_Basics/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/src/makefile.libs

clean::
	$(MAKE) -f /home/stark/ccsv8_ws/CC3220SF_Basics/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/src/makefile.libs clean

