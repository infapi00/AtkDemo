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

/*
static const gchar *
get_toolkit_name (void)
{
  return "My Root";
}

static const gchar *
get_toolkit_version (void)
{
  return atk_get_toolkit_version();
}

static AtkObject *
get_root (void)
{
  static AtkObject *root;

  if (!root)
    {
      root = g_object_new (ATK_TYPE_GOBJECT_ACCESSIBLE, NULL);
      atk_object_initialize (root, NULL);
    }

  return root;
}
*/

static void
set_root (void){
	static GObject *groot=NULL;
	static AtkObject *root=NULL;

	if(!groot){
		groot=g_object_new (ATK_TYPE_GOBJECT_ACCESSIBLE, NULL);
		root =atk_gobject_accessible_for_object(groot);
		atk_object_initialize (root, NULL);
	}
}


int main(int argc, char **argv) {

	set_root;

	int bridge = atk_bridge_adaptor_init (NULL, NULL);

	if(bridge)
		printf("Initialized\n");
	else
		printf("Not Initialized\n");
	atk_bridge_adaptor_cleanup();
	return 0;

}
