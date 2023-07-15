UTIL = ./src/util.cpp ./src/mkSocket.cpp
MAIN1 = ./app/chat.cpp
MAIN2 = ./app/chatServer.cpp
BINARY1 = ./bin/client
BINARY2 = ./bin/server

ifeq (client,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

ifeq (server,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 1,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

all:
	@g++ -Wall  -Wno-unused-result -Werror -g $(UTIL) $(MAIN1) -o $(BINARY1) -lm -pthread
	@g++ -Wall  -Wno-unused-result -Werror -g $(UTIL) $(MAIN2) -o $(BINARY2) -lm -pthread

client:
	@$(BINARY1) $(RUN_ARGS)

server:
	@$(BINARY2) $(RUN_ARGS)