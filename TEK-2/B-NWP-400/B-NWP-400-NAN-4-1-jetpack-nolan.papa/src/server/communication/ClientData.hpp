/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** ClientInputs
*/

#ifndef CLIENTINPUTS_HPP_
#define CLIENTINPUTS_HPP_

#include <vector>
#include <string>

typedef enum ClientInput_e {
    NONE,
    FLY,
    CHANGE_NAME
} ClientInput_t;

class ClientData
{
    private:
        std::vector<ClientInput_t> _inputs;
        std::string _name;
        bool _isFlying;
        int _id;

    public:
        ~ClientData() = default;

        bool getIsFlying() const;
        void setIsFlying(bool isFlying);

        std::string getName() const;
        void setName(std::string name);

        std::vector<ClientInput_t> getInputs() const;
        void setInputs(std::vector<ClientInput_t> inputs);
        void addInput(ClientInput_t input);

        int getId() const;
        void setId(int id);
};

#endif /* !CLIENTINPUTS_HPP_ */
