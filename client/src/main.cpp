#include "client.hh"

int main()
{
  try
  {
	client *cli = new client();
    cli->loop();
    delete cli;
  }
  catch (FileError const &e)
  {
    std::cerr << "Impossible to load " << e.what() << " at : " << e.where() << std::endl;
    return 1;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
