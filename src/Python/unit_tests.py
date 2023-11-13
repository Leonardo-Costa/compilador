import os
from funcs import openFile, readFile, listFiles, printLine
from compile import runProgram

root = "../../data/lexer/"

RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
RESET = "\033[0m"


def compareOutput(expectedOutput, givenOutput, filePath):
    expected_lines = expectedOutput.strip().split("\n")
    given_lines = givenOutput.strip().split("\n")

    for i, (expected_line, given_line) in enumerate(
        zip(expected_lines, given_lines), start=1
    ):
        if expected_line != given_line:
            printLine(RED)
            print(
                f"{RED}ERRO NA LINHA {YELLOW}{i}{RED} DO ARQUIVO {YELLOW}{filePath}{RED}!{RESET}\n"
            )
            print(f"{MAGENTA}ESPERADO: {expected_line}{RESET}")
            print(f"{MAGENTA}OCORRIDO: {given_line}{RESET}")
            printLine(RED)

            return False

    printLine(GREEN)
    print(f"{GREEN}ARQUIVO {filePath.split('/')[-1]} PROCESSADO COM SUCESSO!{RESET}")
    printLine(GREEN)

    return True


def unitTest(filePath, givenOutputString):
    print(f"{BLUE}OUTPUT {YELLOW}{filePath}{RESET}")
    try:
        with openFile(filePath) as file:
            expectedOutputString = readFile(file)
        return compareOutput(expectedOutputString, givenOutputString, filePath)
    except Exception as e:
        print(f"{RED}ERRO: {e}{RESET}")
        return False


def runBatch():
    for file in listFiles(root + "input/"):
        if file.endswith(".cm"):
            print(f"\n{BLUE}INPUT {YELLOW}{file}{RESET}")
            result = runProgram(file)
            if not unitTest(f"{root}output/{file.split('.')[0]}.txt", result):
                return False

