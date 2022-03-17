distclean: clean firmware-distclean esp-serial-distclean
	${RM} -r bin/
	${RM} *~ include/*~
	${RM} ${extra_clean}
