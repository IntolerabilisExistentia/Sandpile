#pragma once
#include <iostream>
#include <string>
#include <vector>

class StringArgument {

public:

  StringArgument(char short_name, std::string long_name, std::string description);

  StringArgument(std::string long_name, std::string description);

  StringArgument(char short_name, std::string long_name);

  StringArgument(std::string long_name);

  StringArgument(const StringArgument &) = default;

  StringArgument& MultiValue(int min_args);

  StringArgument& MultiValue();

  StringArgument& Positional();

  void SetValue(std::string value);

  void Parsed();

  void Default(std::string value);

  void StoreValue(std::string& value);

  void StoreValues(std::vector<std::string>& values);

  char GetShortName();

  std::string GetLongName();

  std::string GetValue(int index);

  std::string GetValue();

  bool IsParsed();

  bool IsPositional();

  std::string GetHelp();

  ~StringArgument();

private:

  bool parsed_ = false;
  bool multi_value_ = false;
  bool positional_ = false;
  char short_name_ = '\0';
  std::string long_name_;
  std::string description_;
  std::string value_;
  std::string* stored_value_ = nullptr;
  int min_args_;
  int curr_args_;
  std::vector<std::string> values_;
  std::vector<std::string>* stored_values_;
};