#ifndef DemoApiClient_hpp
#define DemoApiClient_hpp

#include <oatpp/parser/json/mapping/Serializer.hpp>
#include <utility>
#include "DemoApiModels.hpp"
#include "dto/UserDto.hpp"
#include "dto/DocDto.hpp"
#include "dto/LendRecordDto.hpp"

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

class DemoApiClient : public oatpp::web::client::ApiClient {
#include OATPP_CODEGEN_BEGIN(ApiClient)

  API_CLIENT_INIT(DemoApiClient)
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper>  m_objectMapper = nullptr;
    std::string urlPrefix;
public:
    [[nodiscard]] std::shared_ptr<oatpp::data::mapping::ObjectMapper> getObjectMapper() const {
        return m_objectMapper;
    }
    void setObjectMapper(std::shared_ptr<oatpp::data::mapping::ObjectMapper> objectMapper)  {
       this->m_objectMapper = std::move(objectMapper);
    }

    void setUrlPrefix(std::string prefix) {
        this->urlPrefix = std::move(prefix);
    }
    std::string getUrlPrefix() {
        return this->urlPrefix;
    }

//  user add

    API_CALL("GET", "user/login", doUserLogin, QUERY(String, name, "name"), QUERY(String, password, "password"))
    API_CALL("POST", "user", doUserAdd, BODY_DTO(oatpp::Object<UserDto>, user))


    API_CALL("GET", "doc", doDocGet, QUERY(Int32, docId, "doc_id"), QUERY(Int32, userId, "user_id"))
    API_CALL("POST", "doc", doDocPost, BODY_DTO(oatpp::Object<DocDto>, doc))
    API_CALL("GET", "doc/list", doDocList, QUERY(Int32, offset, "offset"), QUERY(Int32, limit, "limit"))
    API_CALL("DELETE", "doc", doDocDelete, QUERY(Int32, docId, "doc_id"))

    API_CALL("POST", "lend_record", doLendRecordPost, QUERY(Int32, userId, "user_id"), QUERY(Int32, docId, "doc_id"))
    API_CALL("PUT", "lend_record", doLendRecordPut, QUERY(Int32, recordId, "record_id"), QUERY(String , toStatus, "to_status"))
    API_CALL("GET", "lend_record/list", doLendRecordList, QUERY(Int32, offset, "offset"), QUERY(Int32, limit, "limit"))
    API_CALL("GET", "lend_record/user", doLendRecordUser, QUERY(Int32, userId, "user_id"))


#include OATPP_CODEGEN_END(ApiClient)
};

#endif /* DemoApiClient_hpp */
