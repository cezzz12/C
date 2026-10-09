//
// Created by Cezar on 27.05.2025.
//

#include "Action.h"

void ActionAdd::executeUndo() {
    this->repo.deleteRepo(this->addedTutorial);
}

void ActionAdd::executeRedo() {
    this->repo.addRepo(this->addedTutorial);
}

void ActionRemove::executeUndo() {
    this->repo.addRepo(this->deletedTutorial);
}

void ActionRemove::executeRedo() {
    this->repo.deleteRepo(this->deletedTutorial);
}

void ActionUpdate::executeUndo() {
    int pos = this->repo.returnPosition(this->newTutorial);
    this->repo.updateRepo(pos, this->oldTutorial);
}

void ActionUpdate::executeRedo() {
    int pos = this->repo.returnPosition(this->oldTutorial);
    this->repo.updateRepo(pos, this->newTutorial);
}