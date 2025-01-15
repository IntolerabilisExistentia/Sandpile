#pragma once
#include <iostream>
#include <string>

class FlagArgument {

public:

  FlagArgument(char short_name, std::string long_name, std::string description);

  FlagArgument(std::string longName, std::string description);

  FlagArgument(char short_name, std::string long_name);

  FlagArgument(std::string longName);

  FlagArgument(const FlagArgument &) = default;

  void SetValue(bool value);

  void Default(bool value);

  void StoreValue(bool& value);

  char GetShortName();

  std::string GetLongName();

  bool GetValue(); 

  std::string GetHelp();

  ~FlagArgument();

private:
  char short_name_ = '\0';
  std::string long_name_;
  std::string description_;
  bool value_ = false;
  bool* stored_value_ = nullptr;
};