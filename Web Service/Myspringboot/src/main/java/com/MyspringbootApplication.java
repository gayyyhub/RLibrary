package com;

import com.alibaba.fastjson.serializer.SerializerFeature;
import com.alibaba.fastjson.support.config.FastJsonConfig;
import com.alibaba.fastjson.support.spring.FastJsonHttpMessageConverter;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.http.HttpMessageConverters;
import org.springframework.context.annotation.Bean;

//声明该类是一个SpringBoot引导类
@SpringBootApplication
public class MyspringbootApplication{
    //run() 用来 运行Spring boot的引导类，run的参数就是spring boot引导类的字节码对象
    public static void main(String[] args) {
        SpringApplication.run(MyspringbootApplication.class, args);
    }

    @Bean
    public HttpMessageConverters fastjsonHttpMessageConverter(){
        //创建fastjson对象
        FastJsonHttpMessageConverter converter = new FastJsonHttpMessageConverter();

        FastJsonConfig config = new FastJsonConfig();
        //设置是否需要格式化
        config.setSerializerFeatures(SerializerFeature.PrettyFormat);
        converter.setFastJsonConfig(config);
        return new HttpMessageConverters(converter);
    }
}
