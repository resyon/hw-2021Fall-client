#ifndef CLI_Client_hpp
#define CLI_Client_hpp

#include <utility>
#include <unordered_map>
#include <sstream>

#include "SimpleClient.hpp"

class CLIClient {
private:
    std::shared_ptr<SimpleClient> client = nullptr;
    std::shared_ptr<UserDto> userInfo = nullptr;
    std::istringstream inStringStream;
    class cmd;
    std::unordered_map<std::string, std::shared_ptr<cmd>> cmdSet{};
    class cmd {
    public:
        std::string name;
        void (CLIClient::*func)();
        std::string description;
    public:
        cmd(std::string name, void(CLIClient::*func)(), std::string description):
            name(std::move(name)), func(func), description(std::move(description)){}
    };
public:
    explicit CLIClient(std::shared_ptr<SimpleClient> client): client(std::move(client)){
    }

    [[noreturn]] void run();
    void login();
    void userAdd();
    void exit();
    void help();

    void upload();
    void applyList();
    void docList();
    void docPost();
    void docApply();
    void docApproval();
    void docDownload();

    void recordList();

};

#endif
