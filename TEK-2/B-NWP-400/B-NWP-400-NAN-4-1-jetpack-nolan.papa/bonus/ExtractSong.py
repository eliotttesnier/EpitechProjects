##
## EPITECH PROJECT, 2025
## B-NWP-400-NAN-4-1-jetpack-nolan.papa
## File description:
## ExtractSong
##

import sys
import os
from moviepy import VideoFileClip

def extract_audio(video_path, output_path=None):
    """
    Extract audio from a video file and save it as a WAV file.

    Args:
        video_path (str): Path to the video file
        output_path (str, optional): Path where the audio will be saved.
                                    If not provided, uses the video filename with .wav extension

    Returns:
        str: Path to the generated audio file
    """
    try:
        if not os.path.exists(video_path):
            raise FileNotFoundError(f"Video file not found: {video_path}")

        if output_path is None:
            base_name = os.path.splitext(os.path.basename(video_path))[0]
            output_path = os.path.join(os.path.dirname(video_path), f"{base_name}.wav")

        video = VideoFileClip(video_path)
        audio = video.audio
        audio.write_audiofile(output_path)

        video.close()

        print(f"Audio extracted successfully to: {output_path}")
        return output_path

    except Exception as e:
        print(f"Error extracting audio: {str(e)}")
        return None

def print_usage():
    """Print usage information for the script"""
    print("Usage: python ExtractSong.py <video_path> [output_path]")
    print("  video_path: Path to the video file")
    print("  output_path (optional): Path where the audio will be saved")

def main():
    """Main function to handle command-line arguments"""
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)

    video_path = sys.argv[1]

    output_path = sys.argv[2] if len(sys.argv) > 2 else None

    extract_audio(video_path, output_path)

if __name__ == "__main__":
    main()

