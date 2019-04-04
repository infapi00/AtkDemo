/*
 * AtkFrame.c
 *
 *  Created on: Apr 4, 2019
 *      Author: giuseppe
 */

#include "AtkFrame.h"

typedef struct
{
   /* g_type_add_instance_private requires private_size > 0 */
   gint pad;
} CAtkFramePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkFrame, c_atk_frame, ATK_TYPE_OBJECT)


/**
 * atkroot_new:
 *
 * Create a new #AtkRoot.
 *
 * Returns: (transfer full): a newly created #AtkRoot
 */
CAtkFrame *
c_atk_frame_new (void)
{
   CAtkFrame *root = g_object_new (C_TYPE_ATK_FRAME, NULL);

   atk_object_initialize(ATK_OBJECT(root), NULL);

   return root;
}

static void
c_atk_frame_initialize (AtkObject *self, gpointer null)
{
	self->role = ATK_ROLE_FRAME;
	self->accessible_parent = atk_get_root();
}


static void
c_atk_frame_finalize (GObject *object)
{
  G_OBJECT_CLASS (c_atk_frame_parent_class)->finalize (object);
}

static const char*
c_atk_frame_get_name (AtkObject *obj)
{
   return "ATK FRAME DEMO";
}

static AtkObject*
c_atk_frame_get_parent()
{
	return atk_get_root();
}

static void
c_atk_frame_class_init (CAtkFrameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_frame_initialize;
  atk_class->get_name = c_atk_frame_get_name;
  atk_class->get_parent = c_atk_frame_get_parent;
  object_class->finalize = c_atk_frame_finalize;
}

static void
c_atk_frame_init (CAtkFrame *self)
{
}


