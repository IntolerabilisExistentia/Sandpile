#include <iostream>
#include <lib/ArgParser.h>
#include <lib/Sandpile.h>

int main (int argc, char *argv[]) {
  ArgumentParser::ArgParser parser("Sandpile BMP Generator");
  parser.AddHelp('h', "help", "A console program that generates a BMP image representation of the Abelian sandpile model.");
  parser.AddStringArgument('i', "input", "A tsv file containing the starting amount of particles in particular cell.\n\t\t\t\tFormat x \\t y\\t particles")
    .Default("../Default.tsv");
  parser.AddStringArgument('o', "output", "Save directory for the files.").Default("../output/");
  parser.AddIntArgument('m', "max-iter", "A maximum amount of iterations of the model.").Default(10000);
  parser.AddIntArgument('f', "freq", "\tFrequency of saving. For example in case of 5, each 5 iteratons will be generated.\n\t\t\t\tIn case of 0, onlu the final result will be saved.").Default(0);
  parser.Parse(argc, argv);
  if (parser.Help()) {
    std::cout << parser.HelpDescription() << '\n';
    return 0;
  }
  std::string tsv = parser.GetStringValue("input");
  std::string output = parser.GetStringValue("output");
  Sandpile s(tsv, parser.GetIntValue("max-iter"), parser.GetIntValue("freq"));
  s.CreateField();
  s.Collapse(output);
  std::cout << "Generation finished.\n";
  return 0;
}