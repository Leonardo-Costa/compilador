import os

def openFile(path):
    return open(path, "r")

def readFile(file):
    return file.read()

def listFiles(directory):
    try:
        files = os.listdir(directory)
        return files
    except Exception as e:
        print(f"An error occurred: {e}")
        return []

def printLine(color):
    print(f"{color}-------------------------------------------------------------\033[0m")