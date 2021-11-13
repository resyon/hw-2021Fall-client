#ifndef DocDto_hpp
#define DocDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DocDto : public oatpp::DTO {

  DTO_INIT(DocDto, DTO)

  DTO_FIELD(Int32, id, "id");
  DTO_FIELD(String, name, "name");
  DTO_FIELD(String, avatar, "avatar");
  DTO_FIELD(String, url, "url");
  DTO_FIELD(String, description, "description");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DocDto_hpp */
