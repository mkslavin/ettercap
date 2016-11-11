/*
    dummy -- ettercap plugin -- it does nothig !
                                only demostrates how to write a plugin !

    Copyright (C) ALoR & NaGA
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/


#include <ec.h>                        /* required for global variables */
#include <ec_plugins.h>                /* required for plugin ops */
#include <ec_hook.h>

#include <stdlib.h>
#include <string.h>

/* prototypes is required for -Wmissing-prototypes */

/* 
 * this function must be present.
 * it is the entry point of the plugin 
 */
int plugin_load(void *);

/* additional functions */
static int umsg_test_init(void *);
static int umsg_test_fini(void *);
void umsg_test_fn(struct packet_object *po);

/* plugin operations */

struct plugin_ops umsg_test_ops = { 
   /* ettercap version MUST be the global EC_VERSION */
   .ettercap_version =  EC_VERSION,                        
   /* the name of the plugin */
   .name =              "umsg_test",  
    /* a short description of the plugin (max 50 chars) */                    
   .info =              "A plugin to test a possible bug in USER_MSG",  
   /* the plugin version. */ 
   .version =           "1.0",   
   /* activation function */
   .init =              &umsg_test_init,
   /* deactivation function */                     
   .fini =              &umsg_test_fini,
};

/**********************************************************/

/* this function is called on plugin load */
int plugin_load(void *handle) 
{
   DEBUG_MSG("umsg_test plugin load function");
   /*
    *  in this fuction we MUST call the registration procedure that will set
    *  up the plugin according to the plugin_ops structure.
    *  the returned value MUST be the same as plugin_register()
    *  the opaque pointer params MUST be passed to plugin_register()
    */
   return plugin_register(handle, &umsg_test_ops);
}

/*********************************************************/

static int umsg_test_init(void *umsg_test) 
{
   /* the control is given to this function
    * and ettercap is suspended until its return.
    * 
    * you can create a thread and return immediately
    * and then kill it in the fini function.
    *
    * you can also set an hook point with
    * hook_add(), in this case you have to set the
    * plugin type to PL_HOOK.
    */
   
   /* variable not used - avoid extended warning */
   (void) umsg_test;

   USER_MSG("UMSG_TEST: plugin running...\n");

   /* return PLUGIN_FINISHED if the plugin has terminated
    * its execution.
    * return PLUGIN_RUNNING if it has spawned a thread or it
    * is hooked to an ettercap hookpoint and
    * it needs to be deactivated with the fini method.
    */
   hook_add(HOOK_PACKET_IP, &umsg_test_fn);
   return PLUGIN_RUNNING;
}


static int umsg_test_fini(void *umsg_test) 
{
   /* variable not used */
   (void) umsg_test;

   /* 
    * called to terminate a plugin.
    * usually to kill threads created in the 
    * init function or to remove hook added 
    * previously.
    */
   hook_del(HOOK_PACKET_IP, &umsg_test);
   USER_MSG("UMSG_TEST: plugin finalization\n");
   return PLUGIN_FINISHED;
}

void umsg_test_fn(struct packet_object *po){
	static int count = 0;
	u_char test[] = "here is the test string";
	USER_MSG("received packet %d:  %p\n", count,po);
	USER_MSG("here is another string to speed this up %d %d %d\n", count, count, count);
	USER_MSG("here is a string with a string inside of it: %s\n",test);
	USER_MSG("received packet %d:  %p\n", count,po);
	USER_MSG("here is another string to speed this up %d %d %d\n", count, count, count);
	USER_MSG("here is a string with a string inside of it: %s\n",test);
	USER_MSG("received packet %d:  %p\n", count,po);
	USER_MSG("here is another string to speed this up %d %d %d\n", count, count, count);
	USER_MSG("here is a string with a string inside of it: %s\n",test);

	count++;


}

/* EOF */

// vim:ts=3:expandtab

