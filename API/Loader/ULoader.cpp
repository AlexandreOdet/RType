#include "ULoader.hh"

ULoader::ULoader()
{
  this->_handle = NULL;
  this->_loadf = NULL;
}

ULoader::~ULoader()
{
  this->_handle = NULL;
  this->_loadf = NULL;
}

bool ULoader::openLibrary(const std::string & lib_path)
{
  if (this->_handle != NULL)
    return (false);
  try
    {
      if ((_handle = dlopen(lib_path.c_str(), RTLD_LAZY)) != NULL)
      {
        std::cout << "[UNIX :] Enemy Load Correctly !" << std::endl;
        return true;
      }
      else
      	throw std::invalid_argument("Invalid library");
    }
  catch (const std::invalid_argument &ia)
    {
      std::cerr << "Invalid argument: " << ia.what() << std::endl;
      return false;
    }
  return false;
}

void	ULoader::closeLibrary() const
{
  if (this->_handle == NULL)
    return;
  dlclose(this->_handle);
}

IEnemy *ULoader::getInstance() const
{
  IEnemy *(*enemy)();
  enemy = reinterpret_cast<IEnemy *(*)()>(dlsym(this->_handle, "loadLib"));
  if (!enemy)
    throw std::runtime_error(dlerror());
  return (enemy());
}
