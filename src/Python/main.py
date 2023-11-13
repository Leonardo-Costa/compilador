import sys
import os

from compile import compileProgram, runProgram
from funcs import listFiles
from unit_tests import runBatch

RED = '\033[31m'
GREEN = '\033[32m'
YELLOW = '\033[33m'
BLUE = '\033[34m'
MAGENTA = '\033[35m'
CYAN = '\033[36m'
RESET = '\033[0m'
inputRoot = "..\\..\\data\\lexer\\input\\"

if __name__ == "__main__":
    compileProgram()

    if "-r" in sys.argv:
        r_index = sys.argv.index("-r")
        if r_index + 1 < len(sys.argv):
            name = sys.argv[r_index + 1]
            result = runProgram(name)
            print(result)
        else:
            print(f"{RED}ERRO: Nenhum arquivo de entrada foi especificado.{RESET}")
    elif "-b" in sys.argv:
        runBatch()