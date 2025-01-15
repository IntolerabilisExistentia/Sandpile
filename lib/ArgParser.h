#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "StringArgument.h"
#include "IntArgument.h"
#include "FlagArgument.h"

namespace ArgumentParser {

class ArgParser {

public:

  ArgParser(std::string parser_name);

  ArgParser(const ArgParser &) = default;

  bool Parse(int argc, char** argv);

  bool Parse(std::vector<std::string> args);

  StringArgument& AddStringArgument(char short_name, std::string long_name, std::string description);

  StringArgument& AddStringArgument(std::string long_name, std::string description);

  StringArgument& AddStringArgument(char short_name, std::string long_name);

  StringArgument& AddStringArgument(std::string long_name);

  IntArgument& AddIntArgument(char short_name, std::string long_name, std::string description);

  IntArgument& AddIntArgument(std::string long_name, std::string description);

  IntArgument& AddIntArgument(char short_name, std::string long_name);

  IntArgument& AddIntArgument(std::string long_name);

  FlagArgument& AddFlag(char short_name, std::string long_name, std::string description);

  FlagArgument& AddFlag(std::string long_name, std::string description);

  FlagArgument& AddFlag(char short_name, std::string long_name);

  FlagArgument& AddFlag(std::string long_name);

  void AddHelp(char short_name, std::string long_name, std::string description);

  void AddHelp(std::string long_name, std::string description);

  void AddHelp(char short_name, std::string long_name);

  void AddHelp(std::string long_name);

  std::string GetStringValue(std::string long_name);

  int GetIntValue(std::string long_name);

  int GetIntValue(std::string long_name, int index);

  bool GetFlag(std::string long_name);

  bool HelpDescription();

  bool Help();

  ~ArgParser();

private:
  std::string parser_name_;
  std::vector<StringArgument> string_arguments_;
  std::vector<IntArgument> int_arguments_;
  std::vector<FlagArgument> flag_arguments_;
  StringArgument help_ = StringArgument('h', "help", "");
  bool help_flag_ = false;
  std::string description_;
  int positional_index_;
  char positional_type_;

  bool CheckParsed();

  void FillLongArgument(std::string& arg, std::string type, int equality_symbol_index);

  bool FillShortArgument(std::string& arg, std::string type, int equality_symbol_index);

  void FindPositional();

  void ParsePositional(std::string argument);

};

} // namespace ArgumentParser