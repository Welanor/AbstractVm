#include <iostream>
#include "VMachine.hpp"

int main(int ac, char **av)
{
  VMachine cpu;

  if (ac > 1)
      cpu.run(av[1]);
  return (0);
}
