/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <unistd.h>
#include <sys/wait.h>

class Process {
    public:
        enum class ProcessState {
            CREATED,
            RUNNING,
            TERMINATED,
            KILLED,
            FAILED
        };

        Process();
        virtual ~Process();

        Process(const Process&) = delete;
        Process& operator=(const Process&) = delete;

        bool start();
        bool isAlive() const;
        ProcessState getState() const;
        pid_t getPid() const;
        bool terminate(int timeoutMs = 5000);
        bool kill();
        bool wait(int timeoutMs = 0);
        int getExitStatus() const;
        bool isParent() const;
        bool isChild() const;

    protected:
        virtual void childProcess() = 0;
        virtual void parentProcess() = 0;
        virtual void onForkFailure() = 0;

    private:
        pid_t _pid;
        ProcessState _state;
        int _exitStatus;
        bool _isParentProcess;
        void updateState();
        bool checkStatus(int options = WNOHANG);
};

#endif // PROCESS_HPP_
