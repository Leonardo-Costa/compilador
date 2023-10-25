import subprocess
import sys
import os

c_source_file = "..\\C\\"
output_executable = "main"

def compileProgram():
    try:
        compile_command = f"gcc {c_source_file}main.c {c_source_file}funcs.c -o {output_executable}.exe"
        subprocess.run(compile_command, shell=True, check=True)
        print(f"Compilado com sucesso. Executável '{output_executable}.exe' criado.")
    except subprocess.CalledProcessError:
        print("Erro de compilação falhou.")

def runProgram():
    try:
        subprocess.run(f"./{output_executable}")
    except FileNotFoundError:
        print(f"Executável '{output_executable}.exe' não encontrado.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(1)

    compileProgram()

    if "-r" in sys.argv:
        runProgram()
