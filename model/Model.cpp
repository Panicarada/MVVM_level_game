
//Model.cpp


#include"Model.h"
#include <QDebug>

Model::Model() noexcept
    : m_map(QSharedPointer<Map>::create()),
      ice_person(QSharedPointer<Person>::create(m_map, ICE)),
      fire_person(QSharedPointer<Person>::create(m_map, FIRE))
{
    ice_person->set_pos(QPoint(30, 733)); // 设置冰人初始位置
    fire_person->set_pos(QPoint(30, 600)); // 火人初始位置


    // 绑定person发射的信号
    QObject::connect(ice_person.data(), &Person::diamond_notification, this, [&](const int& id){
//        qDebug() << "ice signal sented, id = " << id;
        emit this->diamond_notification_model(id);
    });

    QObject::connect(fire_person.data(), &Person::diamond_notification, this, [&](const int& id){
//        qDebug() << "fire signal sented, id = " << id;
        emit this->diamond_notification_model(id);
    });

    // 绑定机关发射的信号
    QObject::connect(m_map.data(), &Map::lifting_platform_notification, this, [&](const int& id, const QPointF& pos, const movable_item_status& status)
    {
//        qDebug() << "platform signal sented, id = " << id;
        emit this->lifting_platform_notification(id, pos, status);
    });
    QObject::connect(m_map.data(), &Map::trigger_lever_notification, this, [&](const int& id, const double& angle, const movable_item_status& status)
    {
//        qDebug() << "level signal sented, id = " << id;
        emit this->trigger_lever_notification(id, angle, status);
    });

    // 绑定池水发射的游戏状态改变的信号
    QObject::connect(ice_person.data(), &Person::change_game_status_notification, this, [&](const GameStatus& status){
//        qDebug() << "ice person change game status signal sented";
        emit this->change_game_status_notification(status);
    });

    QObject::connect(fire_person.data(), &Person::change_game_status_notification, this, [&](const GameStatus& status){
//        qDebug() << "fire person change game status signal sented";
        emit this->change_game_status_notification(status);
    });

}


void Model::set_speed(double v_x, double v_y, PersonType &&type) noexcept
{
    if (type == PersonType::ICE)
    { // 设置冰人速度
        ice_person->set_speed(QPoint(int(v_x), int(v_y)));
    }
    else
    { // 设置火人速度
        fire_person->set_speed(QPoint(int(v_x), int(v_y)));
    }
}

void Model::set_speed_x(double v_x, PersonType &&type) noexcept
{
    if (type == PersonType::ICE)
    {
        ice_person->set_speed_x(std::move(v_x));
    }
    else
    {
        fire_person->set_speed_x(std::move(v_x));
    }
}

void Model::set_speed_y(double v_y, PersonType &&type) noexcept
{
    if (type == PersonType::ICE)
    {
        ice_person->set_speed_y(std::move(v_y));
    }
    else
    {
        fire_person->set_speed_y(std::move(v_y));
    }
}

const QPointF Model::get_pos(PersonType &&type) noexcept
{
    if (type == PersonType::ICE)
    {
        return ice_person->get_pos();
    }
    else
    {
        return fire_person->get_pos();
    }
}

const QPointF Model::get_speed(PersonType &&type) noexcept
{
    if (type == PersonType::ICE)
    {
        return ice_person->get_speed();
    }
    else
    {
        return fire_person->get_speed();
    }
}

const bool &Model::isAerial(PersonType &&type) noexcept
{
    if (type == PersonType::ICE)
    {
        return ice_person->isAerial();
    }
    else
    {
        return fire_person->isAerial();
    }
}


void Model::Move() noexcept
{
    ice_person->move();
    fire_person->move();
}




