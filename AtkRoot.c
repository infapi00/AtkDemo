/*
 * AtkRoot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include "AtkRoot.h"

struct _CAtkRootPrivate
{
   /* g_type_add_instance_private requires private_size > 0 */
   gint pad;
};

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
   CAtkRoot *root = g_object_new (C_ATK_TYPE_ROOT, NULL);

   atk_object_initialize(ATK_OBJECT(root), NULL);

   return root;
}

static void
c_atk_root_accessible_object_finalize (GObject *obj)
{
	CAtkRootAccessible *toplevel = C_ATK_ROOT_ACCESSIBLE (obj);

  if (toplevel->priv->obj_list)
    g_list_free (toplevel->priv->obj_list);

  G_OBJECT_CLASS (c_atk_root_accessible_parent_class)->finalize (obj);
}

static gint
c_atk_root_accessible_get_n_children (AtkObject *obj)
{
	CAtkRootAccessible *toplevel = C_ATK_ROOT_ACCESSIBLE (obj);

  return g_list_length (toplevel->priv->obj_list);
}

static AtkObject *
c_atk_root_accessible_ref_child (AtkObject *obj,
                                   gint       i)
{
  CAtkRootAccessible *toplevel;
  GList *list;
  AtkObject *atk_obj;

  toplevel = C_ATK_ROOT_ACCESSIBLE (obj);
  list = g_list_nth_data (toplevel->priv->obj_list, i);
  if (!list)
    return NULL;

  atk_obj = atk_gobject_accessible_for_object (G_OBJECT(list));

  g_object_ref (atk_obj);

  return atk_obj;
}

static const char *
c_atk_root_accessible_get_name (AtkObject *obj)
{
  return g_get_prgname ();
}

static void
c_atk_root_accessible_class_init (CAtkRootAccessibleClass *klass)
{
  /* CAtkRoot *self = (CAtkRoot *)object; */
  /* CAtkRootPrivate *priv = c_atk_root_get_instance_private (self); */

  class->initialize = c_atk_root_accessible_initialize;
  class->get_n_children = c_atk_root_accessible_get_n_children;
  class->ref_child = c_atk_root_accessible_ref_child;
  class->get_parent = NULL;
  class->get_name = c_atk_root_accessible_get_name;

  g_object_class->finalize = c_atk_root_accessible_object_finalize;
}

static const char*
c_atk_root_get_name (AtkObject *obj)
{
   return "ATK DEMO FOR THE WIN!!";
}

static gboolean
show_event_watcher (GSignalInvocationHint *ihint,
                    guint                  n_param_values,
                    const GValue          *param_values,
                    gpointer               data)
{
  CAtkRootAccessible *toplevel = C_ATK_ROOT_ACCESSIBLE (data);
  AtkObject *atk_obj = ATK_OBJECT (toplevel);
  GObject *object;
  AtkObject *objaccessible;
  gint n_children;


  object = g_value_get_object (param_values + 0);

  if (!ATK_IS_GOBJECT_ACCESSIBLE (object))
    return TRUE;

  objaccessible = ATK_OBJECT (object);
  if (atk_object_get_parent (objaccessible))
    return TRUE;

  if (atk_object_get_role (objaccessible) == ATK_ROLE_REDUNDANT_OBJECT ||
      atk_object_get_role (objaccessible) == ATK_ROLE_TOOL_TIP)
    return TRUE;

  /* Add the window to the list & emit the signal */
  toplevel->priv->obj_list = g_list_append (toplevel->priv->obj_list, objaccessible);
  n_children = g_list_length (toplevel->priv->obj_list);

  atk_object_set_parent (objaccessible, atk_obj);
  g_signal_emit_by_name (atk_obj, "children-changed::add",
                         n_children - 1, objaccessible, NULL);

  g_signal_connect_swapped (G_OBJECT(object), "destroy",
                            G_CALLBACK (remove_child), toplevel);

  return TRUE;
}

static gboolean
hide_event_watcher (GSignalInvocationHint *ihint,
                    guint                  n_param_values,
                    const GValue          *param_values,
                    gpointer               data)
{
  CAtkRootAccessible *toplevel = C_ATK_ROOT_ACCESSIBLE (data);
  GObject *object;

  object = g_value_get_object (param_values + 0);

  if (!ATK_IS_GOBJECT_ACCESSIBLE (object))
    return TRUE;

  remove_child (toplevel, ATK_OBJECT (object));

  return TRUE;
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_CLASS(klass);

  atk_class->initialize = atk_root_initialize;
  atk_class->get_name = c_atk_root_get_name;
  object_class->finalize = atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
}


