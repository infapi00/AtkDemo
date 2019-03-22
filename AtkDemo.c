/*
 * AtkDemo.c
 *
 *  Created on: Mar 21, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <stdlib.h>
#include <atk-bridge.h>

int main(int argc, char **argv) {

	int bridge=atk_bridge_adaptor_init (&argc, &argv);
	if(bridge)
		printf("Initialized\n",&bridge);
	else
		printf("Not Initialized\n",&bridge);
	//atk_bridge_adaptor_cleanup();
	return 0;

}
