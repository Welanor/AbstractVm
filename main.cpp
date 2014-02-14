#include <iostream>
#include "VMachine.hpp"

int main(int ac, char **av)
{
  (void)ac;
  (void)av;

  VMachine cpu;

  cpu.run();
  return (0);
}
