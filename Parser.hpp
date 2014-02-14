#ifndef PARSER_H_
# define PARSER_H_

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <stdlib.h>
# include "Operand.hpp"
# include "Exception.hpp"

typedef struct			s_param_instrc
{
  std::string			instrc;
  IOperand			*operand;
}				t_param_instrc;

class				Parser
{
private:
  int				indexInstrc;
  std::vector<std::string>	listGrammarInsctr;
  std::vector<std::string>	listGrammarType;
  std::vector<std::string>	listInsctr;
  void				readInstruction(const std::string &file);
  void				readInstruction();
  void				initGrammar();
  bool				parseGrammarInstrc();
  bool				parseGrammarType(std::string &instrc);
  int				numberArgInstrc(std::string &instrc);
  bool				checkFormatArguement(std::string &instrc);
  eOperandType			getTypeArgument(std::string &instrc);
public:
  Parser();
  ~Parser();
  bool			        checkInstrc();
  void				displayInstr();
  t_param_instrc		*getNextInstrc();
  void				setInput(std::string &file);
  void				setInput();
};


#endif // PARSER
