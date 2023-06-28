#include "Textvp.h"

#define MRE_SCREEN_START_X (0)
#define MRE_SCREEN_START_Y (0)
#define MRE_NO_TRANS_COLOR (-1)

static int last_y;
int last_yy;

VMCHAR value1[MRE_STR_SIZE_MAX + 100];
VMCHAR value2[MRE_STR_SIZE_MAX + 1];
VMCHAR value3[MRE_STR_SIZE_MAX + 1];
VMCHAR value4[MRE_STR_SIZE_MAX + 1];
VMCHAR value5[MRE_STR_SIZE_MAX + 1];
VMCHAR value6[MRE_STR_SIZE_MAX + 1];
VMCHAR value7[MRE_STR_SIZE_MAX + 1];
VMCHAR value8[MRE_STR_SIZE_MAX + 1];
VMCHAR value9[MRE_STR_SIZE_MAX + 1];
VMCHAR value10[MRE_STR_SIZE_MAX + 100];
VMCHAR value11[MRE_STR_SIZE_MAX + 1];
VMCHAR value12[MRE_STR_SIZE_MAX + 1];
VMCHAR value13[MRE_STR_SIZE_MAX + 1];
VMCHAR value14[MRE_STR_SIZE_MAX + 1];
VMCHAR value15[MRE_STR_SIZE_MAX + 1];
VMCHAR value16[MRE_STR_SIZE_MAX + 1];
VMCHAR value17[MRE_STR_SIZE_MAX + 1];
VMCHAR value18[MRE_STR_SIZE_MAX + 1];
VMCHAR value19[MRE_STR_SIZE_MAX + 1];
VMCHAR value20[MRE_STR_SIZE_MAX + 1];

VMCHAR value21[MRE_STR_SIZE_MAX + 1];
VMCHAR value22[MRE_STR_SIZE_MAX + 1];
VMCHAR value23[MRE_STR_SIZE_MAX + 1];

VMCHAR likutis[MRE_STR_SIZE_MAX + 100];
VMCHAR nauj_strng[MRE_STR_SIZE_MAX + 100];
VMCHAR vns_simbl[MRE_STR_SIZE_MAX + 100];
VMCHAR konv_stringas[MRE_STR_SIZE_MAX + 100];
VMCHAR knv_vns_simbl[MRE_STR_SIZE_MAX + 100];

//char *ptr = value10;

//char oneDisplay[21][61]; // = malloc(1500);

//char *oneDisplay = malloc(3*2*sizeof(char *)); //61 simbolis

char oneDisplay[21][61] = {
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "      File default.txt not found !"
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "                                                            ",
    "Refresh                                Exit  "
  };

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
            // layer_bufs[0]=vm_graphic_get_layer_buffer(layer_hdls[0]);
            // layer_bufs[1]=vm_graphic_get_layer_buffer(layer_hdls[1]);
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

            //myTest1();

            mre_read_file_display("default.txt");

            //testDimensions();

            //mre_read_file_to_array("default.txt");
            //testDimensions();


            // vertical_scrolling_text("ASYN_HTTP_REQ_NOT_SUPPORT_METHOD");
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
 *  mre_show_text
 * DESCRIPTION
 *  This function takes text string and displays it on the screen
 * PARAMETERS
 *  text				[IN]      Text string in ASCII or GB2312
 *format RETURNS none
 *****************************************************************************/

void mre_show_text(VMSTR text) {
    VMWCHAR s[MRE_STR_SIZE_MAX];
    VMUINT8 *buf;
    int w;

    /* get the target buffer*/
    buf = vm_graphic_get_layer_buffer(layer_hdl[0]);

    /* fill the screen*/
    vm_graphic_fill_rect(buf, MRE_SET_SRC_LEFT_TOP_X, MRE_SET_SRC_LEFT_TOP_Y,
                         vm_graphic_get_screen_width(),
                         vm_graphic_get_screen_height(), VM_COLOR_BLACK,
                         VM_COLOR_BLACK);

    /* converts string into usc2 format to display on the screen */
    vm_gb2312_to_ucs2(s, MRE_STR_SIZE_MAX, text);
    w = vm_graphic_get_string_width(s);

    /* intialize location of string menu item*/
    mre_set_curr_x(MRE_SET_X + MRE_SET_MARGIN);
    mre_set_curr_y(MRE_SET_Y + MRE_SET_MARGIN);

    /* draw text */
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 1 key */
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "01: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 2 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "02: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 3 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "03: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 4 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "04: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 5 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "05: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 6 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "06: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 7 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "07: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 8 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "08: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 9 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "09: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 10 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "10: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 11 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "11: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 12 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "12: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 13 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "13: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 14 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "14: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    /* NUM 15 key..*/
    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    /* converts string into usc2 format to display on the screen */
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, "15: Read content of file m");
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s),
                       VM_COLOR_WHITE);

    vm_graphic_flush_layer(layer_hdl, 1);
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
    VMCHAR data[MRE_STR_SIZE_MAX + 1];
    VMCHAR show_data[MRE_STR_SIZE_MAX + 1 + 10];
    VMCHAR show_text[MRE_STR_SIZE_MAX + 1];
    VMUINT nread;

   last_y = 0;
   last_yy = 0;
   memset(oneDisplay, 0, sizeof(oneDisplay[0][0]) * 21 * 61);

    //drv = vm_get_removable_driver();
    if ((drv = vm_get_removable_driver()) < 0) { drv = vm_get_system_driver(); }

    sprintf(f_name, "%c:\\%s", drv, file_name);
    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    if (f_read < 0) {
    vm_file_close(f_read);
    vertical_scrolling_text("      File default.txt not found !");
    }
    else {

    int i, j, plotis, strng_plot, vns_simbl_plot, trigeris, trigeris1, isve_i_ekr_eil_sk;
    char nauj_strng1, nauj_strng2;
    plotis = 0;
    strng_plot = 0;
    vns_simbl_plot = 0;
    trigeris = 0;
    trigeris1 = 0;
    isve_i_ekr_eil_sk = 0;
    
    for (i = 0; i < 20; i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega 
    {
        if (isve_i_ekr_eil_sk == 20) { break; }

        vm_file_read(f_read, value1, 60, &nread);
        value1[nread] = '\0';
        strcat(value10, value1);
        //trim_left_spaces(value10, value10);
        many_space_symbols_to_one(value10, value10);
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
               trim_left_spaces(nauj_strng, nauj_strng);
               vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
               strng_plot = vm_graphic_get_string_width(konv_stringas);
               trigeris = 1;
               continue;
               }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 1) {     ///trigeris == 1
                vertical_scrolling_text(nauj_strng);
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                sprintf(&oneDisplay[isve_i_ekr_eil_sk - 2][61], "%s", nauj_strng);
                strcpy(nauj_strng, "");
                strng_plot = 0;
                trigeris = 0;
                continue;
            }

            if (isve_i_ekr_eil_sk == 20) { break; }

            strcat(nauj_strng, vns_simbl);
            vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
            strng_plot = vm_graphic_get_string_width(konv_stringas);
            ptr++;
        }

        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
    }

    if ((isve_i_ekr_eil_sk < 20 && strng_plot + vns_simbl_plot) < 240) {
       trim_left_spaces(value10, value10);
       vertical_scrolling_text(value10);                 
       sprintf(&oneDisplay[isve_i_ekr_eil_sk - 1][61], "%s", value10);
    }

    vm_file_close(f_read);

//VMCHAR value1 = {0};
//VMCHAR value10 = {0};
//VMCHAR likutis = {0};
//VMCHAR nauj_strng = {0};
//VMCHAR vns_simbl = {0};
//VMCHAR konv_stringas = {0};
//VMCHAR knv_vns_simbl = {0};

strcpy(value1, "");
strcpy(likutis, "");
strcpy(vns_simbl, "");
strcpy(konv_stringas, "");
strcpy(knv_vns_simbl, "");

strcpy(nauj_strng, "");
strcpy(value10, "");

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

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {
    //mre_draw_rectangle();
    //testDimensions1();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM2) {
    //mre_draw_rectangle();
    // testDimensions();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM3) {
    //mre_draw_rectangle();
    //myTest1();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM4) {
    //mre_draw_rectangle();
    //vertical_scrolling_text("                                        ");
    //vertical_scrolling_text("      File default.txt not found !");
    //vertical_scrolling_text("                                        ");
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM5) {
    //mre_draw_rectangle();
    //myTest2();
    //}

    // if( layer_hdl[0] != -1 )
    //{
    // vm_graphic_delete_layer(layer_hdl[0]);
    // layer_hdl[0] = -1;
    //}
    // vm_exit_app();        /* quit application */
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
    unsigned int i = MRE_INTIAL_VALUE;
    // static int last_y = MRE_INTIAL_VALUE;
    font_height = vm_graphic_get_character_height();
    last_yy = last_yy + font_height;

    max_height = vm_graphic_get_screen_height();
    for (i = MRE_INTIAL_VALUE; i < strlen(ascii_string); i++) {
        int width, height;
        vm_graphic_measure_character(ascii_string[i], &width, &height);
        if (height > max_height) {
            max_height = height;
        }
    }

    // if ((last_y + max_height) > vm_graphic_get_screen_height() || last_y ==
    // MRE_INTIAL_VALUE)
    if (last_y == MRE_INTIAL_VALUE) {
        // last_y = MRE_INTIAL_VALUE;
        vm_graphic_fill_rect(
            vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
            MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
            vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    }

    draw_http_result_string(MRE_SCREEN_START_X, last_y, ascii_string);

    // last_y += max_height; //Originalas
    last_y = last_yy;
}

/*****************************************************************************
 * FUNCTION
 *  draw_http_result_string
 * DESCRIPTION
 *  This function displayes state of http connection and response head, body on
 *screen PARAMETERS none RETURNS none
 *****************************************************************************/
static void draw_http_result_string(int display_string_x_pos,
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
 *  This function draws ellipse on screen
 * PARAMETERS
 *  none
 * RETURNS
 *	none
*****************************************************************************/
void mre_draw_rectangle(void)
{
	/*local variables */
    VMUINT8 *buffer;
    last_y = 0;
    last_yy = 0;

	/* function body */
	/*log information*/
	vm_log_debug("draw rectangle starts");
	/* get the target buffer*/
	buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buffer, MRE_SET_SRC_LEFT_TOP_X, MRE_SET_SRC_LEFT_TOP_Y, vm_graphic_get_screen_width(), 
		                 vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    //vm_graphic_fill_rect(buffer, REC_X, REC_Y, REC_W, REC_L, VM_COLOR_RED, VM_COLOR_RED);
    vm_graphic_flush_layer(layer_hdl, 1); 
    //vm_log_debug("draw rectangle fun ends");
}

void testDimensions (void) {

    VMWCHAR s[MRE_STR_SIZE_MAX];
    VMUINT8 *buf;
    int w;

    buf = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buf, MRE_SET_SRC_LEFT_TOP_X, MRE_SET_SRC_LEFT_TOP_Y, vm_graphic_get_screen_width(),
    vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);

    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[0][0]);
    w = vm_graphic_get_string_width(s);
    //mre_set_curr_x(MRE_SET_X + MRE_SET_MARGIN);
    //mre_set_curr_y(MRE_SET_Y + MRE_SET_MARGIN);
    mre_set_curr_x(MRE_SET_X);
    mre_set_curr_y(MRE_SET_Y);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[1][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[2][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[3][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[4][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[5][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[6][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[7][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[8][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[9][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[10][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[11][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[12][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[13][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[14][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[15][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[16][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[17][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[18][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 22, &oneDisplay[19][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    vm_graphic_flush_layer(layer_hdl, 1);
}

void testDimensions1 (void) {

    VMWCHAR s[MRE_STR_SIZE_MAX];
    VMUINT8 *buf;
    int w;

    buf = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buf, MRE_SET_SRC_LEFT_TOP_X, MRE_SET_SRC_LEFT_TOP_Y, vm_graphic_get_screen_width(),
    vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);

    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX + 50, &oneDisplay[0][0]);
    w = vm_graphic_get_string_width(s);
    mre_set_curr_x(MRE_SET_X + MRE_SET_MARGIN);
    mre_set_curr_y(MRE_SET_Y + MRE_SET_MARGIN);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[1][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[2][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[3][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[4][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[5][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[6][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[7][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[8][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[9][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[10][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[11][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[12][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[13][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[14][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[15][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[16][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[17][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[18][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, MRE_SET_VAL, MRE_STR_SIZE_MAX);
    mre_set_curr_y(mre_get_curr_y() + vm_graphic_get_character_height());
    vm_ascii_to_ucs2(s, MRE_STR_SIZE_MAX, &oneDisplay[19][0]);
    vm_graphic_textout(buf, mre_get_curr_x(), mre_get_curr_y(), s, wstrlen(s), VM_COLOR_WHITE);

    vm_graphic_flush_layer(layer_hdl, 1);
}


VMINT mre_read_file_to_array(VMSTR file_name) {

    VMFILE f_read;
    VMCHAR f_name[MRE_STR_SIZE_MAX + 1];
    VMWCHAR f_wname[MRE_STR_SIZE_MAX + 1];
    VMCHAR data[MRE_STR_SIZE_MAX + 1];
    VMCHAR show_data[MRE_STR_SIZE_MAX + 1 + 10];
    VMCHAR show_text[MRE_STR_SIZE_MAX + 1];
    VMUINT nread;

   last_y = 0;
   last_yy = 0;
   memset(oneDisplay, 0, sizeof(oneDisplay[0][0]) * 21 * 61);

    sprintf(f_name, "%c:\\%s", vm_get_removable_driver(), file_name);
    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    if (f_read < 0) {
        //vertical_scrolling_text("      File default.txt not found !");
        vm_exit_app();
        // return MRE_FILE_OPEN_FAILED;
    }

    int i, j, plotis, strng_plot, vns_simbl_plot, trigeris, trigeris1, isve_i_ekr_eil_sk;
    char nauj_strng1, nauj_strng2;
    plotis = 0;
    strng_plot = 0;
    vns_simbl_plot = 0;
    trigeris = 0;
    trigeris1 = 0;
    isve_i_ekr_eil_sk = 0;
    
    for (i = 0; i < 20; i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega 
    {
        if (isve_i_ekr_eil_sk == 20) { break; }

        vm_file_read(f_read, value1, 60, &nread);
        value1[nread] = '\0';
        strcat(value10, value1);
        //trim_left_spaces(value10, value10);
        many_space_symbols_to_one(value10, value10);
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
               trim_left_spaces(nauj_strng, nauj_strng);
               vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
               strng_plot = vm_graphic_get_string_width(konv_stringas);
               trigeris = 1;
               continue;
               }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 1) {     ///trigeris == 1
//                vertical_scrolling_text(nauj_strng);
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                sprintf(&oneDisplay[isve_i_ekr_eil_sk - 2][61], "%s", nauj_strng);
                strcpy(nauj_strng, "");
                strng_plot = 0;
                trigeris = 0;
                continue;
            }

            if (isve_i_ekr_eil_sk == 20) { break; }

            strcat(nauj_strng, vns_simbl);
            vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
            strng_plot = vm_graphic_get_string_width(konv_stringas);
            ptr++;
        }

        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
    }

    if ((isve_i_ekr_eil_sk < 20 && strng_plot + vns_simbl_plot) < 240) {
       trim_left_spaces(value10, value10);
//       vertical_scrolling_text(value10);                 
       sprintf(&oneDisplay[isve_i_ekr_eil_sk - 1][61], "%s", value10);
    }

    vm_file_close(f_read);

//VMCHAR value1 = {0};
//VMCHAR value10 = {0};
//VMCHAR likutis = {0};
//VMCHAR nauj_strng = {0};
//VMCHAR vns_simbl = {0};
//VMCHAR konv_stringas = {0};
//VMCHAR knv_vns_simbl = {0};

strcpy(value1, "");
strcpy(likutis, "");
strcpy(vns_simbl, "");
strcpy(konv_stringas, "");
strcpy(knv_vns_simbl, "");

strcpy(nauj_strng, "");
strcpy(value10, "");

    return MRE_SCILENT;
}


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

void clean_text(char *reslt_data, char *inp_data) {
    while(*inp_data) {
        if('m' != (unsigned char) *inp_data || 't' != (unsigned char) *inp_data) {
            *reslt_data++ = *inp_data;
          }
        inp_data++;
        *reslt_data++ = *inp_data;
    }
}

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


void myTest1(void) {

    VMCHAR f_name[MRE_STR_SIZE_MAX + 1];
    VMCHAR f_name1[MRE_STR_SIZE_MAX + 1];
    VMWCHAR f_wname[MRE_STR_SIZE_MAX + 1];
    VMWCHAR f_wname1[MRE_STR_SIZE_MAX + 1];      
    VMFILE f_read;
    VMFILE f_read1;
    VMSTR file_name = "default.txt";
    int start, end;

//    time(&start);
//    do time(&end); while(difftime(end, start) <= 2.5);


    sprintf(f_name, "%c:\\%s", vm_get_removable_driver(), file_name);
    sprintf(f_name1, "%c:\\%s", vm_get_system_driver(), file_name);

    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    vm_ascii_to_ucs2(f_wname1, MRE_STR_SIZE_MAX, f_name1);

    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    vertical_scrolling_text(f_name);

    if (f_read < 0) {
    vm_file_close(f_read);
    vertical_scrolling_text("Nerasta !");
    }
    else {
    vm_file_close(f_read);
    vertical_scrolling_text("Rasta !");
    }

    f_read1 = vm_file_open(f_wname1, MODE_READ, FALSE);

    vertical_scrolling_text(f_name1);

    if (f_read1 < 0) {
    vm_file_close(f_read1);
    vertical_scrolling_text("Nerasta !");
    }
    else {
    vm_file_close(f_read1);
    vertical_scrolling_text("Rasta !");
    }
}

void myTest2(void) {

    int i = 0;
    for (i = 0; i < 20; i++) {
       sprintf(value16, "%s", &oneDisplay[i][0]);
       //vm_ucs2_to_ascii(value15, MRE_STR_SIZE_MAX, value16);
       //vm_ascii_to_ucs2(value15, MRE_STR_SIZE_MAX, value16);
       //vertical_scrolling_text(value15);
       vertical_scrolling_text(value16);
    }

}

