import subprocess

sourceRoot = "..\\C\\"
executableName = "main"
inputRoot = "..\\..\\data\\lexer\\input\\"
inputFile = "teste.c"

RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
RESET = "\033[0m"


def compileProgram(sourceRoot=sourceRoot, executableName=executableName):
    try:
        compile_command = f"gcc {sourceRoot}main.c {sourceRoot}funcs.c {sourceRoot}lexer/lexer.c -o {executableName}.exe"
        subprocess.run(compile_command, shell=True, check=True)
        print(
            f"{BLUE}COMPILADO COM {GREEN}SUCESSO!{BLUE} EXECUTÁVEL {YELLOW}'{executableName}.exe'{BLUE} CRIADO.{RESET}"
        )
    except subprocess.CalledProcessError:
        print("{RED}Erro de compilação falhou.{RESET}")


def runProgram(inputFile=inputFile, executableName=executableName):
    try:
        completedProcess = subprocess.run(
            f"./{executableName} {inputRoot + inputFile}",
            capture_output=True,
            text=True,
        )
        output = completedProcess.stdout + completedProcess.stderr
        return output
    except FileNotFoundError:
        print(f"Executável '{executableName}.exe' não encontrado.")
