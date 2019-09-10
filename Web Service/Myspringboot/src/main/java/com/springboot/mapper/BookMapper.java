package com.springboot.mapper;

import com.springboot.domain.Book;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;


@Mapper
public interface BookMapper {
    @Select("select* from Books where Name=#{name}")
    Book select(String name);

    @Update("update Books set Shelf=#{shelf},Row=#{row},Col=#{col} WHERE Identity=#{identity}")
    void update(Book book);
}
