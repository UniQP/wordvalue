CFLAGS += -Wall -W -g

SOURCES = wordvalue.c

Q = @

GOAL = wordvalue
all: $(GOAL)

.PHONY: all clean

$(GOAL): $(SOURCES)
	@echo '===> CC $@'
	$(Q)$(CXX) $(CFLAGS) $(SOURCES) -o $(GOAL)

clean:
	@echo '===> CLEAN'
	$(Q)rm -rf $(GOAL)
