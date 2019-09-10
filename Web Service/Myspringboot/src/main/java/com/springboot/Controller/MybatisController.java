package com.springboot.Controller;

import com.springboot.domain.Book;
import com.springboot.mapper.BookMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;


@RestController
public class MybatisController {

    @Autowired
    private BookMapper bookMapper;

    @RequestMapping(value = "/select",method = RequestMethod.GET,produces = "application/json;utf-8")
    public Book select(@RequestParam String name) {
        Book book = bookMapper.select(name);
        return book;
    }

    @RequestMapping(value = "/update",method = RequestMethod.POST,produces ="application/json;utf-8")
    public void  update(@RequestBody Book book){
        bookMapper.update(book);

    }
}
