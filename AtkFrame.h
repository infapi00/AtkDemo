/*
 * AtkFrame.h
 *
 *  Created on: Apr 4, 2019
 *      Author: giuseppe
 */

#ifndef ATKFRAME_H_
#define ATKFRAME_H_

#include <atk/atk.h>

G_BEGIN_DECLS

#define C_TYPE_ATK_FRAME            (c_atk_frame_get_type ())

/* Work around the fact that Atk does not define the auto pointer cleanup.
 * Add a check using ATK_CHECK_VERSION once fixed in Atk upstream. */
//G_DEFINE_AUTOPTR_CLEANUP_FUNC(AtkObject, g_object_unref)

G_DECLARE_DERIVABLE_TYPE(CAtkFrame, c_atk_frame, C, ATK_FRAME, AtkObject)

struct _CAtkFrameClass
{
  AtkObjectClass parent_class;

};

CAtkFrame *c_atk_frame_new (void);

G_END_DECLS

#endif /* ATKFRAME_H_ */
