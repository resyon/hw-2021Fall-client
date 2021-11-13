#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

// 0=normal_user, 1=admin with weak power, 2=admin, 4=root
ENUM(Role, v_uint8,
     VALUE(USER, 0, "ROLE_USER"),
     VALUE(ASSISTANT, 1, "ROLE_ASSISTANT"),
     VALUE(ADMIN, 2, "ROLE_ADMIN"),
     VALUE(ROOT, 3, "ROLE_ROOT")
)

class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, userName, "username");
  DTO_FIELD(String, name, "name");
  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, password, "password");
  DTO_FIELD(String, avatar, "avatar");
  DTO_FIELD(Int32, deptID, "dept_id");
  DTO_FIELD(Enum<Role>::AsNumber, role, "role");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
