<?php
namespace app\index\controller;
use app\common\model\Klass;        // 班级
use app\common\model\Teacher;
use think\Request;
class KlassController extends IndexController
{
    public function index()
    {
        //获取查询信息
        $name = input('get.name');

        $pageSize = 2;  //每页显示2条数据

        $Klass = new Klass;

        //定制查询信息
        if (!empty($name)) {
            $Klass->where('name', 'like', '%' . $name . '%');
        }

        //按条件查询数据并分页
        $klasses = $Klass->paginate($pageSize, false, [
            'query' =>[
            'name' => $name,
            ],
        ]);
        $this->assign('klasses', $klasses);
        return $this->fetch();
    }
    public function add() 
    {
        // 获取所有教师信息
        $teachers = Teacher::all();
        $this->assign('teachers', $teachers);
        return $this->fetch();
    }       

    public function save()
    {
        // 实例化求信息
        $Request = Request::instance();

        // 实例化班级并赋值
        $Klass = new Klass();
        $Klass->name = $Request->post('name');
        $Klass->teacher_id = $Request->post('teacher_id/d');

        // 添加数据
        if (!$Klass->validate(true)->save()) {
            return $this->error('数据添加错误' . $Klass->getError());
        }

        return $this->success('操作成功' . url('index'));
    }

    public function edit()
    {
        $id = Request::instance()->param('id/d');

        // 获取所有教师信息
        $teachers = Teacher::all();
        $this->assign('teachers', $teachers);

        // 获取用户操作班级信息
        $Klass = Klass::get($id);

        if(false === $Klass)
        {
            return $this->error('系统未找到ID为' . $id . '的记录');
        }
        
        $this->assign('Klass', $Klass);

        return $this->fetch();
    }

    public function update()
    {
        $id = Request::instance()->post('id\d');

        // 获取班级信息
        $Klass = Klass::get($id);
        if (is_null($Klass)) {
            return $this->error('系统未找到ID为' . $id . '的记录');
        }

        // 数据更新
        $Klass->name = Request::instance()->post('name');
        $Klass->teacher_id = Request::instance()->post('teacher_id/d');
        if (!$Klass->validate()->save()) {
            return $this->error('更新错误：' . $Klass->getError());
        } else {
            return $this->success('操作成功', url('index'));
        }
    }

    public function delete()
    {
        // 获取删除的id
        $id = Request::instance()->param('id/d');

        if (is_null($id) || 0 === $id) {
            return $this->error('未获取得到信息');
        }

        // 获取要删除的元素
        $Klass = Klass::get($id);

        // 删除对象不存在
        if (is_null($Klass)) {
            return $this->error('不存在id为' . $id . '的学生，删除失败');
        }

        // 删除对象
        if (!$Klass->delete()) {
            return $this->error('删除失败' . $Klass->getError());
        }

        return $this->success('删除成功', url('index'));
    }
}