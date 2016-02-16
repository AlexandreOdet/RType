#include "ILoader.hh"
#include "WLoader.hh"

typedef IEnemy *(*load_func)();
typedef void (*unload_func)(IEnemy *);


WLoader::WLoader()
{
  this->_library = NULL;
}

WLoader::~WLoader()
{
  this->_library = NULL;
}

bool WLoader::openLibrary(const std::string & lib_path)
{
  try
  {
    this->_library = LoadLibrary(lib_path.c_str());
    if (this->_library)
    {
      std::cout << "[Windows :] Enemy Load Correctly !  " << std::endl;
      return true;
    }
    else
    {
      throw std::invalid_argument("Invalid library");
      return false;
    }
  }
  catch (...)
  {
    std::cerr << "An error occured while loading dynamic library" << std::endl;
    return false;
  }
  return false;
}

void WLoader::closeLibrary() const
{
  FreeLibrary(this->_library);
}

IEnemy *WLoader::getInstance() const
{
	IEnemy *(*enemy)();
	enemy = reinterpret_cast<IEnemy *(*)()>
		((load_func)GetProcAddress(this->_library, "loadLib"));
	if (!enemy)
		throw std::runtime_error("Cannot get Instance");
	return (enemy());
}
 
