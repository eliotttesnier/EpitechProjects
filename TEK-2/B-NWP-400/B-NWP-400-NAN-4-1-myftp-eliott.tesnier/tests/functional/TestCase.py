##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-myftp-eliott.tesnier
## File description:
## TestCase
##

from Colors import *
import subprocess
import select
import time
import shutil

NC_PATH = shutil.which('nc') or shutil.which('netcat')
if not NC_PATH:
    print(f"{RED}Error: netcat (nc) command not found{END}")
    exit(1)

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

    def execute_client(self):
        self.input = self.input[2:]
        self.input = " ".join(self.input)
        self.input = self.input.split(";")

        server = subprocess.Popen(["./myftp", "4242", "./"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        time.sleep(0.1)

        client = subprocess.Popen([NC_PATH, "127.0.0.1", "4242"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        time.sleep(0.1)

        output = []
        for command in self.input:
            command = command.strip()
            client.stdin.write(f"{command}\r\n".encode())
            client.stdin.flush()
            time.sleep(0.1)

            # Use select for non-blocking reads
            readable, _, _ = select.select([client.stdout, client.stderr], [], [], 0.5)
            for stream in readable:
                output.append(stream.read1(1024).decode('utf-8'))

        self.real_output = "".join(output)
        self.real_output = self.real_output.replace("\n", "")
        self.real_output = self.real_output.replace("\r", "")
        self.real_value = 0

        # Cleanup
        client.terminate()
        server.terminate()
        time.sleep(0.1)
        client.kill()
        server.kill()

    def execute(self):
        if "CLIENT" in self.input:
            self.execute_client()
            return


        process = subprocess.Popen(self.input, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        process.wait(timeout=2)

        self.real_output = process.stdout.read().decode('utf-8')
        self.real_output += process.stderr.read().decode('utf-8')
        self.real_output = self.real_output.replace("\n", "")
        self.real_value = process.returncode

    def check(self):
        if ("..." in self.output):
            first = self.real_output.find("(")
            last = self.real_output.find(")")
            content = self.real_output[first + 1:last]
            self.output = self.output.replace("...", "(" + content + ")")

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
