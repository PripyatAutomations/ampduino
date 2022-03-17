# A little bit of a mess to load the system.cf into
# a factory_default which gets loaded into EEPROM at
# first boot...
gen-eeprom: eeprom-data.h

eeprom.c: eeprom-data.h

.tmp.eeprom.user: system.cf
	cat system.cf | \
	   egrep -v '^.*#' | \
	   tr -s " " | tr -d '\r\n' | \
	     xxd -i | \
	     sed 's/\([0-9a-f]\)$$/\0, 0x00/' \
	     > $@

eeprom-data.h: .tmp.eeprom.user
	@> $@
	@echo "/*" >> $@
	@echo " * This header is auto-generated from system.cf by gen-eeprom in mk/gen-eeprom.mk" >> $@
	@echo " * " >> $@
	@echo " * Please do not edit it directly as it will be destroyed during build!" >> $@
	@echo " */" >> $@
	@echo "" >> $@
	@echo "#if !defined(_eeprom_data_h)" >> $@
	@echo "#if defined(EEPROM_C)" >> $@
	@echo "const char factory_defaults[] = "{ >> $@
	@cat .tmp.eeprom.user >> $@
	@echo "};" >> $@
	@echo "#else" >> $@
	@echo "extern const char factory_defaults[];" >> $@
	@echo "// else defined(EEPROM_C)" >> $@
	@echo "#endif" >> $@
	@echo "// !defined(__eeprom_data_h)" >> $@
	@echo "#endif" >> $@

extra_headers += eeprom-data.h

extra_clean += eeprom-data.h .tmp.eeprom.user

