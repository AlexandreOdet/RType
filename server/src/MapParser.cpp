//
// MapParser.cpp for  in /home/coudra_c/rendu/rtype
//
// Made by colin
// Login   <coudra_c@epitech.net>
//
// Started on  Mon Dec 21 16:12:07 2015 colin
// Last update Tue Dec 22 11:32:40 2015 colin
//

#include "MapParser.hh"

MapParser::MapParser()
{

}

MapParser::~MapParser()
{

}

#include <stdio.h>

// tag(enemies, open) [ enemy ]* tag(enemies, closed)
// tag(enemies, open) [ enemy ]* tag(enemies, closed)

bool			MapParser::parse(const std::string &path_to_map)
{
  std::ifstream		myfile(path_to_map);
  Buffer		buff(&myfile);
  unsigned int		u = 1;
  char			*tmp;

  while ((tmp = buff.getContext(u)) && u == 1)
    {
      printf("%c", *tmp);
    }
  return (false);
}

char			MapParser::serialize_char(const char *str)
{
  char ret = 0;

  for (int i = 0; i < 8; ++i)
    {
      ret |= ((str[7 - i] == WALL_CHAR) << i);
    }
  return (ret);
}
