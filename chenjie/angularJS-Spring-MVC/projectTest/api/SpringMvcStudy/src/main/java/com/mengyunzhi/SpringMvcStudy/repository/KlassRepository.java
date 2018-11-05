package com.mengyunzhi.SpringMvcStudy.repository;


import com.mengyunzhi.SpringMvcStudy.entity.Klass;
import org.springframework.data.repository.CrudRepository;

/**
 * @author 某杰 on 2018/09/12
 * 建立一个访问klass数据表的接口
 * 指明：
 * 1.要操作的为klass数据
 * 2.Teacher数据表中主键类型是Long
 */
public interface KlassRepository extends CrudRepository<Klass, Long> {
}