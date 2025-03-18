/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-eliott.tesnier
** File description:
** myftp
*/

#ifndef MYFTP_H_
    #define MYFTP_H_

    // INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/poll.h>
    #include <signal.h>
    #include <errno.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdbool.h>
    #include <stdarg.h>

    // CONSTANTS
    #define MAX_CLIENTS 100
    #define BUFFER_SIZE 4096
    #define PATH_MAX_LEN 1024
    #define USERNAME_MAX_LEN 256

// REPLY CODES
typedef enum reply_code {
    RPL_SERVICE_READY_MIN = 120,
    RPL_DATA_CONNECTION_OPEN = 125,
    RPL_FILE_STATUS_OK = 150,
    RPL_COMMAND_OK = 200,
    RPL_HELP_MESSAGE = 214,
    RPL_SERVICE_READY = 220,
    RPL_CLOSING_CONTROL_CONNECTION = 221,
    RPL_DATA_CONNECTION_CLOSE = 226,
    RPL_PASSIVE_MODE = 227,
    RPL_LOGGED_IN = 230,
    RPL_FILE_ACTION_OK = 250,
    RPL_PATHNAME_CREATED = 257,
    RPL_USERNAME_OK = 331,
    RPL_NEED_ACCOUNT = 332,
    RPL_CANT_OPEN_DATA_CNX = 425,
    RPL_ERROR = 500,
    RPL_SYNTAX_ERROR = 501,
    RPL_NOT_IMPLEMENTED = 502,
    RPL_BAD_SEQUENCE = 503,
    RPL_NOT_LOGGED_IN = 530,
    RPL_FILE_UNAVAILABLE = 550,
} reply_code_t;

// CLIENT CONNECTION STATE
typedef enum client_state {
    CONNECTED,
    AUTHENTICATED,
    PENDING_AUTH,
} client_state_t;

// DATA TRANSFER MODE
typedef enum transfer_mode {
    NONE,
    ACTIVE,
    PASSIVE,
} transfer_mode_t;

// CLIENT STRUCTURE
typedef struct client_s {
    int control_fd;
    int data_fd;
    pid_t data_pid;
    struct sockaddr_in addr;
    char username[256];
    char current_dir[PATH_MAX_LEN];
    char complete_current_dir[PATH_MAX_LEN];
    client_state_t state;
    transfer_mode_t mode;
    struct sockaddr_in data_addr;
    int passive_listen_fd;
    char *buffer;
    char *rnfr_path;
    char *cpfr_path;
} client_t;

// SERVER STRUCTURE
typedef struct server_s {
    char root_dir[PATH_MAX_LEN];
    char complete_root_dir[PATH_MAX_LEN];
    int socket_fd;
    int port;
    struct pollfd *poll_fds;
    client_t *clients;
    int nb_clients;
} server_t;

// SHELL COMMANDS
typedef int (*command_handler_t)(server_t *serv, client_t *client, char *args);

typedef struct command_s {
    char *name;
    command_handler_t handler;
    bool need_auth;
} command_t;

//HELP COMMAND
typedef struct {
    const char *cmd;
    const char *help;
} command_help_t;

// PROTOTYPES
// Server management
int init_server(server_t *serv, int port, char *root_dir);
void run_server(server_t *serv);
void clear_server(server_t *serv);

// Client management
void add_client(server_t *serv, int fd);
void remove_client(server_t *serv, int i);
int handle_client_command(server_t *serv, client_t *client, char *cmd);
void send_reply(client_t *client, reply_code_t code, char *msg);

// Authentification
int user_command(server_t *serv, client_t *client, char *username);
int pass_command(server_t *serv, client_t *client, char *password);

// File management
int pwd_command(server_t *serv, client_t *client, char *args);
int cwd_command(server_t *serv, client_t *client, char *args);
int cdup_command(server_t *serv, client_t *client, char *args);
int dele_command(server_t *serv, client_t *client, char *args);

// Data transfer
int pasv_command(server_t *serv, client_t *client, char *args);
int port_command(server_t *serv, client_t *client, char *args);
int retr_command(server_t *serv, client_t *client, char *args);
int stor_command(server_t *serv, client_t *client, char *args);
int list_command(server_t *serv, client_t *client, char *args);

// Utils commands
int quit_command(server_t *serv, client_t *client, char *args);
int help_command(server_t *serv, client_t *client, char *args);
int noop_command(server_t *serv, client_t *client, char *args);

// Signal handling
int setup_signal_handlers(void);
void set_signal_server(server_t *server);
void handle_child_signal(server_t *serv);

// Socket management
int setup_server_socket(int port);
int init_poll_structures(server_t *serv);

// Utils
bool is_subpath(const char *parent, const char *child);
char *get_absolute_path(const char *base_path, const char *relative_path);
char *normalize_relative_path(const char *path);
bool is_valid_path(const char *root_path, const char *current_path,
    const char *new_path);
bool check_file_access(client_t *client, const char *path);
bool check_directory_access(client_t *client, const char *path);
bool is_file_path_valid(server_t *serv, client_t *client, const char *path);
bool is_file_path_existing(const char *path);
bool is_folder_path_existing(const char *path);
char *get_abs(server_t *serv, client_t *client, const char *path);
int error(const char *format, ...);

// Main
int myftp(int ac, char **av);

// Bonus commands
int mkd_command(server_t *serv, client_t *client, char *args);
int rmd_command(server_t *serv, client_t *client, char *args);
int rnfr_command(server_t *serv, client_t *client, char *args);
int rnto_command(server_t *serv, client_t *client, char *args);
int cpfr_command(server_t *serv, client_t *client, char *args);
int cpto_command(server_t *serv, client_t *client, char *args);
int size_command(server_t *serv, client_t *client, char *args);
int mdtm_command(server_t *serv, client_t *client, char *args);

#endif /* !MYFTP_H_ */
