##
## EPITECH PROJECT, 2025
## tekspice
## File description:
## tester
##

import os
import subprocess
import time

TEST_FILE = "tests/functional/tests.txt"
FILES_OUTPUT_FOLDER = "tests/functional/files_output/"

NAME_SYNTAX = "Name: "
DESC_SYNTAX = "Description: "
INPUT_SYNTAX = "Input: "
OUTPUT_SYNTAX = "Output: "
VALUE_SYNTAX = "Value: "

RED = "\033[91m"
GREEN = "\033[92m"
YELLOW = "\033[93m"
BLUE = "\033[94m"
MAGENTA = "\033[95m"
CYAN = "\033[96m"
WHITE = "\033[97m"
ORANGE = "\033[33m"
END = "\033[0m"

class TestCase:
    def __init__(self, name, desc, input, output, value):
        self.name = name
        self.desc = desc
        self.input = input
        self.output = output
        self.value = value

        self.real_output = None
        self.real_value = None

        if "FILE CONTENT - " in self.output:
            self.output = self.output.replace("FILE CONTENT - ", "")
            self.output = self.output.strip()
            with open(FILES_OUTPUT_FOLDER + self.output, "r") as file:
                self.output = file.read()
                self.output = self.output.replace("\n", "")

    def execute(self):
        process = subprocess.Popen(self.input, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        process.wait()

        self.real_output = process.stdout.read().decode('utf-8')
        self.real_output += process.stderr.read().decode('utf-8')
        self.real_output = self.real_output.replace("\n", "")
        self.real_value = process.returncode

    def check(self):
        if (self.real_output != self.output and self.output != "ANYTHING"):
            return False
        if (self.real_value != self.value):
            return False
        return True

    def displayPassed(self, int):
        print(f"{WHITE}Test {int + 1} {BLUE}|{END} {self.name}{END} {GREEN}OK ✅{END}")

    def displayFailed(self, int):
        print(f"{WHITE}Test {int + 1} | {self.name}{END} {RED}KO ❌{END}")
        print(f"    {YELLOW}Description: {END}{self.desc}")
        print(f"    {YELLOW}Expected : {RED}{self.value}{END} | {RED}{self.output}{END}")
        print(f"    {YELLOW}Got      : {RED}{self.real_value}{END} | {RED}{self.real_output}{END}")

def parseFile():
    tests = []

    with open(TEST_FILE, "r") as file:
        lines = file.readlines()

        for i in range(0, len(lines), 6):
            try:
                name = lines[i][len(NAME_SYNTAX):].strip()
                desc = lines[i + 1][len(DESC_SYNTAX):].strip()
                input = lines[i + 2][len(INPUT_SYNTAX):].strip().split()
                output = lines[i + 3][len(OUTPUT_SYNTAX):].strip()
                value = int(lines[i + 4][len(VALUE_SYNTAX):].strip())

                tests.append(TestCase(name, desc, input, output, value))
            except:
                print(f"{RED}Error: Invalid test format on line {i} {END}")

    return tests

def main():
    tests = parseFile()
    total = len(tests)
    passed = 0
    count = 0
    start_time = time.time()

    for test in tests:
        test.execute()
        if test.check():
            test.displayPassed(count)
            passed += 1
        else:
            test.displayFailed(count)
        count += 1

    end_time = time.time()
    print(f"\n{YELLOW}Synthesis: Tested: {BLUE}{total}{YELLOW}, Passed: {GREEN}{passed}{YELLOW}, Failed: {RED}{total - passed}{END}")
    print(f"{YELLOW}Time: {BLUE}{end_time - start_time:.2f}s{END}")
    if passed == total:
        return 0
    return 1

if __name__ == "__main__":
    exit(main())
