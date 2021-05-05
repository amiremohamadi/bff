#include <fstream>
#include <iostream>
#include <string>

#define MAX 1000
int tape[MAX] = {0};
int ptr = 0;

void parse(std::string code, bool loop = false) {
  std::cout << "code: " << code << std::endl;
  int start, end;
  int loop_cnt = 0;

  do {
    for (int i = 0; i < code.size(); ++i) {
      int token = code[i];
      switch (token) {
      case '>':
        ptr++;
        break;
      case '<':
        ptr--;
        break;
      case '+':
        tape[ptr]++;
        break;
      case '-':
        tape[ptr]--;
        break;
      case '.':
        std::cout << (char)tape[ptr];
        break;
      case ',':
        std::cin >> tape[ptr];
        break;
      case '[':
        if (loop_cnt == 0)
          start = i;
        loop_cnt++;
        break;
      case ']':
        loop_cnt--;
        if (loop_cnt == 0) {
          end = i;
          parse(code.substr(start + 1, end - start - 1), true);
        }
        break;
      default:
        break;
      }
    }
  } while (loop && tape[ptr]);
}

void dump() {
  for (int i = 0; i < MAX; ++i) {
    std::cout << std::hex << tape[i] << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  if (argc < 1) {
    std::cerr << "invalid number of arguments\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  std::string line, code;
  while (std::getline(file, line)) {
    code += line;
  }

  parse(code);
  dump();
  return 0;
}
