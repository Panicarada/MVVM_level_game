#pragma once
//Model.h


#ifndef _MODEL_H
#define _MODEL_H

#include"Person.h"
#include"Map.h"
#include <QObject>
#include "diamond.h"
#include "./common/Common.h"

class Model : public QObject
{
    Q_OBJECT
public:
    Model() noexcept;
    // 设置对应人物的速度
    void set_speed(double v_x, double v_y, PersonType &&type) noexcept;
    // 设置对应人物x方向的速度
    void set_speed_x(double v_x, PersonType &&type) noexcept;
    // 设置对应人物y方向的速度
    void set_speed_y(double v_y, PersonType &&type) noexcept;
    // 获取对应人物的位置
    const QPointF &get_pos(PersonType &&type) noexcept;
    // 获取对应人物的速度
    const QPointF &get_speed(PersonType &&type) noexcept;
    // 判断对应人物是否在空中
    const bool &isAerial(PersonType &&type) noexcept;
    // 间隔刷新的move函数
    void Move() noexcept;
public:
    // 接收来自Person.h，钻石被碰到时发射的信号
    void fire_diamond_notification(const Diamond& diamond);
    void ice_diamond_notification(const Diamond& diamond);
signals:
    void diamond_notification(const Diamond& diamond);

private:
    QSharedPointer<Map> m_map;
    QSharedPointer<Person> ice_person;
    QSharedPointer<Person> fire_person;
};

#endif // !_MODEL_H
