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

static CAtkRoot * root = NULL;

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


int main(int argc, char **argv) {

	setup_atk_util();

	int bridge = atk_bridge_adaptor_init (&argc, &argv);

	if(bridge)
		printf ("Initialized\n");
	else
		printf ("Not Initialized\n");
	atk_bridge_adaptor_cleanup();
	return 0;

}
