#include "StringArgument.h"

StringArgument::StringArgument(char short_name, std::string long_name, std::string description) 
  : short_name_(short_name), long_name_(long_name), 
  description_("-" + std::string(1, short_name_) + ",\t--" + long_name_ + "=<string>,\t" + description) {};

StringArgument::StringArgument(std::string long_name, std::string description) 
  : long_name_(long_name), description_("--" + long_name_ + "=<string>,\t" + description) {};

StringArgument::StringArgument(char short_name, std::string long_name) 
  : short_name_(short_name), long_name_(long_name), 
  description_("-" + std::string(1, short_name_) + ",\t--" + long_name_ + "=<string>,\tNo description provided.") {};

StringArgument::StringArgument(std::string long_name) 
  : long_name_(long_name), description_("--" + long_name_ + "=<string>,\tNo description provided.") {};

StringArgument& StringArgument::MultiValue(int min_args) {
  multi_value_ = true;
  min_args_ = min_args;
  description_ += "[repeated, min args = " + std::to_string(min_args_) + "]";
  curr_args_ = 0;
  return *this;
}

StringArgument& StringArgument::MultiValue() {
  multi_value_ = true;
  curr_args_ = 0;
  description_ += "[repeated]";
  return *this;
}

StringArgument& StringArgument::Positional() {
  if (multi_value_) {
    positional_ = true;
    description_ += "[positional]";
    return *this;
  }
  throw std::invalid_argument("Positional argument must be multivalue.");
}

void StringArgument::SetValue(std::string value) {
  value_ = value;
  if (stored_value_) {
    *stored_value_ = value;
  }
}

void StringArgument::Parsed() {
  parsed_ = true;
}

void StringArgument::Default(std::string value) {
  value_ = value;
  if (stored_value_){
    *stored_value_ = value;
  }
  description_ += "[default = " + value + "]";
  parsed_ = true;
}

void StringArgument::StoreValue(std::string& value) {
  stored_value_ = &value;
}

void StringArgument::StoreValues(std::vector<std::string>& values) {
  stored_values_ = &values;
}

char StringArgument::GetShortName() {
  return short_name_;
}

std::string StringArgument::GetLongName() {
  return long_name_;
}

std::string StringArgument::GetValue() {
  return value_;
}

std::string StringArgument::GetValue(int index) {
  return values_[index];
}

bool StringArgument::IsParsed() {
  return parsed_;
}

bool StringArgument::IsPositional() {
  return positional_;
}

std::string StringArgument::GetHelp() {
  return description_;
}

StringArgument::~StringArgument() {};