![Jetpack Joyride Gameplay](https://imgs.crazygames.com/jetpack-joyride-pcp_16x9/20250121090354/jetpack-joyride-pcp_16x9-cover?metadata=none&quality=90&width=600&height=315&fit=crop "Jetpack Joyride Screenshot")

# Jetpack Joyride (Network Programming Project)

This project is a networked multiplayer clone of Jetpack Joyride, developed as part of the EPITECH B4 Network Programming module. It features a client-server architecture, real-time gameplay, and a graphical interface using SFML.

The purpose of this project is to create a server that handles all of the game's logic, and a client that runs the communication in another thread, while only handling the player's input and graphical interface.

## Features
- Multiplayer Jetpack Joyride gameplay
- Real-time server-client communication
- Custom map support
- Sound and animation effects
- Coding style checks with cpplint

## Requirements
- Linux OS
- g++ (C++17 or later)
- SFML 2.5+
- Python 3 (for some bonus scripts)
- `pip` (for installing cpplint)

## Building the Project

1. Clone the repository and enter the project directory:
   ```sh
   git clone <repo_url>
   cd jetpack
   ```
2. Build the project using the provided Makefile:
   ```sh
   make
   ```
   This will generate the `jetpack_client` and `jetpack_server` binaries in the `jetpack/` directory.

## Launching the Game

### Start the Server
Run the server with:
```sh
./jetpack_server -p <port> -m <map>
```
Example:
```sh
./jetpack_server -p 8484 -m basic.map
```

### Start the Client
Run the client with:
```sh
./jetpack_client -h <server_ip> -p <port>
```
Example:
```sh
./jetpack_client -h 127.0.0.1 -p 8484
```

You can launch multiple clients to join the same game.

## Coding Style Check

The project uses `cpplint` for C++ coding style checks.

### How to Run the Coding Style Check
1. Install `cpplint` if not already installed:
   ```sh
   pip install cpplint
   ```
2. Run the style checker script:
   ```sh
   ./styleChecker.sh
   ```
3. Check the `coding-style-cpp-reports.log` file for any style errors. If the file is not empty, there are style issues to fix.

## Bonus
- Bonus scripts and tools are available in the `bonus/` directory.

## Authors
- Alban (alban.roussee@epitech.eu)
- Eliott (eliott.tesnier@epitech.eu)
- Nolan (nolan.papa@epitech.eu)

## License
This project is for educational purposes at EPITECH.
