#include <iostream>
#include "VMachine.hpp"

int main(int ac, char **av)
{
  VMachine cpu;

  cpu.run(ac - 1, &av[1]);
  return (0);
}
