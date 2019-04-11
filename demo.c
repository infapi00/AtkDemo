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
#include "myAtk.h"

static CAtkRoot *root = NULL;
static CAtkFrame *frame = NULL;
static CAtkWindow *window = NULL;
static GMainLoop *mainloop;

static AtkObject *
get_root (void)
{
	if (!root)
		root = c_atk_root_new ();

	return ATK_OBJECT(root);
}

const gchar *
get_toolkit_name (void)
{
  return strdup ("MY ATK-UTIL");
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
	if (root && !frame)
	{
		frame = c_atk_frame_new();
		c_atk_root_add_child(root, ATK_OBJECT(frame));
		//interrogation of java object
		c_atk_frame_add_state(frame, ATK_STATE_ENABLED);
		c_atk_frame_add_state(frame, ATK_STATE_FOCUSABLE);
		c_atk_frame_add_state(frame, ATK_STATE_VISIBLE);
		c_atk_frame_add_state(frame, ATK_STATE_SHOWING);
		c_atk_frame_add_state(frame, ATK_STATE_RESIZABLE);
	}
}

static void
add_atk_window(void){
	if (frame && !window)
	{
		window = c_atk_window_new();
		c_atk_frame_add_child(frame, ATK_OBJECT(window));
	}
}


int main(int argc, char **argv) {

	setup_atk_util();

	int init_outcome = atk_bridge_adaptor_init (&argc, &argv);

	if(init_outcome == 0){
		printf ("Initialized\n");
		add_atk_frame();
		add_atk_window();
	}
	else
		printf ("Not Initialized\n");

	mainloop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (mainloop);

	atk_bridge_adaptor_cleanup();
	g_object_unref(window);
	g_object_unref(frame);
	g_object_unref(root);

	return 0;

}
