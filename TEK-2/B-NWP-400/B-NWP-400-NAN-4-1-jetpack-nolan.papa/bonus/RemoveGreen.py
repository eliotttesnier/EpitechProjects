##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-jetpack-nolan.papa
## File description:
## RemoveGreen
##

import sys
import os
from PIL import Image
import glob

def remove_green_screen(image_path, output_path=None, tolerance=60):
    """
    Remove green screen from an image and make those pixels transparent.

    Args:
        image_path (str): Path to the input image
        output_path (str, optional): Path where the processed image will be saved.
                                    If not provided, overwrite the original image
        tolerance (int): How much variation from pure green to tolerate (0-255)

    Returns:
        bool: True if successful, False otherwise
    """
    try:
        img = Image.open(image_path).convert("RGBA")
        pixel_data = img.getdata()

        new_data = []

        for item in pixel_data:
            r, g, b, a = item

            if g > r + tolerance and g > b + tolerance:
                new_data.append((r, g, b, 0))
            else:
                new_data.append(item)

        img.putdata(new_data)

        if output_path is None:
            output_path = image_path
        img.save(output_path)

        return True

    except Exception as e:
        print(f"Error processing image {image_path}: {str(e)}")
        return False

def process_folder(folder_path, tolerance=60):
    """
    Process all PNG images in a folder to remove green screen.

    Args:
        folder_path (str): Path to the folder containing PNG images
        tolerance (int): How much variation from pure green to tolerate

    Returns:
        int: Number of successfully processed images
    """
    try:
        if not os.path.exists(folder_path):
            raise FileNotFoundError(f"Folder not found: {folder_path}")

        png_files = glob.glob(os.path.join(folder_path, "*.png"))

        if not png_files:
            print(f"No PNG files found in {folder_path}")
            return 0

        print(f"Found {len(png_files)} PNG files to process")
        successful_count = 0

        for i, image_path in enumerate(png_files):
            print(f"Processing image {i+1}/{len(png_files)}: {os.path.basename(image_path)}", end="... ")
            if remove_green_screen(image_path, None, tolerance):
                print("Done")
                successful_count += 1
            else:
                print("Failed")

        print(f"Finished processing. {successful_count}/{len(png_files)} images processed successfully.")
        return successful_count

    except Exception as e:
        print(f"Error processing folder: {str(e)}")
        return 0

def print_usage():
    """Print usage information for the script"""
    print("Usage: python RemoveGreen.py <folder_path> [tolerance]")
    print("  folder_path: Path to the folder containing PNG images")
    print("  tolerance (optional): How much variation from pure green to tolerate (0-255, default: 60)")

def main():
    """Main function to handle command-line arguments"""
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)

    folder_path = sys.argv[1]

    tolerance = int(sys.argv[2]) if len(sys.argv) > 2 else 60

    process_folder(folder_path, tolerance)

if __name__ == "__main__":
    main()
