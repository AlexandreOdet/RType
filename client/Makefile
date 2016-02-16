CXX=            g++ -g3

RM=             rm -f

SFMLFLAGS=			-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_REPO=       src

API_REPO=       ../API

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
INCLUDES +=	-I./SFML/include -I./includes -I./includes/menu -I./includes/game
SFMLFLAGS=	-L./SFML -framework sfml-graphics  -framework sfml-window -framework sfml-system -framework sfml-audio
else
INCLUDES=	-I./includes -I./includes/menu -I./includes/game
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

API_INCLUDES=   -I$(API_REPO)/interface/ -I$(API_REPO)/includes

CXXFLAGS=       -W -Wall -Werror -std=c++11 $(INCLUDES) $(API_INCLUDES)

SRC=						src/menu/myPopUp.cpp \
								src/menu/Room.cpp \
								src/menu/ConnectMenu.cpp \
								src/menu/Cursor.cpp \
								src/menu/Menu.cpp \
								src/menu/MainWindow.cpp \
								src/menu/InsertCoin.cpp \
								src/menu/readyLighter.cpp \
								src/menu/Light.cpp \
								src/game/Beam.cpp \
								src/game/Eball.cpp \
								src/game/Eeye.cpp \
								src/game/Eredship.cpp \
								src/game/Eshoot.cpp \
								src/game/Explode.cpp \
								src/game/graphic.cpp \
								src/game/HUD.cpp \
								src/game/Nabibi.cpp \
								src/game/Object.cpp \
								src/game/Player.cpp \
								src/game/Shoot.cpp \
								src/game/Shootgun.cpp \
								src/game/Space.cpp \
								src/game/Spinlazor.cpp \
								src/game/Starship.cpp \
								src/Sound.cpp \
								src/client.cpp \
								src/AManager.cpp \
								src/main.cpp

API_SRC=        $(API_REPO)/Tools/FlowControl.cpp \
								$(API_REPO)/Tools/PacketQueue.cpp \
								$(API_REPO)/Tools/ReliabilitySystem.cpp \
								$(API_REPO)/Tools/STTime.cpp \
								$(API_REPO)/Tools/Timer.cpp \
								$(API_REPO)/Time/LTime.cpp \
								$(API_REPO)/Socket/LSocket.cpp \
								$(API_REPO)/Mutex/LMutex.cpp \
								$(API_REPO)/Client/LClient.cpp

NAME=           client_rtype

API_OBJ=        $(API_SRC:.cpp=.o)

OBJ=            $(SRC:.cpp=.o)

all:            $(NAME)

$(NAME):        $(API_OBJ) $(OBJ)
								$(CXX) $(API_OBJ) $(OBJ) -o $(NAME) $(CXXFLAGS) $(SFMLFLAGS)  $(INCLUDES) $(API_INCLUDES) -lpthread

clean:
								$(RM) $(API_OBJ)
								$(RM) $(OBJ)

fclean:         clean
								$(RM) $(NAME)

re:             fclean all
