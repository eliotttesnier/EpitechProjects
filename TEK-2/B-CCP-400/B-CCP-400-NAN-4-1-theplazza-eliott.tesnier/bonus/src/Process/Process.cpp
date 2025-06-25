/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Process
*/

#include "Process.hpp"
#include <signal.h>
#include <errno.h>
#include <chrono>
#include <thread>
#include <iostream>

/**
 * @brief Constructor
 */
Process::Process()
    : _pid(-1),
      _state(ProcessState::CREATED),
      _exitStatus(-1),
      _isParentProcess(true)
{
}

/**
 * @brief Virtual destructor for proper cleanup
 */
Process::~Process()
{
    if (_isParentProcess && _pid > 0 && _state == ProcessState::RUNNING) {
        terminate(1000);
        if (_state == ProcessState::RUNNING) {
            kill();
        }
    }
}

/**
 * @brief Start the process by forking
 *
 * @return true if process was started successfully, false otherwise
 */
bool Process::start()
{
    if (_state != ProcessState::CREATED) {
        return false;
    }

    _pid = fork();

    if (_pid < 0) {
        _state = ProcessState::FAILED;
        onForkFailure();
        return false;
    } else if (_pid == 0) {
        _isParentProcess = false;
        _state = ProcessState::RUNNING;
        try {
            childProcess();
        } catch (const std::exception& e) {
            std::cerr << "Child process exception: " << e.what() << std::endl;
            _exit(1);
        }
        _exit(0);
    } else {
        _isParentProcess = true;
        _state = ProcessState::RUNNING;
        parentProcess();
        return true;
    }
}

/**
 * @brief Check if the process is currently alive
 *
 * @return true if process is running, false otherwise
 */
bool Process::isAlive() const
{
    if (_pid <= 0 || !_isParentProcess) {
        return false;
    }

    if (::kill(_pid, 0) == 0) {
        return true;
    }

    return false;
}

/**
 * @brief Get the current process state
 *
 * @return Current ProcessState
 */
Process::ProcessState Process::getState() const
{
    if (_isParentProcess && _pid > 0) {
        const_cast<Process*>(this)->updateState();
    }
    return _state;
}

/**
 * @brief Get the process ID
 *
 * @return Process ID, or -1 if not started
 */
pid_t Process::getPid() const
{
    return _pid;
}

/**
 * @brief Terminate the process gracefully
 *
 * @param timeoutMs Maximum time to wait for graceful termination
 * @return true if process terminated gracefully, false otherwise
 */
bool Process::terminate(int timeoutMs)
{
    if (_pid <= 0 || !_isParentProcess || _state != ProcessState::RUNNING) {
        return false;
    }

    if (::kill(_pid, SIGTERM) != 0) {
        return false;
    }

    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - startTime).count() < timeoutMs) {
        if (checkStatus(WNOHANG)) {
            if (_state == ProcessState::TERMINATED) {
                return true;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return false;
}

/**
 * @brief Kill the process forcefully
 *
 * @return true if process was killed, false otherwise
 */
bool Process::kill()
{
    if (_pid <= 0 || !_isParentProcess) {
        return false;
    }

    if (::kill(_pid, SIGKILL) == 0) {
        _state = ProcessState::KILLED;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        checkStatus(WNOHANG);
        return true;
    }

    return false;
}

/**
 * @brief Wait for the process to finish
 *
 * @param timeoutMs Maximum time to wait (0 = wait indefinitely)
 * @return true if process finished within timeout, false otherwise
 */
bool Process::wait(int timeoutMs)
{
    if (_pid <= 0 || !_isParentProcess) {
        return false;
    }

    if (timeoutMs == 0) {
        return checkStatus(0);
    } else {
        auto startTime = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - startTime).count() < timeoutMs) {
            if (checkStatus(WNOHANG)) {
                return _state == ProcessState::TERMINATED || _state == ProcessState::KILLED;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return false;
    }
}

/**
 * @brief Get the exit status of the process
 *
 * @return Exit status, or -1 if process hasn't terminated
 */
int Process::getExitStatus() const
{
    return _exitStatus;
}

/**
 * @brief Check if this is the parent process
 *
 * @return true if this is the parent process, false if parent
 */
bool Process::isParent() const
{
    return _isParentProcess;
}

/**
 * @brief Check if this is the child process
 *
 * @return true if this is the child process, false if parent
 */
bool Process::isChild() const
{
    return !_isParentProcess;
}

/**
 * @brief Update process state by checking if it's still alive
 */
void Process::updateState()
{
    if (_pid <= 0 || !_isParentProcess) {
        return;
    }

    checkStatus(WNOHANG);
}

/**
 * @brief Internal method to check process status using waitpid
 *
 * @param options Options for waitpid (WNOHANG, etc.)
 * @return true if status was obtained, false otherwise
 */
bool Process::checkStatus(int options)
{
    if (_pid <= 0 || !_isParentProcess) {
        return false;
    }

    int status;
    pid_t result = waitpid(_pid, &status, options);

    if (result == _pid) {
        if (WIFEXITED(status)) {
            _state = ProcessState::TERMINATED;
            _exitStatus = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            _state = ProcessState::KILLED;
            _exitStatus = WTERMSIG(status);
        }
        return true;
    } else if (result == 0) {
        return false;
    } else if (result < 0) {
        if (errno == ECHILD) {
            _state = ProcessState::TERMINATED;
        }
        return false;
    }

    return false;
}
