#!/usr/bin/env python3

import json
import tkinter as tk
from PIL import Image, ImageTk
import sys

map_data = {
    "startPosP1": {"x": "0.0", "y": "0.0"},
    "startPosP2": {"x": "0.0", "y": "0.0"},
    "endPosP1": {"x": "0.0", "y": "0.0"},
    "endPosP2": {"x": "0.0", "y": "0.0"},
    "sky": "sky_path",
    "blocks": [],
}

available_blocks = [
    {
        "type": "B_map",
        "texture": "./assets/blocks/B.png"
    },
    {
        "type": "T1_map",
        "texture": "./assets/blocks/T1.png"
    },
    {
        "type": "T2_map",
        "texture": "./assets/blocks/T2.png"
    },
    {
        "type": "T3_map",
        "texture": "./assets/blocks/T3.png"
    },
    {
        "type": "T4_map",
        "texture": "./assets/blocks/T4.png"
    }
]

block_size = 20
grid_width = 40  # In blocks
grid_height = 30  # In blocks

window = tk.Tk()

if len(sys.argv) > 1:
    with open(sys.argv[1], "r") as f:
        map_data = json.load(f)

    for block in map_data["blocks"]:
        image = Image.open(block["texture"])
        image = image.resize((block_size, block_size))
        block['image'] = ImageTk.PhotoImage(image)
        # Create a semi-transparent version of the block
        image = image.copy()
        image.putalpha(200)
        block['image_hover'] = ImageTk.PhotoImage(image)

for block in available_blocks:
    image = Image.open(block["texture"])
    image = image.resize((block_size, block_size))
    block['image'] = ImageTk.PhotoImage(image)
    # Create a semi-transparent version of the block
    image = image.copy()
    image.putalpha(200)
    block['image_hover'] = ImageTk.PhotoImage(image)

# Open a window to create a map
window.title("Map Creator")
window.geometry(
    str(grid_width * block_size + 200) + "x" + str(grid_height * block_size))

# Create a canvas to draw the map on the left
canvas = tk.Canvas(window, width=grid_width * block_size + 200,
                   height=grid_height * block_size)
canvas.pack(side=tk.LEFT)


# Create a button to save the map
def save_map():
    # Copy the map data to a new dictionary without the images
    map_data_copy = map_data.copy()
    for block in map_data_copy["blocks"]:
        if "image" in block:
            block.pop("image")
        if "image_hover" in block:
            block.pop("image_hover")
    with open("map.json", "w") as f:
        # Pretty print the JSON
        json.dump(map_data_copy, f, indent=4)
    window.destroy()


save_button = tk.Button(window, text="Save", command=save_map)
# Place the button on the bottom right
save_button.place(x=grid_width * block_size + 50,
                  y=grid_height * block_size - 50)


# Create a button to exit the map creator
def exit_map_creator():
    window.destroy()


exit_button = tk.Button(window, text="Exit", command=exit_map_creator)
# Place the button on the bottom right
exit_button.place(x=grid_width * block_size + 50,
                  y=grid_height * block_size - 100)

picked_block: {
    "type": str,
    "texture": str,
    "image": ImageTk.PhotoImage,
    "image_hover": ImageTk.PhotoImage
} = None


# Listen for mouse clicks
def mouse_click(event):
    x = event.x
    y = event.y
    # Round to the nearest grid block
    x = round(x / block_size) * block_size
    y = round(y / block_size) * block_size
    # If outside the grid, we use the block picker
    global picked_block
    if x >= grid_width * block_size:
        for _i, _block in enumerate(available_blocks):
            _block_x = grid_width * block_size + (_i % (200 // block_size)) * block_size
            _block_y = (_i // (200 // block_size)) * block_size
            if x >= _block_x and x < _block_x + block_size and y >= _block_y and y < _block_y + block_size:
                picked_block = _block
                return
        return
    # If a block is picked, place it
    if picked_block is not None:
        map_data["blocks"].append(
            {"pos": {"x": str(x // block_size) + ".0" , "y": str(y // block_size) + ".0"}, "type": picked_block["type"], "texture": picked_block["texture"], "data": {}, "image": picked_block["image"]})
        return


# Listen for ctrl + z to undo the last block
def undo(event):
    if len(map_data["blocks"]) > 0:
        block = map_data["blocks"].pop()
        x = block["x"]
        y = block["y"]
        canvas.create_rectangle(x, y, x + block_size, y + block_size,
                                fill="white")


# Bind the undo function to the window
window.bind("<Control-z>", undo)
window.bind("<Button-1>", mouse_click)

while True:
    # if close the window
    if window.winfo_exists() == 0:
        break
    # Draw the grid
    canvas.create_rectangle(0, 0, grid_width * block_size + 200,
                            grid_height * block_size, fill="white")
    for i in range(grid_width):
        canvas.create_line(i * block_size, 0, i * block_size,
                           grid_height * block_size, fill="gray")
    for i in range(grid_height):
        canvas.create_line(0, i * block_size, grid_width * block_size,
                           i * block_size, fill="gray")

    # Draw map data
    for block in map_data["blocks"]:
        canvas.create_image(float(block["pos"]["x"]) * block_size, float(block["pos"]["y"]) * block_size,
                            image=block["image"], anchor=tk.NW)

    mouse_x = window.winfo_pointerx() - window.winfo_rootx()
    mouse_y = window.winfo_pointery() - window.winfo_rooty()
    x = round(mouse_x / block_size) * block_size
    y = round(mouse_y / block_size) * block_size
    # Draw a red hollow rectangle to show where the block will be placed
    canvas.create_rectangle(x, y, x + block_size, y + block_size, outline="red")
    # Draw a semi-transparent version of the picked block
    if picked_block is not None:
        canvas.create_image(x, y,
                            image=picked_block["image_hover"], anchor=tk.NW)

    block_x = 0
    block_y = 0
    # Draw the list of available blocks on the right
    for i, block in enumerate(available_blocks):
        canvas.create_image(grid_width * block_size + block_x,
                            block_y, image=block["image"], anchor=tk.NW)
        block_x += block_size
        if block_x >= 200:
            block_x = 0
            block_y += block_size

    canvas.update()
    window.update()
