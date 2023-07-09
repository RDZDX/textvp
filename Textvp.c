#include "Textvp.h"

int last_y = 0;
int myFilePosition = 0;

VMCHAR value10[MRE_STR_SIZE_MAX + 23]; //21
VMCHAR nauj_strng[MRE_STR_SIZE_MAX + 23];

/*****************************************************************************
 * FUNCTION
 *  vm_main
 * DESCRIPTION
 *  This function is main function which is invoked in start up
 *  ie entry function.
 * PARAMETERS
 *  none
 * RETURNS
 *	none
 *****************************************************************************/
void vm_main(void) {
    layer_hdl[0] = -1;

    mre_set_global_data();

    /* cerate base layer that has same size as the screen*/

    vm_mul_lang_set_lang(VM_LANG_ENG);
    vm_reg_sysevt_callback(handle_sysevt);
    vm_reg_keyboard_callback(handle_keyevt);
}

/*****************************************************************************
 * FUNCTION
 *  handle_sysevt
 * DESCRIPTION
 *  This function handles system events
 * PARAMETERS
 *  event		    	[IN]      message id
 *  param               [IN]      parameter
 * RETURNS
 *	none
 *****************************************************************************/

void handle_sysevt(VMINT message, VMINT param) {
    // vm_log_debug ("system event handle function starts with message : %d and
    // parameter : %d", message, param);
    /* The application updates the screen when receiving the message
     * VM_MSG_PAINT what is sent after the application is activated. The
     * application can skip the process on screen when the VM_MSG_ACTIVE or
     * VM_MSG_INACTIVE is received.
     */
    switch (message) {
        case VM_MSG_CREATE:
            /* the GDI operation is not recommended as the response of the
             * message*/
            break;
        case VM_MSG_ACTIVE:
            layer_hdl[0] =
                vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(),
                                        vm_graphic_get_screen_height(), -1);
            // layer_hdl[1] = vm_graphic_create_layer(0, 0,
            // vm_graphic_get_screen_width(), vm_graphic_get_screen_height(),
            // -1);
            vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(),
                                vm_graphic_get_screen_height());
            // layer_bufs[0]=vm_graphic_get_layer_buffer(layer_hdl[0]);
            // layer_bufs[1]=vm_graphic_get_layer_buffer(layer_hdl[1]);
            vm_switch_power_saving_mode(turn_off_mode);
            break;
        case VM_MSG_PAINT:
            // vm_log_debug ("paint message, support bg");
            layer_hdl[0] =
                vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(),
                                        vm_graphic_get_screen_height(), -1);
            vm_graphic_active_layer(layer_hdl[0]);
            /* set clip area */
            vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(),
                                vm_graphic_get_screen_height());

            mre_read_file_display("default.txt");

            vm_switch_power_saving_mode(turn_off_mode);
            break;

        case VM_MSG_HIDE:
            break;

        case VM_MSG_INACTIVE:
            vm_switch_power_saving_mode(turn_on_mode);
            // vm_log_debug ("VM_MSG_HIDE message, support bg");
            if (layer_hdl[0] != -1) {
                vm_graphic_delete_layer(layer_hdl[0]);
                // vm_graphic_delete_layer(layer_hdl[1]);
            }
            break;

        case VM_MSG_QUIT:
            // vm_log_debug ("VM_MSG_QUIT message, support bg");
            // if (layer_hdl[0] != -1) {
            // vm_graphic_delete_layer(layer_hdl[0]);
            // layer_hdl[0] = -1;
            // handle_exitevt(NULL);
            // break;
            //}
            handle_exitevt(NULL);
            break;
    }
}


/*****************************************************************************
 * FUNCTION
 *  mre_read_file_display
 * DESCRIPTION
 *  This function displays file's content on display text box
 *  which is actually input textbox
 * PARAMETERS
 *  file name				[IN]      name of file
 * RETURNS
 *	result                  [OUT]     some code for error and success
 *****************************************************************************/

VMINT mre_read_file_display(VMSTR file_name) {
    VMINT drv;
    VMFILE f_read;
    VMCHAR f_name[MRE_STR_SIZE_MAX + 1];
    VMWCHAR f_wname[MRE_STR_SIZE_MAX + 1];
    VMUINT nread;

    VMCHAR value1[MRE_STR_SIZE_MAX + 23]; //21
    VMCHAR value21[MRE_STR_SIZE_MAX + 23];
    VMCHAR vns_simbl[MRE_STR_SIZE_MAX];
    VMCHAR konv_stringas[MRE_STR_SIZE_MAX + 23];
    VMCHAR knv_vns_simbl[MRE_STR_SIZE_MAX];

    //VMCHAR value10[MRE_STR_SIZE_MAX + 23];
    //VMCHAR nauj_strng[MRE_STR_SIZE_MAX + 23];

    //last_y = 0;

    if ((drv = vm_get_removable_driver()) < 0) { drv = vm_get_system_driver(); }

    sprintf(f_name, "%c:\\%s", drv, file_name);
    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    if (f_read < 0) {
    vm_file_close(f_read);
    vertical_scrolling_text("      File default.txt not found !");
    }
    else {

    vm_file_seek(f_read, myFilePosition, BASE_CURR);

    int i, j, plotis, strng_plot, vns_simbl_plot, trigeris, trigeris1, isve_i_ekr_eil_sk, nauj_strng_ilg, uodegos_ilgis;
    plotis = 0;
    strng_plot = 0;
    vns_simbl_plot = 0;
    trigeris = 0;
    trigeris1 = 0;
    isve_i_ekr_eil_sk = 0;
    nauj_strng_ilg = 0;
    uodegos_ilgis = 0;
    
    for (i = 0; i < 20; i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega 
    {
        if (isve_i_ekr_eil_sk == 20) { break; }

        vm_file_read(f_read, value1, 60, &nread);
        value1[nread] = '\0';
        myFilePosition = vm_file_tell(f_read);

        strcat(value10, value1);
        //trim_left_spaces(value10, value10);
        //many_space_symbols_to_one(value10, value10);
        vm_ascii_to_ucs2(value21, 123, value10);  // 123
        plotis = vm_graphic_get_string_width(value21);

        if (plotis < 236 || plotis == 236) { continue; }  // jei nesigaunasi pilna eilute, prasisukam - generuojam "dviguba" fragmenta.

        char *ptr = value10;

        while (*ptr != '\0') {

            if (trigeris == 0){                                  //pries isvedant i ekrana pravalom tarpo simboli
               sprintf(vns_simbl, "%c", *ptr);
//             if (vns_simbl == '\n' || vns_simbl == '\t') {strcpy(vns_simbl, "");} 
               vm_ascii_to_ucs2(knv_vns_simbl, 123, vns_simbl);
               vns_simbl_plot = vm_graphic_get_string_width(knv_vns_simbl);
               }

           if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 0) {     ///trigeris == 0
               //trim_left_spaces(nauj_strng, nauj_strng);
               vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
               strng_plot = vm_graphic_get_string_width(konv_stringas);
               trigeris = 1;
               continue;
               }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 1) {     ///trigeris == 1
                vertical_scrolling_text(nauj_strng);
                nauj_strng_ilg = strlen(nauj_strng);
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                strcpy(nauj_strng, "");
                strng_plot = 0;
                trigeris = 0;
                continue;
            }

            if (isve_i_ekr_eil_sk == 20) {
            //myFilePosition = myFilePosition - (nauj_strng_ilg + uodegos_ilgis + 20);
            myFilePosition = myFilePosition - (nauj_strng_ilg + uodegos_ilgis + 3);
            //myFilePosition = myFilePosition - uodegos_ilgis;
            break; }

            strcat(nauj_strng, vns_simbl);
            vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
            strng_plot = vm_graphic_get_string_width(konv_stringas);
            ptr++;
        }

        strcpy(value10, nauj_strng);
        uodegos_ilgis = strlen(value10);
        strcpy(nauj_strng, "");
    }

    if ((isve_i_ekr_eil_sk < 20 && strng_plot + vns_simbl_plot) < 240) {
       //trim_left_spaces(value10, value10);
       vertical_scrolling_text(value10);                 
    }

    if (vm_file_is_eof(f_read)) {
    strcpy(value10, "");     
    myFilePosition = 0; }

    vm_file_close(f_read);

strcpy(value1, "");
strcpy(vns_simbl, "");
strcpy(konv_stringas, "");
strcpy(knv_vns_simbl, "");
strcpy(nauj_strng, "");
strcpy(value10, "");
strcpy(f_name, "");
strcpy(f_wname, "");
strcpy(value21, "");

    return MRE_SCILENT;
}
}

/*****************************************************************************
 * FUNCTION
 *  mre_set_global_data
 * DESCRIPTION
 *  This function sets global data variables
 *  handling actions
 * PARAMETERS
 *  none
 * RETURNS
 *	none
 *****************************************************************************/
void mre_set_global_data(void) {
    mre_set_curr_x(MRE_SET_X);
    mre_set_curr_y(MRE_SET_Y);
    vm_font_set_font_size(VM_SMALL_FONT);
    // vm_switch_power_saving_mode(turn_off_mode);
}

/*****************************************************************************
 * FUNCTION
 *  mre_set_curr_x
 * DESCRIPTION
 *  This function sets current x cordinate to write strings on screen
 * PARAMETERS
 *  x			         [IN]      current x cordinate
 * RETURNS
 *	none
 *****************************************************************************/
void mre_set_curr_x(VMINT x) { g_mre_curr_x = x; }

/*****************************************************************************
 * FUNCTION
 *  mre_get_curr_x
 * DESCRIPTION
 *  This function gets current x cordinate to write strings on screen
 * PARAMETERS
 *  none
 * RETURNS
 *  g_mre_curr_x        [OUT]      current x cordinate
 *****************************************************************************/
VMINT mre_get_curr_x(void) { return g_mre_curr_x; }

/*****************************************************************************
 * FUNCTION
 *  mre_set_curr_y
 * DESCRIPTION
 *  This function sets current y cordinate to write strings on screen
 * PARAMETERS
 *  y			         [IN]      current y cordinate
 * RETURNS
 *	none
 *****************************************************************************/
void mre_set_curr_y(VMINT y) { g_mre_curr_y = y; }

/*****************************************************************************
 * FUNCTION
 *  mre_get_curr_y
 * DESCRIPTION
 *  This function gets current y cordinate to write strings on screen
 * PARAMETERS
 *  none
 * RETURNS
 *  g_mre_curr_y         [OUT]      current y cordinate
 *****************************************************************************/
VMINT mre_get_curr_y(void) { return g_mre_curr_y; }

/*****************************************************************************
 * FUNCTION
 *  handle_keyevt
 * DESCRIPTION
 *  This function handles key events
 * PARAMETERS
 *  event		    	[IN]      event no
 *  keycode             [IN]      keycode no
 * RETURNS
 *	none
 *****************************************************************************/
/* closing application on pressing right soft key */

void handle_keyevt(VMINT event, VMINT keycode) {
    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
       if( layer_hdl[0] != -1 )
			{
				vm_graphic_delete_layer(layer_hdl[0]);
				layer_hdl[0] = -1;
			}
       vm_exit_app();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
    mre_draw_rectangle();
    mre_read_file_display("default.txt");
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_DOWN) {
    mre_draw_rectangle();
    mre_read_file_display("default.txt");
    }
}

/*****************************************************************************
 * FUNCTION
 *  vertical_scrolling_text
 * DESCRIPTION
 *  This function displays results of http conne
 * PARAMETERS
 *  ascii_string      [IN]           - contains display string
 * RETURNS
 *	none
 *****************************************************************************/
void vertical_scrolling_text(VMSTR ascii_string) {
    /* local variables */
    int max_height;
    int font_height;

    font_height = vm_graphic_get_character_height();
    max_height = vm_graphic_get_screen_height();

    if (last_y > vm_graphic_get_screen_height() || last_y == 0) {
        last_y = 0;
        vm_graphic_fill_rect(vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
            MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
            vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    }

    draw_result_string(MRE_SCREEN_START_X, last_y, ascii_string);
    last_y += font_height;
}

/*****************************************************************************
 * FUNCTION
 *  draw_result_string
 * DESCRIPTION
 *  This function displayes state of http connection and response head, body on
 *screen PARAMETERS none RETURNS none
 *****************************************************************************/
static void draw_result_string(int display_string_x_pos,
                                    int display_string_y_pos,
                                    VMSTR ascii_string) {
    /* local variables */
    VMWSTR display_string, exit_str;
    VMINT size;

    /* function body */
    size = (strlen(ascii_string) + 1) * 2;
    display_string = vm_malloc(size);
    vm_graphic_clear_layer_bg(layer_hdl[0]);
    vm_ascii_to_ucs2(display_string, size, ascii_string);
    /* draw text */
    vm_graphic_textout(vm_graphic_get_layer_buffer(layer_hdl[0]),
                       display_string_x_pos, display_string_y_pos,
                       display_string, wstrlen(display_string), VM_COLOR_WHITE);

    /* flush the screen with data in the buffer*/
    vm_graphic_flush_layer(layer_hdl, 1);
    vm_free(display_string);
}

/*****************************************************************************
 * FUNCTION
 *  handle_exitevt
 * DESCRIPTION
 *  
 * PARAMETERS
 *  
 * RETURNS
 *	
*****************************************************************************/
void handle_exitevt(void *ctx) {
    if (layer_hdl[0] != -1) {
        vm_graphic_delete_layer(layer_hdl[0]);
        layer_hdl[0] = -1;
    }
    if (layer_hdl[1] != -1) {
        vm_graphic_delete_layer(layer_hdl[0]);
        layer_hdl[1] = -1;
    }
    // widget_on_destroy(g_mtid_view);
    // vm_res_deinit();
    vm_exit_app();
}

/*****************************************************************************
 * FUNCTION
 *  mre_draw_rectangle
 * DESCRIPTION
 *  This function draws rectangle on screen
 * PARAMETERS
 *  
 * RETURNS
 *	
*****************************************************************************/
void mre_draw_rectangle(void)
{
    last_y = 0;

	/*local variables */
    VMUINT8 *buffer;

	/* get the target buffer*/
	buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buffer, MRE_SET_SRC_LEFT_TOP_X, MRE_SET_SRC_LEFT_TOP_Y, vm_graphic_get_screen_width(), 
		                 vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    vm_graphic_flush_layer(layer_hdl, 1); 
}

/*****************************************************************************
 * FUNCTION
 *  trim_left_spaces
 * DESCRIPTION
 *  
 * PARAMETERS
 *  
 * RETURNS
 *	
*****************************************************************************/
void trim_left_spaces(char *reslt_data, char *inp_data) {

    int flag = 0;

    while(*inp_data) {
        //if(!isspace((unsigned char) *inp_data) && flag == 0) {
        if(' ' != (unsigned char) *inp_data && flag == 0) {

            *reslt_data++ = *inp_data;
            flag = 1;
        }
        inp_data++;
        if(flag == 1) {
            *reslt_data++ = *inp_data;
        }
    }
  *reslt_data = '\0';
}

/*****************************************************************************
 * FUNCTION
 *  trim_right_spaces
 * DESCRIPTION
 *  
 * PARAMETERS
 *  
 * RETURNS
 *	
*****************************************************************************/
void trim_right_spaces(char *reslt_data, char *inp_data) {

      while(*inp_data) {
            *reslt_data++ = *inp_data;
          inp_data++;
    }
     
     while(1) {
        reslt_data--;
               if(!isspace((unsigned char) *reslt_data)) {
            break;
        }
    //    *reslt_data = '\0';  // Ar cia ?
        }
    *reslt_data = '\0'; // Ar cia ?
}

/*****************************************************************************
 * FUNCTION
 *  many_space_symbols_to_one
 * DESCRIPTION
 *  
 * PARAMETERS
 *  
 * RETURNS
 *	
*****************************************************************************/
void many_space_symbols_to_one(char *reslt_data, char *inp_data) {

    while(*inp_data) {
        
        if(isspace((unsigned char) *inp_data) && isspace((unsigned char) *(inp_data + 1))) {
            inp_data++;
            continue;
        }
        
            //inp_data++; //Jei cia tai nebus pirmo tarpo
            *reslt_data++ = *inp_data;
            inp_data++;  //Jei cia tai bus pirmas tarpas
    }
  *reslt_data = '\0';
}
