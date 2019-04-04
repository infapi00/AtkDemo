/*
 * AtkRoot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include "AtkRoot.h"
#include <gmodule.h>

typedef struct
{
	GList * accessibleObjects;

	guint obj_added_id;
	guint obj_removed_id;

} CAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, ATK_TYPE_OBJECT)


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
   CAtkRoot *root = g_object_new (C_TYPE_ATK_ROOT, NULL);

   atk_object_initialize(ATK_OBJECT(root), NULL);

   return root;
}

static void
c_atk_root_initialize(AtkObject *self, gpointer null)
{
	self->role=ATK_ROLE_APPLICATION;
	self->accessible_parent=NULL;

}

static gint
c_atk_root_get_n_children (AtkObject *obj)
{
  CAtkRoot *root = C_ATK_ROOT(obj);

  return g_list_length (root->priv->accessibleObjects);
}



static void
c_atk_root_finalize (GObject *object)
{
  G_OBJECT_CLASS (c_atk_root_parent_class)->finalize (object);
}

static const char*
c_atk_root_get_name (AtkObject *obj)
{
   return "ATK DEMO FOR THE WIN!!";
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_CLASS(klass);

  atk_class->initialize = c_atk_root_initialize;
  atk_class->get_name = c_atk_root_get_name;
  atk_class->get_n_children = c_atk_root_get_n_children;
  //add methods
  object_class->finalize = c_atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
	self->private = c_atk_root_get_istance_private(self);
	self->private->accessibleObjects=NULL;
	self->private->obj_added_id=0;
	self->private->obj_added_id=0;
}

