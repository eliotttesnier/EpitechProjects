##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-jetpack-nolan.papa
## File description:
## Framer
##

import sys
import os
import cv2

def extract_frames(video_path, output_dir=None, fps=10):
    """
    Extract frames from a video file and save them as PNG files at the specified FPS.

    Args:
        video_path (str): Path to the video file
        output_dir (str, optional): Directory where frames will be saved.
                                   If not provided, creates a directory based on the video filename
        fps (int): Frames per second to extract (default: 10)

    Returns:
        str: Path to the directory containing the frames
    """
    try:
        if not os.path.exists(video_path):
            raise FileNotFoundError(f"Video file not found: {video_path}")

        if output_dir is None:
            base_name = os.path.splitext(os.path.basename(video_path))[0]
            output_dir = os.path.join(os.path.dirname(video_path), base_name)

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        video = cv2.VideoCapture(video_path)

        if not video.isOpened():
            raise IOError(f"Could not open video file: {video_path}")

        # Get video properties
        original_fps = video.get(cv2.CAP_PROP_FPS)
        total_frames = int(video.get(cv2.CAP_PROP_FRAME_COUNT))
        print(f"Original video: {total_frames} frames at {original_fps} fps")

        frame_interval = max(1, round(original_fps / fps))
        estimated_frames = total_frames // frame_interval
        print(f"Extracting approximately {estimated_frames} frames at {fps} fps")

        frame_count = 0
        output_count = 0
        success = True

        while success:
            success, frame = video.read()

            if not success:
                break

            if frame_count % frame_interval == 0:
                output_path = os.path.join(output_dir, f"{output_count+1}.png")
                cv2.imwrite(output_path, frame)
                output_count += 1

                if output_count % 10 == 0:
                    print(f"Extracted {output_count} frames so far")

            frame_count += 1

        video.release()

        print(f"Frame extraction completed. {output_count} frames saved to: {output_dir}")
        print(f"Actual output rate: approximately {output_count / (total_frames / original_fps)} fps")
        return output_dir

    except Exception as e:
        print(f"Error extracting frames: {str(e)}")
        return None

def print_usage():
    """Print usage information for the script"""
    print("Usage: python Framer.py <video_path> [output_directory] [fps]")
    print("  video_path: Path to the video file")
    print("  output_directory (optional): Directory where frames will be saved")
    print("  fps (optional): Frames per second to extract (default: 10)")

def main():
    """Main function to handle command-line arguments"""
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)

    video_path = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else None
    fps = int(sys.argv[3]) if len(sys.argv) > 3 else 10

    extract_frames(video_path, output_dir, fps)

if __name__ == "__main__":
    main()
