#ifndef LendRecordDto_hpp
#define LendRecordDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(LendStatus, v_uint8,
     VALUE(APPLY, 0, "APPLY"),
     VALUE(LEND, 1, "LEND"),
     VALUE(RETURN, 2, "RETURN"),
     VALUE(REJECT, 3, "REJECT")
)

class LendRecordDto : public oatpp::DTO {

  DTO_INIT(LendRecordDto, DTO)

  DTO_FIELD(Int32, id, "id");

  DTO_FIELD(Int32, userID, "user_id");

  DTO_FIELD(Int32, docID, "doc_id");

  DTO_FIELD(Enum<LendStatus>::AsNumber, status, "status");

  DTO_FIELD(Int32, applyAt, "apply_at");

  DTO_FIELD(Int32, lendAt, "lend_at");

  DTO_FIELD(Int32, returnAt, "return_at");

  DTO_FIELD(Int32, grantedBy, "granted_by");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* LendRecordDto_hpp */
