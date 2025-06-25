#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-jetpack-nolan.papa
## File description:
## VideoCrop
##

import sys
import os
from moviepy import VideoFileClip

def print_usage():
    """Print usage information."""
    print("Usage: python VideoCrop.py <video_path> [start_time] [end_time]")
    print("  <video_path>: Path to the MP4 video file")
    print("  [start_time]: Start time in seconds (default: 0)")
    print("  [end_time]  : End time in seconds (default: end of video)")

def crop_video(video_path, start_time=0.0, end_time=None):
    """
    Crop a video from start_time to end_time

    Args:
        video_path (str): Path to the video file
        start_time (float): Start time in seconds
        end_time (float): End time in seconds (None for end of video)

    Returns:
        str: Path to the cropped video
    """
    try:
        if not os.path.isfile(video_path):
            print(f"Error: File not found - {video_path}")
            return None

        if not video_path.lower().endswith('.mp4'):
            print(f"Error: The file must be an MP4 video - {video_path}")
            return None

        video = VideoFileClip(video_path)

        if end_time is None or end_time > video.duration:
            end_time = video.duration

        if start_time < 0 or end_time < 0 or start_time >= end_time:
            print(f"Error: Invalid time range - start: {start_time}, end: {end_time}")
            video.close()
            return None

        base_name = os.path.basename(video_path)
        name_without_ext = os.path.splitext(base_name)[0]
        output_path = f"{name_without_ext}_cropped_{start_time:.2f}_{end_time:.2f}.mp4"

        print(f"Cropping video from {start_time:.2f}s to {end_time:.2f}s...")

        cropped_video = video.subclipped(start_time, end_time)

        cropped_video.write_videofile(output_path, codec="libx264", audio_codec="aac")

        cropped_video.close()
        video.close()

        print(f"Cropped video saved as {output_path}")
        return output_path

    except Exception as e:
        print(f"Error occurred: {e}")
        return None

def main():
    """Main function to process command-line arguments and crop the video."""
    if len(sys.argv) < 2 or len(sys.argv) > 4:
        print_usage()
        return 1

    video_path = sys.argv[1]
    start_time = 0.0
    end_time = None

    if len(sys.argv) >= 3:
        try:
            start_time = float(sys.argv[2])
        except ValueError:
            print(f"Error: Start time must be a number - {sys.argv[2]}")
            return 1

    if len(sys.argv) >= 4:
        try:
            end_time = float(sys.argv[3])
        except ValueError:
            print(f"Error: End time must be a number - {sys.argv[3]}")
            return 1

    result = crop_video(video_path, start_time, end_time)
    if result:
        return 0
    else:
        return 1

if __name__ == "__main__":
    sys.exit(main())
