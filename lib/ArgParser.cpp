#include "ArgParser.h"

namespace ArgumentParser {

ArgParser::ArgParser(std::string parser_name) : parser_name_(parser_name) {};

bool ArgParser::Parse(std::vector<std::string> args) {
  FindPositional();
  for (int i = 1; i < args.size(); ++i) {
    if (args[i].substr(0, 1) == "-") {
      if (args[i].substr(0, 2) == "--") {
        int equality_symbol_index = args[i].find('=');
        if (args[i].substr(2, equality_symbol_index - 2) == help_.GetLongName()) {
          help_flag_ = true;
          return true;
        }
        if (equality_symbol_index < args[i].length()) {
          FillLongArgument(args[i], "string", equality_symbol_index);
          FillLongArgument(args[i], "int", equality_symbol_index);  
        } else {
          FillLongArgument(args[i], "flag", args[i].length() + 1);
        }

      } else {
        int equality_symbol_index = args[i].find('=');
        if (args[i][1] == help_.GetShortName() && args[i].length() == 2) {
          help_flag_ = true;
          return true;
        }
        if (equality_symbol_index < args[i].length()) {
          if (equality_symbol_index != 2) {
            return false;
          }
          FillShortArgument(args[i], "string", equality_symbol_index);
          FillShortArgument(args[i], "int", equality_symbol_index);
        } else {
          if (!FillShortArgument(args[i], "flag", equality_symbol_index)) {
            ParsePositional(args[i]);
          }
        }
      }

    } else {
      ParsePositional(args[i]); 
    }
  }
  return CheckParsed();
}

bool ArgParser::Parse(int argc, char** argv) {
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.push_back(std::string(argv[i]));
  }
  return Parse(args);
}

StringArgument& ArgParser::AddStringArgument(char short_name, std::string long_name, std::string description) {
  string_arguments_.emplace_back(short_name, long_name, description);
  return string_arguments_.back();
}

StringArgument& ArgParser::AddStringArgument(std::string long_name, std::string description) {
  string_arguments_.emplace_back(long_name, description);
  return string_arguments_.back();
}

StringArgument& ArgParser::AddStringArgument(char short_name, std::string long_name) {
  string_arguments_.emplace_back(short_name, long_name);
  return string_arguments_.back();
}

StringArgument& ArgParser::AddStringArgument(std::string long_name) {
  string_arguments_.emplace_back(long_name);
  return string_arguments_.back();
}

IntArgument& ArgParser::AddIntArgument(char short_name, std::string long_name, std::string description) {
  int_arguments_.emplace_back(short_name, long_name, description);
  return int_arguments_.back();
}

IntArgument& ArgParser::AddIntArgument(std::string long_name, std::string description) {
  int_arguments_.emplace_back(long_name, description);
  return int_arguments_.back();
}

IntArgument& ArgParser::AddIntArgument(char short_name, std::string long_name) {
  int_arguments_.emplace_back(short_name, long_name);
  return int_arguments_.back();
}

IntArgument& ArgParser::AddIntArgument(std::string long_name) {
  int_arguments_.emplace_back(long_name);
  return int_arguments_.back();
}

FlagArgument& ArgParser::AddFlag(char short_name, std::string long_name, std::string description) {
  flag_arguments_.emplace_back(short_name, long_name, description);
  return flag_arguments_.back();
}

FlagArgument& ArgParser::AddFlag(std::string long_name, std::string description) {
  flag_arguments_.emplace_back(long_name, description);
  return flag_arguments_.back();
}

FlagArgument& ArgParser::AddFlag(char short_name, std::string long_name) {
  flag_arguments_.emplace_back(short_name, long_name);
  return flag_arguments_.back();
}

FlagArgument& ArgParser::AddFlag(std::string long_name) {
  flag_arguments_.emplace_back(long_name);
  return flag_arguments_.back();
}

void ArgParser::AddHelp(char short_name, std::string long_name, std::string description) {
  description_ = description;
  help_ = StringArgument(short_name, long_name, description);
}

void ArgParser::AddHelp(std::string long_name, std::string description) {
  description = description_;
  help_ = StringArgument(long_name, description);
}

void ArgParser::AddHelp(char short_name, std::string long_name) {
  description_ = "No description provided.";
  help_ = StringArgument(short_name, long_name);
}

void ArgParser::AddHelp(std::string long_name) {
  description_ = "No description provided.";
  help_ = StringArgument(long_name);
}

std::string ArgParser::GetStringValue(std::string long_name) {
  for (StringArgument i : string_arguments_) {
    if (i.GetLongName() == long_name) {
      return i.GetValue();
    }
  }
  throw std::invalid_argument("Given argument doesn't exist.");
}

int ArgParser::GetIntValue(std::string long_name) {
  for (IntArgument i : int_arguments_) {
    if (i.GetLongName() == long_name) {
      return i.GetValue();
    }
  }
  throw std::invalid_argument("Given argument doesn't exist.");
}

int ArgParser::GetIntValue(std::string long_name, int index) {
  for (IntArgument i : int_arguments_) {
    if (i.GetLongName() == long_name) {
      return i.GetValue(index);
    }
  }
  throw std::invalid_argument("Given argument doesn't exist.");
}

bool ArgParser::GetFlag(std::string long_name) {
  for (FlagArgument i : flag_arguments_) {
    if (i.GetLongName() == long_name) {
      return i.GetValue();
    }
  }
  throw std::invalid_argument("Given argument doesn't exist.");
}

bool ArgParser::HelpDescription() {
  std::cout << parser_name_ << '\n' << description_ << "\n\n";
  for (FlagArgument i : flag_arguments_) {
    std::cout << i.GetHelp() << '\n';
  }
  for (IntArgument i : int_arguments_) {
    std::cout << i.GetHelp() << '\n';
  }
  for (StringArgument i : string_arguments_) {
    std::cout << i.GetHelp() << '\n';
  }
  if (help_.GetShortName() != '\0'){
    std::cout << '-' << help_.GetShortName() << ",\t--" << help_.GetLongName() << ",\tDisplay help and exit.\n";
  } else {
    std::cout << "--" << help_.GetLongName() << ",\tDisplay help and exit.\n";
  }
  return true;
}

bool ArgParser::Help() {
  return help_flag_;
}

ArgParser::~ArgParser() {};

bool ArgParser::CheckParsed() {
  for (StringArgument i : string_arguments_) {
    if (!i.IsParsed()) {
      return false;
    }
  }
  for (IntArgument i : int_arguments_) {
    if (!i.IsParsed()) {
      return false;
    }
  }
  return true;
}

void ArgParser::FillLongArgument(std::string& arg, std::string type, int equality_symbol_index) {
  if (type == "string") {
    for (StringArgument& j : string_arguments_) {
      if (arg.substr(2, equality_symbol_index - 2) == j.GetLongName()) {
        j.SetValue(arg.substr(equality_symbol_index + 1));
        j.Parsed();
      }
    }
  } else if (type == "int") {
    for (IntArgument& j : int_arguments_) {
      if (arg.substr(2, equality_symbol_index - 2) == j.GetLongName()) {
        j.SetValue(std::stoi(arg.substr(equality_symbol_index + 1)));
        j.Parsed();
      }
    } 
  } else if (type == "flag") {
    for(FlagArgument& j : flag_arguments_) {
      if (arg.substr(2, equality_symbol_index - 2) == j.GetLongName()) {
        j.SetValue(j.GetValue() ^ 1);
      }
    }
  } else {
    throw std::invalid_argument("Incorrect argument type.");
  }
}

bool ArgParser::FillShortArgument(std::string& arg, std::string type, int equality_symbol_index) {
  if (type == "string") {
    for (StringArgument& j : string_arguments_) {
      if (arg[1] == j.GetShortName()) {
        j.SetValue(arg.substr(equality_symbol_index + 1));
        j.Parsed();
      }
    }
    return true;
  } else if (type == "int") {
    for (IntArgument& j : int_arguments_) {
      if (arg[1] == j.GetShortName()) {
        j.SetValue(std::stoi(arg.substr(equality_symbol_index + 1)));
        j.Parsed();
      }
    }
    return true;
  } else if (type == "flag") {
    for (int i = 1; i < arg.length(); ++i) {
      bool parsed = false;
      for(FlagArgument& j : flag_arguments_) {
        if (arg[i] == j.GetShortName()) {
          parsed = true;
          j.SetValue(j.GetValue() ^ 1);
        }
      }
      if (!parsed) {
        return false;
      }
    }
    return true;
  } else {
    throw std::invalid_argument("Incorrect argument type.");
  }
  return false;
}

void ArgParser::FindPositional() {
  for (int i = 0; i < string_arguments_.size(); ++i) {
    if (string_arguments_[i].IsPositional()) {
      positional_index_ = i;
      positional_type_ = 's';
    }
  }
  if (positional_type_ != 's') {
    for (int i = 0; i < int_arguments_.size(); ++i) {
      if (int_arguments_[i].IsPositional()) {
        positional_index_ = i;
        positional_type_ = 'i';
      }
    }
  }
}

void ArgParser::ParsePositional(std::string argument) {
  if (positional_type_ == 'c') {
    string_arguments_[positional_index_].SetValue(argument);
    string_arguments_[positional_index_].Parsed();
  } else if (positional_type_ == 'i') {
    int_arguments_[positional_index_].SetValue(std::stoi(argument));
    int_arguments_[positional_index_].Parsed();
  } else {
    throw std::invalid_argument("Incorrect input.");
  }
}

}