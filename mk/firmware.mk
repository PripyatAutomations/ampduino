# Support building and installing firmware for ubitx and atu-100 as needed
ATU100_FW := atu-100/dist/default/production/atu-100-mplab.production.elf
UBITX_FW := ubitx/bin/nano/ubitx/ubitx.elf

install-atu100:  ${ATU100_FW}
	# XXX: Prompt user to connect programmer
	# XXX: Upload and verify image

firmware: ${ATU100_FW} ${UBITX_FW}

${ATU100_FW}:
	${MAKE} -C atu-100

${UBITX_FW}:
	${MAKE} -C ubitx all

firmware-distclean: firmware-clean
	${MAKE} -C ubitx distclean

firmware-clean:
	${MAKE} -C atu-100 clean
	${MAKE} -C ubitx clean
