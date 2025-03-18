##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-myftp-eliott.tesnier
## File description:
## Utils
##

import os

def createDummyFile():
    with open("dummy.txt", "w") as file:
        file.write("This is a dummy file\n")
        file.write("It is used to test the file content feature\n")
        file.write("It is a dummy file\n")

def deleteDummyFile():
    try:
        os.remove("dummy.txt")
    except:
        pass
