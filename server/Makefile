##
## Makefile for Makefile in /home/lopez_t/rtype/server
##
## Made by Thibaut Lopez
## Login   <lopez_t@epitech.net>
##
## Started on  Tue Nov 24 14:55:27 2015 Thibaut Lopez
## Last update Wed Dec 23 13:46:40 2015 Thibaut Lopez
##

CXX=		g++ -g3

RM=		rm -f

SRC_REPO=	src

API_REPO=	../API

INCLUDES=	-I./includes

API_INCLUDES=	-I$(API_REPO)/interface/ -I$(API_REPO)/includes

CXXFLAGS=	-W -Wall -Werror -std=c++11 $(INCLUDES) $(API_INCLUDES)

SRC=		$(SRC_REPO)/Entity.cpp			\
		$(SRC_REPO)/Wall.cpp			\
		$(SRC_REPO)/AShoot.cpp			\
		$(SRC_REPO)/NormalShoot.cpp		\
		$(SRC_REPO)/MediumShoot.cpp		\
		$(SRC_REPO)/LongShoot.cpp		\
		$(SRC_REPO)/EnemyShoot.cpp		\
		$(SRC_REPO)/Creature.cpp		\
		$(SRC_REPO)/Enemy.cpp			\
		$(SRC_REPO)/EnemyType.cpp		\
		$(SRC_REPO)/Player.cpp			\
		$(SRC_REPO)/FCommand.cpp		\
		$(SRC_REPO)/Stage.cpp			\
		$(SRC_REPO)/MapParser.cpp		\
		$(SRC_REPO)/Game.cpp			\
		$(SRC_REPO)/Room.cpp			\
		$(SRC_REPO)/ScopedLock.cpp		\
		$(SRC_REPO)/ThreadPool.cpp		\
		$(SRC_REPO)/Client.cpp			\
		$(SRC_REPO)/Server.cpp			\
		$(SRC_REPO)/main.cpp

API_SRC=	$(API_REPO)/Tools/PacketQueue.cpp	\
		$(API_REPO)/Tools/ReliabilitySystem.cpp	\
		$(API_REPO)/Tools/FlowControl.cpp	\
		$(API_REPO)/Tools/STTime.cpp		\
		$(API_REPO)/Tools/Timer.cpp		\
		$(API_REPO)/Network/LNetwork.cpp	\
		$(API_REPO)/Socket/LSocket.cpp		\
		$(API_REPO)/Thread/LThread.cpp		\
		$(API_REPO)/Mutex/LMutex.cpp		\
		$(API_REPO)/Loader/ULoader.cpp		\
		$(API_REPO)/Time/LTime.cpp

NAME=		server_rtype

API_OBJ=	$(API_SRC:.cpp=.o)

OBJ=		$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(API_OBJ) $(OBJ)
		$(CXX) $(API_OBJ) $(OBJ) -ldl -lpthread -o $(NAME) $(INCLUDES) $(API_INCLUDES)

%.o:		%.cpp
			$(CC) $(CXXFLAGS) $(INCLUDES) -fPIC -c -o $@ $<

clean:
		$(RM) $(API_OBJ)
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
