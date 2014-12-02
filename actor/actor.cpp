#include "actor.h"
#include "dialogactor.h"


Actor::Actor()
{

}

void Actor::Play()
{
    DialogActor* actor = new DialogActor;
    actor->show();
}
