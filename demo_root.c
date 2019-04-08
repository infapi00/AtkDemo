/*
 * AtkRoot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include "demo_root.h"

#include <gmodule.h>

#define C_ATK_ROOT_GET_PRIVATE(o) (c_atk_root_get_istance_private (o))

typedef struct
{
	GList * accessibleObjects;

	guint obj_added_id;
	guint obj_removed_id;

} CAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, ATK_TYPE_OBJECT)

static void
c_atk_add_obj(CAtkRootPrivate *priv, AtkObject *obj, gpointer data)
{
	CAtkRoot *root = C_ATK_ROOT(data);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (root));

	priv->accessibleObjects = g_list_append (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);
	g_signal_emit_by_name (root, "children_changed::add", index, obj, NULL);

}

static void
c_atk_remove_obj(CAtkRootPrivate *priv, AtkObject *obj, gpointer data)
{
	CAtkRoot *root = C_ATK_ROOT(data);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (root));

	priv->accessibleObjects = g_list_remove (priv->accessibleObjects, obj);

	index = g_list_index (priv->accessibleObjects, obj);

	g_signal_emit_by_name (root, "children_changed::remove", index, obj, NULL);
}



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

   atk_object_initialize (ATK_OBJECT(root), NULL);

   return root;
}

static void
c_atk_root_initialize (AtkObject *self, gpointer null)
{
	const GList *iter = NULL;
	const GSList *obj_list = NULL;
	AtkObject *child = NULL;
	CAtkRoot * root= NULL;

	atk_object_set_role(self, ATK_ROLE_APPLICATION);
	atk_object_set_parent(self, NULL);

	root = C_ATK_ROOT(self);
	CAtkRootPrivate *priv = c_atk_root_get_instance_private(root);
	obj_list = priv->accessibleObjects;

	for (iter = obj_list; iter != NULL; iter = g_list_next (iter))
	    {
	      child = ATK_OBJECT(iter->data);

	      atk_object_set_parent (child, ATK_OBJECT (root));

	      priv->accessibleObjects = g_list_append (priv->accessibleObjects, child);

	    }

	  priv->obj_added_id = g_signal_connect (G_OBJECT (priv), "obj-added", G_CALLBACK (c_atk_add_obj), root);

	  priv->obj_removed_id = g_signal_connect (G_OBJECT (priv), "obj-removed", G_CALLBACK (c_atk_remove_obj), root);

}

static gint
c_atk_root_get_n_children (AtkObject *obj)
{
  CAtkRootPrivate *priv = c_atk_root_get_instance_private(C_ATK_ROOT(obj));
  return g_list_length (priv->accessibleObjects);
}

static AtkObject*
c_atk_root_ref_child (AtkObject *obj,
                     gint i)
{
  CAtkRoot *root = NULL;
  GList *obj_list = NULL;
  gint num = 0;
  AtkObject *item = NULL;

  root = C_ATK_ROOT(obj);
  CAtkRootPrivate *priv = c_atk_root_get_instance_private(root);
  obj_list = priv->accessibleObjects;
  num = g_list_length (obj_list);

  g_return_val_if_fail ((i < num)&&(i >= 0), NULL);

  item = g_list_nth_data (obj_list, i);
  if (!item)
    {
      return NULL;
    }

  g_object_ref (item);

  return item;
}


static void
c_atk_root_finalize (GObject *object)
{
	CAtkRoot *root = C_ATK_ROOT(object);

	g_return_if_fail (C_IS_ATK_ROOT(object));

	CAtkRootPrivate *priv = c_atk_root_get_instance_private(root);

	if (priv->accessibleObjects)
	{
	  g_list_free (priv->accessibleObjects);
	  priv->accessibleObjects = NULL;
	}

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
  atk_class->ref_child = c_atk_root_ref_child;
  //add methods
  object_class->finalize = c_atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
	CAtkRootPrivate *priv = c_atk_root_get_instance_private(self);
	priv->accessibleObjects = NULL;
	priv->obj_added_id = 0;
	priv->obj_added_id = 0;
}

