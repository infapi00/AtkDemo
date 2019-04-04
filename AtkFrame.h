/*
 * AtkFrame.h
 *
 *  Created on: Apr 4, 2019
 *      Author: giuseppe
 */

#ifndef ATKFRAME_H_
#define ATKFRAME_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_FRAME            (c_atk_frame_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkFrame, c_atk_frame, C, ATK_FRAME, AtkObject)

struct _CAtkFrameClass
{
  AtkObjectClass parent_class;

};

CAtkFrame *c_atk_frame_new (void);

G_END_DECLS

#endif /* ATKFRAME_H_ */
