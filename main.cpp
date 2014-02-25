#include <iostream>
#include "Cpu.hpp"

int main(int ac, char **av)
{
  Cpu cpu;

  try
    {
      std::string file;

      if (ac == 1)
	{
	  file = "";
	  cpu.execute(file);
	  return (0);
	}
      for (int i=1;i < ac;i++)
	{
	  file = av[i];
	  cpu.execute(file);
	}
      return (0);
    }
  catch (Exception &e)
    {
      std::cerr << "Error: " << e.what() << " in " << e.where() << std::endl;
      return (1);
    }
}
