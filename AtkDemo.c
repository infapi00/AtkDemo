/*
 * AtkDemo.c
 *
 *  Created on: Mar 21, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include <atk-bridge.h>

#include "AtkRoot.h"
#include "AtkFrame.h"

static CAtkRoot * root = NULL;
static CAtkFrame * frame=NULL;
static GMainLoop *mainloop;

static AtkObject *
get_root (void)
{
	if (!root){
           root = c_atk_root_new ();
	}
	return ATK_OBJECT(root);
}

const gchar *
get_toolkit_name (void)
{
  return strdup ("My ATK-UTIL");
}

static void
setup_atk_util (void)
{
  AtkUtilClass *klass;

  klass = g_type_class_ref (ATK_TYPE_UTIL);
  klass->get_root = get_root;
  klass->get_toolkit_name = get_toolkit_name;
  g_type_class_unref (klass);
}

static void
add_atk_frame(void){
	if (!root && frame){
			frame = c_atk_frame_new ();
			atk_object_add_relationship(ATK_OBJECT(root), ATK_RELATION_CONTROLLER_FOR,ATK_OBJECT(frame));
		}
}


int main(int argc, char **argv) {

	setup_atk_util();

	int init_outcome = atk_bridge_adaptor_init (&argc, &argv);

	if(init_outcome == 0){
		printf ("Initialized\n");
		add_atk_frame();
	}
	else
		printf ("Not Initialized\n");

	mainloop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (mainloop);

	atk_bridge_adaptor_cleanup();
	return 0;

}
