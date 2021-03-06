#pragma once
//Move_command


#ifndef _MOVECOMMAND_H
#define _MOVECOMMAND_H

#include"./common/commands.h"


template <class ViewModel>
class Move_command :public Commands
{
public:
    Move_command(QSharedPointer<ViewModel> vm) { m_VM = vm; }
    void exec() override
    {
        m_VM->Exec_move_command();
    }
private:
    QSharedPointer<ViewModel> m_VM;
};

#endif // !_MOVECOMMAND_H
