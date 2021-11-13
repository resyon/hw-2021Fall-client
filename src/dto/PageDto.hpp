
#ifndef CRUD_PAGE_DTO_HPP
#define CRUD_PAGE_DTO_HPP

#include "UserDto.hpp"
#include "DocDto.hpp"
#include "LendRecordDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

  DTO_INIT(PageDto, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class UsersPageDto : public PageDto<oatpp::Object<UserDto>> {

  DTO_INIT(UsersPageDto, PageDto<oatpp::Object<UserDto>>)

};

class DocsPageDto : public PageDto<oatpp::Object<DocDto>> {

  DTO_INIT(DocsPageDto, PageDto<oatpp::Object<DocDto>>)

};

class LendRecordsPageDto : public PageDto<oatpp::Object<LendRecordDto>> {

    DTO_INIT(LendRecordsPageDto, PageDto<oatpp::Object<LendRecordDto>>)

};
#include OATPP_CODEGEN_END(DTO)

#endif //CRUD_PAGE_DTO_HPP
