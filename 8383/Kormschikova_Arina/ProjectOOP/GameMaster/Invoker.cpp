//
//  Invoker.cpp
//  OOP
//
//  Created by Арина Кормщикова on 06.04.2020.
//  Copyright © 2020 Arina Kormschikova. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Command.h"
#include "Units.h"
#include "GameUnits.h"
#include "Map.h"
#include "GameBlock.h"
#include "Base.h"
#include "Handler.h"

#include "Invoker.h"

Invoker::Invoker(GameMap *map, FriendsUnits* units, EnemiesUnits* enemies, Base *base, int* index): map(map), units(units), enemies(enemies), base(base), index(index), death(false){
    helpMePleaseH = new HelpHandler();
    baseH = new BaseControlHandler();
    changeH = new ChangeUnitHandler();
    moveH = new MoveHandler();
    attackH = new AttackHandler();
    moveH->setNext(attackH)->setNext(changeH)->setNext(baseH)->setNext(helpMePleaseH);
   }

void Invoker::invokerCycle(char request){
    command = moveH->handle(request, map, units, enemies, base, index, &death);
    if(command != nullptr){
        command->execute();
        if(death){
            map->getBlock(units->units[(*index)]->y, units->units[(*index)]->x )->unitOnBlock = nullptr;
            units->units.pop_back();
            units->size--;
            command = baseH->handle('b', map, units, enemies, base, index, &death);
            command->execute();
        }
    }
}

