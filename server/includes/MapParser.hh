//
// MapParser.hh for  in /home/coudra_c/rendu/rtype
//
// Made by colin
// Login   <coudra_c@epitech.net>
//
// Started on  Mon Dec 21 15:59:32 2015 colin
// Last update Tue Dec 22 11:36:15 2015 colin
//

#ifndef MAPPARSER_HH_
#define MAPPARSER_HH_

#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <array>
#include <fstream>
#include <stack>
#include "EnemyType.hh"

#define WALL_CHAR '@'
typedef std::vector<std::array<char, 8> > Map;

class EnemyType;

class MapParser
{
public:
  //! A buffer that will produce stream to be consumed by the MapParser
  class				Buffer
  {
#define	BUFFPAGE 4096
  public:
    Buffer(std::ifstream *file)
      : file(file)
    {
      this->i = 0;
      this->size = 0;
      this->buff = 0;
    }

    ~Buffer()
    {

    }
    //! Save the context, which can be restored if needed
    void			saveContext()
    {
      this->save.push(this->i);
    }

    //! Restore a saved context
    void			restoreContext()
    {
      this->i = this->save.top();
      this->save.pop();
    }

    //! Get to_read char from the file.
    //! If cannot read, change the value of to_read of the amount of read chars
    char			*getContext(unsigned int &to_read)
    {
      char			*ret;

      while (to_read > this->size - this->i)
	{
	  char			*tmp = this->buff;
	  std::streamsize	r;

	  this->buff = new char[this->size + BUFFPAGE];
	  if (tmp)
	    {
	      this->cpy(this->buff, tmp, this->size);
	      delete [] tmp;
	    }
	  r = this->file->readsome(&this->buff[i], BUFFPAGE);
	  if (r <= 0)
	    break;
	  this->size += r;
	}
      if (to_read > this->size - this->i)
	to_read = this->size - this->i;
      ret = &this->buff[this->i];
      this->i += to_read;
      return (ret);
    }

  private:
    //! Copy n char from src to dest, no matter if there are \0.
    //! dest is assumed long enough
    char			*cpy(char *dest, const char *src, size_t n)
    {
      for (size_t i = 0; i < n; ++i)
	dest[i] = src[i];
      return (dest);
    }

    std::ifstream		*file;
    std::stack<unsigned int>	save;
    unsigned int		i;
    char			*buff;
    unsigned int		size;
  };
  // \Buffer
				MapParser();
  virtual			~MapParser();

  //! This function takes a path to a map file into parameter and fill its field with the map info
  bool				parse(const std::string &path_to_map);
  //! This function serialize a 8 char string into a char, when '@' = 0b1 and else worth 0b0
  static char			serialize_char(const char *str);

protected:
  Map				map;
  std::map<char, EnemyType *>   _enemyTypes;
};

#endif /* MAPPARSER_HH_ */
