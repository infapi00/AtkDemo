/*
 * AtkRoot.c
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe

#include "AtkRoot.h"

typedef struct
{

} CAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, ATK_TYPE_OBJECT)


enum {
  PROP_0,
  N_PROPS
};

/**
 * atkroot_new:
 *
 * Create a new #AtkRoot.
 *
 * Returns: (transfer full): a newly created #AtkRoot


CAtkRoot *
c_atk_root_new (void)
{
  return g_object_new (C_TYPE_ATK_ROOT, NULL);
}

static void
atk_root_initialize(AtkObject *self, gpointer data)
{
	ATK_OBJECT_CLASS (c_atk_root_parent_class)->initialize (self, data);

	self->role = ATK_ROLE_APPLICATION;
	self->accessible_parent = NULL;

}

static void
atk_root_finalize (GObject *object)
{
  CAtkRoot *self = (CAtkRoot *)object;
  CAtkRootPrivate *priv = c_atk_root_get_instance_private (self);

  G_OBJECT_CLASS (c_atk_root_parent_class)->finalize (object);
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_GET_CLASS(klass);

  atk_class->initialize = atk_root_initialize;
  atk_class->get_parent = NULL;
  object_class->finalize = atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
}
*/
