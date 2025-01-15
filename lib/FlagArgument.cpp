#include "FlagArgument.h"

FlagArgument::FlagArgument(char short_name, std::string long_name, std::string description) 
  : short_name_(short_name), long_name_(long_name), 
  description_("-" + std::string(1, short_name_) + ",\t--" + long_name_ + ",\t" + description) {};

FlagArgument::FlagArgument(std::string long_name, std::string description) 
  : long_name_(long_name), description_("--" + long_name_ + ",\t" + description) {};

FlagArgument::FlagArgument(char short_name, std::string long_name) 
  : short_name_(short_name), long_name_(long_name), 
  description_("-" + std::string(1, short_name_) + ",\t--" + long_name_ + ",\tNo description provided.") {};

FlagArgument::FlagArgument(std::string long_name) 
  : long_name_(long_name), description_("--" + long_name_ + ",\tNo description provided.") {};

void FlagArgument::SetValue(bool value) {
  value_ = value;
  if (stored_value_) {
    *stored_value_ = value;
  }
}

void FlagArgument::Default(bool value) {
  value_ = value;
  if (stored_value_){
    *stored_value_ = value;
  }
  std::string string_value = (value) ? "true" : "false";
  description_ += "[default = " + string_value + "]";
}

void FlagArgument::StoreValue(bool& value) {
  stored_value_ = &value;
}

char FlagArgument::GetShortName() {
  return short_name_;
}

std::string FlagArgument::GetLongName() {
  return long_name_;
}

bool FlagArgument::GetValue() {
  return value_;
}

std::string FlagArgument::GetHelp() {
  return description_;
}

FlagArgument::~FlagArgument() {};