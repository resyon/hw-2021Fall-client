
#ifndef SimpleClient_hpp
#define SimpleClient_hpp

#include <utility>

#include "./DemoApiClient.hpp"
#include "dto/DocDto.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"
#include "dto/LendRecordDto.hpp"

class SimpleClient {
private:
  constexpr static const char* TAG = "SimpleClient";
  std::shared_ptr<DemoApiClient> client;
public:

    explicit SimpleClient(std::shared_ptr<DemoApiClient> client): client(std::move(client)){}

    oatpp::Object<UserDto> userLogin(const oatpp::String& username, const oatpp::String& password);

    oatpp::Object<UserDto> userAdd(const std::shared_ptr<UserDto>& user);

    oatpp::Object<DocsPageDto> docList(const oatpp::Int32& limit, const oatpp::Int32& offset);

    oatpp::Object<DocDto> userDocList(const oatpp::Int32& userId, const oatpp::Int32& docId);

    oatpp::Object<StatusDto> upload(oatpp::String filePath);

    void download(oatpp::String url, oatpp::String localPath);

    oatpp::Object<DocDto> docPost(const std::shared_ptr<DocDto>& doc);

    oatpp::Object<LendRecordDto> applyDoc(const oatpp::Int32& userId, const oatpp::Int32& docId);

    oatpp::Object<StatusDto> processApply(const oatpp::Int32& docId, const oatpp::Int32& toStatus);

    oatpp::Object<LendRecordsPageDto> getRecordByUserId(const oatpp::Int32& userId);

    oatpp::Object<LendRecordsPageDto> getALlRecord(const oatpp::Int32 &limit, const oatpp::Int32 &offset);

/**
 * Client call error.
 */
class Error : public std::runtime_error {
private:
    oatpp::String m_message;
    v_int32 m_httpErrorCode{};
public:

    /**
     * Constructor.
     * @param message - error message.
     * @param httpErrorCode - http error code.
     */
    Error(const oatpp::String& message, v_int32 httpErrorCode)
            :std::runtime_error(message->c_str())
            , m_message(message)
    {}

    explicit Error(const std::shared_ptr<oatpp::web::protocol::http::incoming::Response>& resp):
    std::runtime_error(resp->readBodyToString()), m_message(resp->readBodyToString())
    {}

    /**
     * Get error message.
     * @return - &id:oatpp::String;.
     */
    oatpp::String& getMessage() {
        return m_message;
    }

    /**
     * Get http error code.
     * @return - http error code.
     */
    v_int32 getHttpErrorCode() const {
        return m_httpErrorCode;
    }

};
};

#endif /* SimpleClient_hpp */
