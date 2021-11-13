#include "SimpleClient.hpp"
#include <sys/wait.h>
#include <fstream>

oatpp::Object<UserDto> SimpleClient::userLogin(const oatpp::String &username, const oatpp::String &password) {
   auto resp = client->doUserLogin(username, password);
   if(resp->getStatusCode() != 200) {
      throw Error("[POST] /user/login: " + resp->readBodyToString(), resp->getStatusCode());
   }
    auto user = resp->readBodyToDto<oatpp::Object<UserDto>>(client->getObjectMapper());
    return user;
}

oatpp::Object<UserDto> SimpleClient::userAdd(const std::shared_ptr<UserDto>& user) {
    auto resp = client->doUserAdd(user);
    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    auto ret =  resp->readBodyToDto<oatpp::Object<UserDto>>(client->getObjectMapper());
    return ret;
}

oatpp::Object<DocsPageDto> SimpleClient::docList(const oatpp::Int32 &limit, const oatpp::Int32 &offset) {
    auto resp = client->doDocList(offset, limit);
    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<DocsPageDto>>(client->getObjectMapper());
}

oatpp::Object<StatusDto> SimpleClient::upload(oatpp::String filePath) {
    std::string cmd = std::string{"/usr/local/bin/curl -X POST -F'file=@"} + filePath->c_str()  + "'  " + client->getUrlPrefix() + "/upload > ./tmp.out";
    if(fork() == 0){
        execlp("/usr/bin/bash", "/usr/bin/bash", "-c", cmd.c_str(), NULL);
    }
    wait(nullptr);
    std::ifstream f{"./tmp.out"};
    if(!f.is_open()) {
        throw Error("file may be not exist", 400);
    }
    std::string body;
    f>>body;
    return client->getObjectMapper()->readFromString<oatpp::Object<StatusDto>>(body);
}

void SimpleClient::download(oatpp::String url, oatpp::String localPath) {
    std::string cmd = std::string{"/usr/local/bin/curl -X GET "} + url->c_str() + " > " + localPath->c_str();
    if(fork() == 0){
        execlp("/usr/bin/bash", "/usr/bin/bash", "-c", cmd.c_str(), NULL);
    }
    wait(nullptr);
}

oatpp::Object<DocDto> SimpleClient::docPost(const std::shared_ptr<DocDto>& doc) {
   auto resp = client->doDocPost(doc);

    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<DocDto>>(client->getObjectMapper());
}


oatpp::Object<LendRecordDto>  SimpleClient::applyDoc(const oatpp::Int32& userId, const oatpp::Int32& docId) {
    auto resp = client->doLendRecordPost(userId, docId);

    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<LendRecordDto>>(client->getObjectMapper());
}


oatpp::Object<StatusDto> SimpleClient::processApply(const oatpp::Int32& applyId, const oatpp::Int32& toStatus) {
    auto resp = client->doLendRecordPut(applyId, (toStatus == 1 ? "LEND": "REJECT"));

    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<StatusDto>>(client->getObjectMapper());

}

oatpp::Object<LendRecordsPageDto> SimpleClient::getRecordByUserId(const oatpp::Int32 &userId) {
    auto resp = client->doLendRecordUser(userId);
    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<LendRecordsPageDto>>(client->getObjectMapper());
}

oatpp::Object<LendRecordsPageDto> SimpleClient::getALlRecord(const oatpp::Int32 &limit, const oatpp::Int32 &offset) {
    auto resp = client->doLendRecordList(offset, limit);
    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<LendRecordsPageDto>>(client->getObjectMapper());
}

oatpp::Object<DocDto> SimpleClient::userDocList(const oatpp::Int32 &userId, const oatpp::Int32 &docId) {
    auto resp = client->doDocGet(docId, userId);

    if(resp->getStatusCode() != 200) {
        throw Error(resp->readBodyToString(), resp->getStatusCode());
    }
    return resp->readBodyToDto<oatpp::Object<DocDto>>(client->getObjectMapper());
}
