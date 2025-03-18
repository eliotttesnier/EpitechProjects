##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-myftp-eliott.tesnier
## File description:
## TestCase
##

from Colors import *
import subprocess

class TestCase:
    def __init__(self, name, desc, input, output, value, output_folder):
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
            with open(output_folder + self.output, "r") as file:
                self.output = file.read()
                self.output = self.output.replace("\n", "")

    def execute_tty(self):
        command_parts = " ".join(self.input).split("|")
        input_commands = command_parts[0].replace("echo", "").strip().strip('"').strip("'")

        if ";" in input_commands:
            input_commands = input_commands.split(";")
            input_commands = "\n".join(cmd.strip() for cmd in input_commands)
        program_command = command_parts[1].strip()

        process = subprocess.Popen(program_command.split(),
                                 stdin=subprocess.PIPE,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE,
                                 text=True)

        stdout, stderr = process.communicate(input=input_commands + "\n")

        self.real_output = stdout + stderr
        self.real_output = self.real_output.replace("> ", "")
        self.real_output = self.real_output.replace("\n", "")
        self.real_value = process.returncode

    def execute(self):
        if (self.input[0] == "echo"):
            self.execute_tty()
            return

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

    def displayPassed(self, index):
        print(f"{WHITE}Test {index + 1:03d} {BLUE}|{END} {self.name}{END} {GREEN}OK ✅{END}")

    def displayFailed(self, index):
        print(f"{WHITE}Test {index + 1:03d} | {self.name}{END} {RED}KO ❌{END}")
        print(f"    {YELLOW}Description: {END}{self.desc}")
        print(f"    {YELLOW}Expected : {RED}{self.value}{END} | {RED}{self.output}{END}")
        print(f"    {YELLOW}Got      : {RED}{self.real_value}{END} | {RED}{self.real_output}{END}")
