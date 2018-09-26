package com.mengyunzhi.SpringMvc.config;

import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;

@Component
public class WebMvcConfig {
    // 声明一个Bean，SpringMVC在启动的时候，会自动的扫描Bean，并按这个Bean的配置进行一些配置
    @Bean
    public WebMvcConfigurer corsConfigurer() {
        return new WebMvcConfigurerAdapter() {
            @Override
            public void addCorsMappings(CorsRegistry registry) {
                //添加一个映射
                //此映射允许进行CORS的地址为：http://localhost:9000
                registry.addMapping("/**").allowedOrigins("http://localhost:9000")
                        .allowedMethods("OPTIONS", "GET", "PUT", "POST", "PATCH", "DELETE");
            }
        };
    }

//    @Configuration
//    public class WebConfig {
//        /**
//         * 添加h2控制台的映射地址
//         * @return
//         * @author 河北工业大学梦云智开发团队 panjie
//         */
//        @Bean
//        ServletRegistrationBean h2servletRegistration(){
//            ServletRegistrationBean registrationBean = new ServletRegistrationBean( new WebServlet());
//            registrationBean.addUrlMappings("/h2-console/*");
//            return registrationBean;
//        }
//    }
}
