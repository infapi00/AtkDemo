/*
 * AtkRoot.h
 *
 *  Created on: Mar 27, 2019
 *      Author: giuseppe
 */


#ifndef _C_ATK_ROOT_H_
#define _C_ATK_ROOT_H_

#include <atk/atk.h>

/*old code
G_BEGIN_DECLS


#define C_TYPE_ATK_ROOT (c_atk_root_get_type())

G_DECLARE_DERIVABLE_TYPE (CAtkRoot, c_atk_root, C, ATK_ROOT, AtkObject)



struct _CAtkRootClass
{
  AtkObjectClass parent_class;

};

CAtkRoot *c_atk_root_new (void);

G_END_DECLS

*/

G_BEGIN_DECLS

G_DECLARE_DERIVABLE_TYPE (CAtkRoot, c_atk_root, C, ATK_ROOT, GObject)

#define C_TYPE_ATK_ROOT_ACCESSIBLE               (c_atk_root_accessible_get_type ())
#define C_ATK_ROOT_ACCESSIBLE(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), C_TYPE_ATK_ROOT_ACCESSIBLE, CAtkRootAccessible))
#define C_ATK_ROOT_ACCESSIBLE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), C_TYPE_ATK_ROOT_ACCESSIBLE, CAtkRootAccessibleClass))
#define C_IS_ATK_ROOT_ACCESSIBLE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), C_TYPE_ATK_ROOT_ACCESSIBLE))
#define C_IS_ATK_ROOT_ACCESSIBLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), C_TYPE_ATK_ROOT_ACCESSIBLE))
#define C_ATK_ROOT_ACCESSIBLE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), C_TYPE_ATK_ROOT_ACCESSIBLE, CAtkRootAccessibleClass))

typedef struct _CAtkRootAccessible        CAtkRootAccessible;
typedef struct _CAtkRootAccessibleClass   CAtkRootAccessibleClass;
typedef struct _CAtkRootAccessiblePrivate CAtkRootAccessiblePrivate;

struct _CAtkRootAccessible
{
  AtkObject parent;

  CAtkRootAccessiblePrivate *priv;
};

struct _CAtkRootAccessibleClass
{
  AtkObjectClass parent_class;
};

GType  c_atk_root_get_type     (void);

GType  c_atk_root_accessible_get_type     (void);

GList *c_atk_root_accessible_get_children (CAtkRootAccessible *accessible);

G_END_DECLS

#endif /* ATKROOT_H_ */
