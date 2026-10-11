# Official Poryscript binary is installed by the workspace bootstrap.
PORYSCRIPT := tools/poryscript/poryscript$(EXE)
PORY_SOURCES := $(shell find data/ -type f -name '*.pory')
PORY_OUTPUTS := $(PORY_SOURCES:.pory=.inc)
AUTO_GEN_TARGETS += $(PORY_OUTPUTS)

# Restrict generation to real .pory sources; never rebuild upstream .inc files.
ifneq ($(strip $(PORY_OUTPUTS)),)
$(PORY_OUTPUTS): %.inc: %.pory $(PORYSCRIPT) tools/poryscript/command_config.json tools/poryscript/font_config.json
	$(PORYSCRIPT) -i $< -o $@ -fc tools/poryscript/font_config.json -cc tools/poryscript/command_config.json
endif
