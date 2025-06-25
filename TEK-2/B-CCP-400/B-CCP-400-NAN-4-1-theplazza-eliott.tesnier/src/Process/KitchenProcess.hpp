/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** KitchenProcess
*/

#pragma once

#include <memory>
#include "../Process/Process.hpp"
#include "../Config/Config.hpp"
#include "../Kitchen/Kitchen.hpp"
#include "../IPC/IIPCChannel.hpp"

class KitchenProcess : public Process {
    public:

        KitchenProcess(const Config& config, int kitchenId);
        virtual ~KitchenProcess();

        std::shared_ptr<Kitchen> getKitchen() const;
        int getKitchenId() const;
        bool isKitchenValid() const;
        void setIpcChannel(std::shared_ptr<Plazza::IIPCChannel> channel);

    protected:
        virtual void childProcess() override;
        virtual void parentProcess() override;
        virtual void onForkFailure() override;

    private:
        Config _config;
        int _kitchenId;
        std::shared_ptr<Kitchen> _kitchen;
        std::shared_ptr<Plazza::IIPCChannel> _ipcChannel;
        void cleanupFifos();
};
