#pragma once
#include <iostream>
#include <vector>

class IntArgument {

public:

  IntArgument(char short_name, std::string long_name, std::string description);

  IntArgument(std::string long_name, std::string description);

  IntArgument(char short_name, std::string long_name);

  IntArgument(std::string long_name);

  IntArgument(const IntArgument &) = default;

  IntArgument& MultiValue(int min_args);

  IntArgument& MultiValue();

  IntArgument& Positional();

  void SetValue(int value);

  void Parsed();

  void Default(int value);

  void StoreValue(int& value);

  void StoreValues(std::vector<int>& values);

  char GetShortName();

  std::string GetLongName();

  int GetValue(int index);

  int GetValue();

  bool IsParsed();

  bool IsPositional();

  std::string GetHelp();

  ~IntArgument();

private:
  bool parsed_ = false;
  bool multi_value_ = false;
  bool positional_ = false;
  char short_name_ = '\0';
  std::string long_name_;
  std::string description_;
  int value_;
  int* stored_value_ = nullptr;
  int min_args_ = 0;
  int curr_args_;
  std::vector<int> values_;
  std::vector<int>* stored_values_ = nullptr;
};