#include "IntArgument.h"

IntArgument::IntArgument(char short_name, std::string long_name, std::string description) 
  : short_name_(short_name), long_name_(long_name), 
  description_("-" + std::string(1, short_name_) + ",\t--" + long_name_ + "=<int>,\t" + description) {};

IntArgument::IntArgument(std::string long_name, std::string description) 
  : long_name_(long_name), description_("--" + long_name_ + "=<int>,\t" + description) {};

IntArgument::IntArgument(char short_name, std::string long_name) 
  : short_name_(short_name), long_name_(long_name), 
  description_("-" + std::string(1, short_name_) + ",\t--" + long_name_ + "=<int>,\tNo description provided.") {};

IntArgument::IntArgument(std::string long_name) 
  : long_name_(long_name), description_("--" + long_name_ + "=<int>,\tNo description provided.") {};

IntArgument& IntArgument::MultiValue(int min_args) {
  multi_value_ = true;
  min_args_ = min_args;
  description_ += "[repeated, min args = " + std::to_string(min_args_) + "]";
  curr_args_ = 0;
  return *this;
}

IntArgument& IntArgument::MultiValue() {
  multi_value_ = true;
  curr_args_ = 0;
  description_ += "[repeated]";
  return *this;
}

IntArgument& IntArgument::Positional() {
  if (multi_value_) {
    positional_ = true;
    description_ += "[positional]";
    return *this;
  }
  throw std::invalid_argument("Positional argument must be multivalue.");
}

void IntArgument::SetValue(int value) {
  if (multi_value_) {
    values_.push_back(value);
    ++curr_args_;
    if (stored_values_) {
      stored_values_->push_back(value);
    }
  } else {
    value_ = value;
    if (stored_value_) {
      *stored_value_ = value;
    }
  }
}

void IntArgument::Parsed() {
  if (multi_value_) {
    if (curr_args_ >= min_args_) {
      parsed_ = true;
    }
  } else { 
    parsed_ = true;
  }
}

void IntArgument::Default(int value) {
  value_ = value;
  if (stored_value_){
    *stored_value_ = value;
  }
  description_ += "[default = " + std::to_string(value) + "]";
  parsed_ = true;
}

void IntArgument::StoreValue(int& value) {
  stored_value_ = &value;
}

void IntArgument::StoreValues(std::vector<int>& values) {
  stored_values_ = &values;
}

char IntArgument::GetShortName() {
  return short_name_;
}

std::string IntArgument::GetLongName() {
  return long_name_;
}

int IntArgument::GetValue() {
  return value_;
}

int IntArgument::GetValue(int index) {
  return values_[index];
}

bool IntArgument::IsParsed() {
  return parsed_;
}

bool IntArgument::IsPositional() {
  return positional_;
}

std::string IntArgument::GetHelp() {
  return description_;
}

IntArgument::~IntArgument() {};