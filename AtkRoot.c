/*
 * AtkRoot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include "AtkRoot.h"

struct _CAtkRootAccessiblePrivate
{
  GList *obj_list;
};

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRootAccessible, c_atk_root_accessible, ATK_TYPE_OBJECT)

enum {
  PROP_0,
  N_PROPS
};

static void
c_atk_root_accessible_initialize (AtkObject *accessible,
                                    gpointer   data)
{
  ATK_OBJECT_CLASS (c_atk_root_accessible_parent_class)->initialize (accessible, data);

  accessible->role = ATK_ROLE_APPLICATION;
  accessible->accessible_parent = NULL;
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
  AtkObjectClass *class = ATK_OBJECT_CLASS(klass);
  GObjectClass *g_object_class = G_OBJECT_CLASS(klass);

  class->initialize = c_atk_root_accessible_initialize;
  class->get_n_children = c_atk_root_accessible_get_n_children;
  class->ref_child = c_atk_root_accessible_ref_child;
  class->get_parent = NULL;
  class->get_name = c_atk_root_accessible_get_name;

  g_object_class->finalize = c_atk_root_accessible_object_finalize;
}

static void
remove_child (CAtkRootAccessible *toplevel,
              AtkObject             *obj)
{
  AtkObject *atk_obj = ATK_OBJECT (toplevel);
  GList *l;
  guint obj_count = 0;
  AtkObject *child;

  if (toplevel->priv->obj_list)
    {
	  AtkObject *tmp_obj;

      for (l = toplevel->priv->obj_list; l; l = l->next)
        {
    	  tmp_obj = ATK_OBJECT (l->data);

          if (obj == tmp_obj)
            {
              /* Remove the window from the obj_list & emit the signal */
              toplevel->priv->obj_list = g_list_delete_link (toplevel->priv->obj_list, l);
              child = obj;
              g_signal_emit_by_name (atk_obj, "children-changed::remove",
                                     obj_count, child, NULL);
              atk_object_set_parent (child, NULL);
              break;
            }

          obj_count++;
        }
    }
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
c_atk_root_accessible_init (CAtkRootAccessible *toplevel)
{
  AtkObject *obj;
  GList *l;
  guint signal_id;

  toplevel->priv = c_atk_root_accessible_get_instance_private (toplevel);

  l = toplevel->priv->obj_list = g_list_alloc();

  while (l)
    {
      obj = ATK_OBJECT (l->data);
      if (!obj ||
          atk_object_get_parent (obj))
        {
          GList *temp_l  = l->next;

          toplevel->priv->obj_list = g_list_delete_link (toplevel->priv->obj_list, l);
          l = temp_l;
        }
      else
        {
          g_signal_connect_swapped (G_OBJECT (obj), "destroy",
                                    G_CALLBACK (remove_child), toplevel);
          l = l->next;
        }
    }

  g_type_class_ref (ATK_TYPE_OBJECT);

  signal_id  = g_signal_lookup ("show", ATK_TYPE_OBJECT);
  g_signal_add_emission_hook (signal_id, 0,
                              show_event_watcher, toplevel, (GDestroyNotify) NULL);

  signal_id  = g_signal_lookup ("hide", ATK_TYPE_OBJECT);
  g_signal_add_emission_hook (signal_id, 0,
                              hide_event_watcher, toplevel, (GDestroyNotify) NULL);
}

GList *
gtk_toplevel_accessible_get_children (CAtkRootAccessible *accessible)
{
  return accessible->priv->obj_list;
}

static void
c_atk_root_init (CAtkRoot *self)
{
}


