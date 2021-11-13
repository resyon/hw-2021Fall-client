#include "CLIClient.hpp"
#include <iostream>

void CLIClient::login(){
    while(true) {
        try {
            std::string username, password;
            std::cout<<"ready to login"<<std::endl;
            std::cout<<"username:";
            std::cin >> username;
            password = getpass("password:");
            getchar();
//            OATPP_LOGD("[GET] /user/login", "<name=%s&password=%s>", username.c_str(), password.c_str())
            auto user = client->userLogin(username.c_str(), password.c_str());
            this->userInfo = user.getPtr();
            cmdSet.clear();
            if(userInfo->role != Role::USER) {
                cmdSet["login"] = std::make_shared<cmd>("login", &CLIClient::login, "login, otherwise nothing you can do");
                cmdSet["userAdd"] = std::make_shared<cmd>("userAdd <username> <email> <password>", &CLIClient::userAdd, "add user");
                cmdSet["exit"] = std::make_shared<cmd>("exit", &CLIClient::exit, "exit");
                cmdSet["help"] = std::make_shared<cmd>("help", &CLIClient::help, "show help info");
                cmdSet["docList"] = std::make_shared<cmd>("docList [offset] [limit]", &CLIClient::docList, "show docs in range");
                cmdSet["upload"] = std::make_shared<cmd>("upload <filePath>", &CLIClient::upload, "upload file");
                cmdSet["docPost"] = std::make_shared<cmd>("docPost <doc_name> <doc_url> <doc_description>", &CLIClient::docPost, "add doc entry, start with @ to upload a local file");
                cmdSet["docApproval"] = std::make_shared<cmd>("docApproval <allow|deny> <doc_id>", &CLIClient::docApproval, "approval doc access application");
                cmdSet["applyList"] = std::make_shared<cmd>("applyList", &CLIClient::applyList, "show all apply list");

            }else {
                cmdSet["login"] = std::make_shared<cmd>("login", &CLIClient::login, "login, otherwise nothing you can do");
                cmdSet["docList"] = std::make_shared<cmd>("docList [offset] [limit]", &CLIClient::docList, "show docs in range");
                cmdSet["help"] = std::make_shared<cmd>("help", &CLIClient::help, "show help info");
                cmdSet["docApply"] = std::make_shared<cmd>("docApply <doc_id>", &CLIClient::docApply, "apply to a doc access permission");
                cmdSet["exit"] = std::make_shared<cmd>("exit", &CLIClient::exit, "exit");
                cmdSet["recordList"] = std::make_shared<cmd>("recordList", &CLIClient::recordList, "get recordList created by self");
                cmdSet["docDownload"] = std::make_shared<cmd>("docDownload <doc_id> ", &CLIClient::docDownload, "doc download");
            }
            break;
        } catch (SimpleClient::Error& error) {
            std::cerr<< error.getMessage()->c_str()<<std::endl;
        }
    }
}

[[noreturn]] void CLIClient::run() {
    login();

    while(true) {
        std::cout<<userInfo->name->c_str()<< ">>>";
        std::string s;
        std::getline(std::cin, s);
        std::istringstream iss(s);

        iss >> s;
        this->inStringStream.swap(iss);
        auto entry = cmdSet.find(s);
        if(entry == cmdSet.end()) {
           std::cerr<< "command not found, type help to see usage" << std::endl;
            continue;
        }
        try{
            (this->*(entry->second->func))();
        }catch (SimpleClient::Error& error) {
            std::cerr<< error.getMessage()->c_str()<<std::endl;
        }
    }
}


void CLIClient::exit() {
    std::cout<<"you have exited"<<std::endl;
    std::exit(0);
}

void CLIClient::help() {
    for (const auto &item : cmdSet){
        std::cout<< item.second->name.c_str() << ": \n\t" << item.second->description << "\n" <<  std::endl;
    }
}

void CLIClient::userAdd() {
  std::string username, email, password;
  this->inStringStream >> username >> email >> password;
  auto user = UserDto::createShared();
  user->name = username;
  user->email = email;
  user->password = password;
  user->role = Role::USER;
  client->userAdd(user.getPtr());
}

void CLIClient::docList() {
    int offset=0, limit=10;
    if(!this->inStringStream.eof()) this->inStringStream >> offset;
    if(!this->inStringStream.eof()) this->inStringStream >> limit;
    auto list = client->docList( limit, offset);
    if(userInfo->role == Role::USER) {
        std::cout << "id  |      name        |         description       " << std::endl;
        for (const auto &item: *list.getPtr()->items) {
            printf("%d|%s|%s\n", *item->id.get(), item->name->c_str(), item->description->c_str());
        }
        return;
    }
    std::cout<<"id  |      name        |         description       |      url  "<<std::endl;
    for(const auto& item : *list.getPtr()->items){
        printf("%d|%s|%s|%s\n", *item->id.get(), item->name->c_str(), item->description->c_str(), item->url->c_str());
    }
}

void CLIClient::upload() {
    std::string file;
    this->inStringStream >> file;
    client->upload(file.c_str());
}

/**
 * docPost <doc_name> <doc_url> <doc_description>
 */
void CLIClient::docPost() {
    auto doc = DocDto::createShared();
    std::string docName, docUrl, docDesc;
    this->inStringStream >> docName >> docUrl >> docDesc;
    if(docUrl[0] == '@') {
        auto resp = client->upload(docUrl.substr(1, docUrl.length()-1));
        doc->url = resp->message;
    }else {
        doc->url = docUrl.c_str();
    }

    doc->name = docName.c_str();
    doc->description = docDesc.c_str();

    client->docPost(doc.getPtr());
}

void CLIClient::docApply() {
    int docId;
    this->inStringStream >> docId;
    client->applyDoc(this->userInfo->id, docId);
}

void CLIClient::docApproval() {
    int applyId;
    std::string action;
    this->inStringStream >> action >> applyId;
    client->processApply(applyId, action == "allow" ? 1 : 3);
}

void CLIClient::recordList() {
    auto list = client->getRecordByUserId(userInfo->id);
    std::cout<<"id  |      user_id        |         docId       |      status  "<<std::endl;
    for(const auto& item : *list.getPtr()->items){
        printf("%d|%d|%d|%s\n", *item->id.get(), *item->userID.get(), *item->docID.get(), oatpp::Enum<LendStatus>::getEntryByValue(item->status).name.std_str().c_str() );
    }
}

void CLIClient::applyList() {
    int offset=0, limit=10;
    if(!this->inStringStream.eof()) this->inStringStream >> offset;
    if(!this->inStringStream.eof()) this->inStringStream >> limit;
    auto list = client->getALlRecord(limit, offset);

    std::cout<<"id  |      user_id        |         docId       |      status  "<<std::endl;
    for(const auto& item : *list.getPtr()->items){
        auto s = "APPLY";
        if(item->status == LendStatus::LEND) {
            s = "LEND";
        }else if(item->status == LendStatus::REJECT) {
            s = "REJECT";
        }

        printf("%d|%d|%d|%s\n", *item->id.get(), *item->userID.get(), *item->docID.get(),  s);
    }
}

void CLIClient::docDownload() {
    int docId;
    std::string localPath;

    this->inStringStream >> docId;
    if(!this->inStringStream.eof())
        this->inStringStream >> localPath;

    auto entity = client->userDocList(userInfo->id, docId);
    localPath = entity->name;
    client->download(entity->url, localPath);
}
