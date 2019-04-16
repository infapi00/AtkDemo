/*
 * demo_actor.h
 *
 *  Created on: Apr 14, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_ACTOR_H_
#define DEMO_ACTOR_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_ACTOR            (c_atk_actor_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkActor, c_atk_actor, C, ATK_ACTOR, AtkObject)

struct _CAtkActorClass
{
  AtkObjectClass parent_class;

};

void c_atk_actor_add_child (CAtkActor *actor, AtkObject *obj);

void c_atk_actor_remove_child (CAtkActor *actor, AtkObject *obj);

void c_atk_actor_add_state (CAtkActor *actor, AtkStateType state);

void c_atk_actor_remove_state (CAtkActor *actor, AtkStateType state);

void c_atk_actor_add_attribute (CAtkActor *actor, AtkAttribute *attribute);

void c_atk_actor_remove_attribute (CAtkActor *actor, AtkAttribute *attribute);

G_END_DECLS

#endif /* DEMO_ACTOR_H_ */