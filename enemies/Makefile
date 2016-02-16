##
## Makefile for Makefile in /home/lopez_t/rtype/enemies
##
## Made by Thibaut Lopez
## Login   <lopez_t@epitech.net>
##
## Started on  Thu Dec 17 12:01:26 2015 Thibaut Lopez
## Last update Sat Jan  2 18:30:06 2016 Thibaut Lopez
##

CXX=		g++

RM=		rm -f

CPPFLAGS=	-W -Wall -Wextra -I./include -ldl -std=c++11

INCLUDES=	-I./includes/  -I../API/interface -I../API/includes -I../server/includes

ZIPP_SRC=	Zipp/Zipp.cpp

SAT_SRC=	Satellite/Satellite.cpp

MANX_SRC=	Manx/Manx.cpp ../server/src/Entity.cpp ../server/src/Game.cpp ../API/Tools/STTime.cpp ../API/Time/LTime.cpp

BAGUT_SRC=	Bagut/Bagut.cpp

BYDO_SRC=	Bydo/Bydo.cpp

ZIPP_NAME=	Zipp.so

SAT_NAME=	Satellite.so

MANX_NAME=	Manx.so

BAGUT_NAME= 	Bagut.so

BYDO_NAME= 	Bydo.so

ZIPP_OBJ=	$(ZIPP_SRC:.cpp=.o)

SAT_OBJ=	$(SAT_SRC:.cpp=.o)

MANX_OBJ=	$(MANX_SRC:.cpp=.o)

BAGUT_OBJ=	$(BAGUT_SRC:.cpp=.o)

BYDO_OBJ=	$(BYDO_SRC:.cpp=.o)

all:		$(ZIPP_NAME) $(SAT_NAME) $(MANX_NAME) $(BAGUT_NAME) $(BYDO_NAME)

Zipp:		$(ZIPP_NAME)

Satellite:	$(SAT_NAME)

Manx:		$(MANX_NAME)

Bagut:		$(BAGUT_NAME)

Bydo:		$(BYDO_NAME)

$(ZIPP_NAME):	$(ZIPP_OBJ)
		$(CXX) -o $@ $(ZIPP_OBJ) $(CPPFLAGS) -fPIC -shared

$(SAT_NAME):	$(SAT_OBJ)
		$(CXX) -o $@ $(SAT_OBJ) $(CPPFLAGS) -fPIC -shared

$(MANX_NAME):	$(MANX_OBJ)
		$(CXX) -o $@ $(MANX_OBJ) $(CPPFLAGS) -fPIC -shared

$(BAGUT_NAME):	$(BAGUT_OBJ)
		$(CXX) -o $@ $(BAGUT_OBJ) $(CPPFLAGS) -fPIC -shared

$(BYDO_NAME):	$(BYDO_OBJ)
		$(CXX) -o $@ $(BYDO_OBJ) $(CPPFLAGS) -fPIC -shared

%.o:		%.cpp
		$(CC) $(CPPFLAGS) $(INCLUDES) -fPIC -c -o $@ $<

clean:
		$(RM) $(ZIPP_OBJ)
		$(RM) $(SAT_OBJ)
		$(RM) $(MANX_OBJ)
		$(RM) $(BAGUT_OBJ)
		$(RM) $(BYDO_OBJ)

fclean:		clean
		$(RM) $(ZIPP_NAME)
		$(RM) $(SAT_NAME)
		$(RM) $(MANX_NAME)
		$(RM) $(BAGUT_NAME)
		$(RM) $(BYDO_NAME)

re:		fclean all
