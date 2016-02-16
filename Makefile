MAKE=		make -C

SERVER= rtype

SERVER_BIN=	server_rtype

SERVER_REPO=	server

CLIENT= clien_rtype

CLIENT_BIN=	client_rtype

CLIENT_REPO=	client

all:		$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):
		$(MAKE) $(SERVER_REPO)
		@ln -s $(SERVER_REPO)/$(SERVER_BIN) $(SERVER_BIN)

$(CLIENT_BIN):
		$(MAKE) $(CLIENT_REPO)
		@ln -s $(CLIENT_REPO)/$(CLIENT_BIN) $(CLIENT_BIN)

clean:
		$(MAKE) $(SERVER_REPO) clean
		$(MAKE) $(CLIENT_REPO) clean

fclean:
		@rm -f $(SERVER_BIN)
		$(MAKE) $(SERVER_REPO) fclean
		@rm -f $(CLIENT_BIN)
		$(MAKE) $(CLIENT_REPO) fclean

re:
		$(MAKE) $(SERVER_REPO) re
		$(MAKE) $(CLIENT_REPO) re
