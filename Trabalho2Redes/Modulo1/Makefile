UTIL = ./src/util.cpp ./src/mkSocket.cpp
MAIN = ./app/chat.cpp
BINARY = ./bin/executavel

ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

all:
	@g++ -Wall  -Wno-unused-result -Werror -g $(UTIL) $(MAIN) -o $(BINARY) -lm -pthread

run:
	@$(BINARY) $(RUN_ARGS)