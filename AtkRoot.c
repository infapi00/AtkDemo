/*
 * AtkRoot.c
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */
#include "AtkRoot.h"

typedef struct
{

} CAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, ATK_TYPE_OBJECT)


enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

/**
 * atkroot_new:
 *
 * Create a new #AtkRoot.
 *
 * Returns: (transfer full): a newly created #AtkRoot
 */
CAtkRoot *
c_atk_root_new (void)
{
  return g_object_new (C_TYPE_ATK_ROOT, NULL);
}

static void
atk_root_initialize(AtkObject *self, gpointer null)
{
	atk_object_set_role(self, ATK_ROLE_APPLICATION);
}


static void
atk_root_finalize (GObject *object)
{
  CAtkRoot *self = (CAtkRoot *)object;
  CAtkRootPrivate *priv = c_atk_root_get_instance_private (self);

  G_OBJECT_CLASS (c_atk_root_parent_class)->finalize (object);
}

static void
atk_root_get_property (GObject    *object,
                       guint       prop_id,
                       GValue     *value,
                       GParamSpec *pspec)
{
  CAtkRoot *self = C_ATK_ROOT (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
atk_root_set_property (GObject      *object,
                       guint         prop_id,
                       const GValue *value,
                       GParamSpec   *pspec)
{
  CAtkRoot *self = C_ATK_ROOT (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_GET_CLASS(klass);

  atk_class->initialize = atk_root_initialize;
  object_class->finalize = atk_root_finalize;
  object_class->get_property = atk_root_get_property;
  object_class->set_property = atk_root_set_property;
}

static void
c_atk_root_init (CAtkRoot *self)
{
}
