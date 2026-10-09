//
// Created by Cezar on 27.05.2025.
//

#ifndef ACTION_H
#define ACTION_H
#include "../Domain/Tutorial.h"
#include "../Repository/Repo.h"

class Action {
public:
    Action(){};
    virtual ~Action(){};
    virtual void executeUndo()=0;
    virtual void executeRedo()=0;
};

class ActionAdd: public Action{
private:
    Tutorial addedTutorial;
    Repo &repo;
public:
    ActionAdd(Tutorial tutorial, Repo &repository_n): addedTutorial{tutorial}, repo{repository_n}{};
    ~ActionAdd(){};
    void executeUndo() override;
    void executeRedo() override;
};

class ActionRemove: public Action{
private:
    Tutorial deletedTutorial;
    Repo& repo;
public:
    ActionRemove(Tutorial tutorial, Repo& repository_n): deletedTutorial{tutorial}, repo{repository_n}{};
    ~ActionRemove(){};
    void executeUndo() override;
    void executeRedo() override;

};


class ActionUpdate: public Action{
private:
    Tutorial oldTutorial;
    Tutorial newTutorial;
    Repo& repo;
public:
    ActionUpdate(Tutorial otutorial,Tutorial ntutorial, Repo& repository_n): oldTutorial{otutorial},newTutorial{ntutorial}, repo{repository_n}{};
    ~ActionUpdate(){};
    void executeUndo() override;
    void executeRedo() override;

};

#endif //ACTION_H
