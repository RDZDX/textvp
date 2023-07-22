#include "Textvp.h"

VMWSTR path[101] = {0};
VMSTR file_name = "default.txt";
int filledDsplByLines = 0;
int myFilePosition = 0;
int repeatAutoStartErr = 0;
int fileNotFound = 0;
int pageCounter = 0;
int failoGalas = 0;
int stopCounter = 0;
int lastPressedKey = 0;
int failoGalasPriesTai = 0;
int galoTrigeris = 0;
int failoGalasTemp = 0;

/*****************************************************************************
 * FUNCTION
 *  vm_main
 * DESCRIPTION
 *
 * PARAMETERS
 *
 *
 * RETURNS
 *	none
 *****************************************************************************/

void vm_main(void) {
    layer_hdl[0] = -1;
    vm_reg_sysevt_callback(handle_sysevt);
    vm_reg_keyboard_callback(handle_keyevt);
    vm_font_set_font_size(VM_SMALL_FONT);
    checkFileExist();  // Remove if '#define SUPPORT_BG' is enabled
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
    VMUINT8 *buffer;
    switch (message) {
        case VM_MSG_CREATE:
        case VM_MSG_ACTIVE:
            layer_hdl[0] =
                vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(),
                                        vm_graphic_get_screen_height(), -1);
            vm_graphic_set_clip(0, 0, vm_graphic_get_screen_width(),
                                vm_graphic_get_screen_height());
            buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
            vm_switch_power_saving_mode(turn_off_mode);
            break;

        case VM_MSG_PAINT:
            vm_switch_power_saving_mode(turn_off_mode);
            mre_read_file_display(path);
            break;
        case VM_MSG_INACTIVE:
            vm_switch_power_saving_mode(turn_on_mode);
            if (layer_hdl[0] != -1) vm_graphic_delete_layer(layer_hdl[0]);

            break;
        case VM_MSG_QUIT:
            if (layer_hdl[0] != -1) vm_graphic_delete_layer(layer_hdl[0]);
            break;
    }
}

/*****************************************************************************
 * FUNCTION
 *  handle_keyevt
 * DESCRIPTION
 *
 * PARAMETERS
 *
 *
 * RETURNS
 *	none
 *****************************************************************************/

void handle_keyevt(VMINT event, VMINT keycode) {
    VMWCHAR *FILE_PATH = 0;
    VMCHAR cPageCnter[101] = {0};
    VMWCHAR cPageCnterX[101] = {0};

    int trigerisC2X = 0;

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
        if (layer_hdl[0] != -1) {
            vm_graphic_delete_layer(layer_hdl[0]);
            layer_hdl[0] = -1;
        }
        vm_exit_app();
    }

    // Remove if '#define SUPPORT_BG' is enabled
    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
        mre_draw_black_rectangle();
        vm_selector_run(0, FILE_PATH, file);
        pageCounter = 1;
        lastPressedKey = 0;  
        myFilePosition = 0;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_DOWN) {
        mre_draw_black_rectangle();
        failoGalasTemp = failoGalas;
        mre_read_file_display(path);

        if (failoGalas == 0 && pageCounter == 1 && failoGalasPriesTai == 0) {
            trigerisC2X = 2;
        }
        if (failoGalas == 0 && pageCounter != 1 && lastPressedKey == 3 && failoGalasPriesTai == 0) {
            trigerisC2X = 2;
        }
        if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter != 1 &&  lastPressedKey == 3) {
            trigerisC2X = 2;
            failoGalasPriesTai = 1;
        }
        if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter == 1 &&  lastPressedKey == 0 && failoGalasTemp == 1) {
            //trigerisC2X = 2; //del dvieju ekranu teksto, konfliktuoja su vieno ekrano tekstu
            failoGalasPriesTai = 1;
        }
        if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter == 1 &&  lastPressedKey == 0) {
            trigerisC2X = 2; //del dvieju ekranu teksto, konfliktuoja su vieno ekrano tekstu
            failoGalasPriesTai = 1;
        }
        if (trigerisC2X == 2) {
            pageCounter = pageCounter + 1;
        }
        lastPressedKey = 3;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {
        mre_draw_black_rectangle();
        vertical_scrolling_ucs2_text(path);

        sprintf(cPageCnter, "Current page No: %d", pageCounter);
        vm_ascii_to_ucs2(cPageCnterX, 123, cPageCnter);
        vertical_scrolling_ucs2_text(cPageCnterX);
    }

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_UP) {
    // mre_draw_black_rectangle();
    //}

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT) {
    // mre_draw_black_rectangle();
    // }

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT) {
    // mre_draw_black_rectangle();
    // }

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM2) {
    // mre_draw_black_rectangle();
    //}



}

/*****************************************************************************
 * FUNCTION
 *  file
 * DESCRIPTION
 *
 * PARAMETERS
 *
 *
 * RETURNS
 *	none
 *****************************************************************************/

VMINT file(VMWSTR FILE_PATH, VMINT wlen) {

    mre_draw_black_rectangle();
    vm_wstrcpy(path, FILE_PATH);
    //vmSelectrPathLen = wlen;
    stopCounter = 0;
    failoGalas = 0;
    pageCounter = 1;
    failoGalasPriesTai = 0;
    failoGalasTemp = 0;
    galoTrigeris = 0;
    return 0;
}

/*****************************************************************************
 * FUNCTION
 *  mre_read_file_display
 * DESCRIPTION
 *  This function displays file's cotent on display as 20 text lines
 *  which is actually input textbox
 * PARAMETERS
 *  file name				[IN]      name of file
 * RETURNS
 *	result                  [OUT]     some code for error and success
 *****************************************************************************/
VMINT mre_read_file_display(VMWSTR path) {
    VMFILE f_read;
    VMUINT nread;

    VMCHAR value1[MRE_STR_SIZE_MAX + 23] = {0};  // 21
    VMCHAR value21[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR vns_simbl[MRE_STR_SIZE_MAX] = {0};
    VMCHAR konv_stringas[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR knv_vns_simbl[MRE_STR_SIZE_MAX] = {0};
    VMCHAR value10[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR nauj_strng[MRE_STR_SIZE_MAX + 23] = {0};

    int myFlPosBackCurr = 0;
    int myFlPosBackTemp = 0;
    int myFlPosBackPrev = 0;

    f_read = vm_file_open(path, MODE_READ, FALSE);
  
    vm_file_seek(f_read, myFilePosition, BASE_CURR);

    myFlPosBackCurr = myFilePosition; 

    int i, j, plotis, strng_plot, vns_simbl_plot, trigeris, isve_i_ekr_eil_sk, nauj_strng_ilg, combUodegosIlgis, uodegosIlgis, uodegosTrigeris;
    plotis = 0;
    strng_plot = 0;
    vns_simbl_plot = 0;
    trigeris = 0;
    isve_i_ekr_eil_sk = 0;
    nauj_strng_ilg = 0;
    combUodegosIlgis = 0;
    uodegosIlgis = 0;
    uodegosTrigeris = 0;

    for (i = 0; i < 20; i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega
    {
        if (isve_i_ekr_eil_sk == 20) {
            break;
        }

        vm_file_read(f_read, value1, 60, &nread);  
        value1[nread] = '\0';
        myFilePosition = vm_file_tell(f_read);    
        strcat(value10, value1);                  
        // trim_left_spaces(value10, value10);
        // many_space_symbols_to_one(value10, value10);
        vm_ascii_to_ucs2(value21, 123, value10);  // 123
        plotis = vm_graphic_get_string_width(value21);

        if (plotis < 236 || plotis == 236) { continue; } 

        char *ptr = value10;
        while (*ptr != '\0') {
            if (trigeris == 0) {
                sprintf(vns_simbl, "%c", *ptr);                               
                vm_ascii_to_ucs2(knv_vns_simbl, 123, vns_simbl);              
                vns_simbl_plot = vm_graphic_get_string_width(knv_vns_simbl);  
            }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 0) {
                vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);         
                strng_plot = vm_graphic_get_string_width(konv_stringas);  
                trigeris = 1;                                             
                continue;                                                 
            }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 1) {
                vertical_scrolling_ucs2_text(konv_stringas);

                nauj_strng_ilg = strlen(nauj_strng);         

                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;   
                strcpy(nauj_strng, "");                      
                strng_plot = 0;                              
                trigeris = 0;                                


                continue;                                    
            }

            if (isve_i_ekr_eil_sk == 20) {
                break;
            }

            strcat(nauj_strng, vns_simbl);
            vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
            strng_plot = vm_graphic_get_string_width(konv_stringas);
            ptr++;
        }

        combUodegosIlgis = strlen(value10);
        uodegosIlgis = combUodegosIlgis - nauj_strng_ilg; 
        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
        if (vm_file_is_eof(f_read)) {break;}
    }

    if (vm_file_is_eof(f_read)) {

       if (isve_i_ekr_eil_sk < 20 && (strng_plot + vns_simbl_plot) < 240) {
          vertical_scrolling_ucs2_text(konv_stringas);
          uodegosTrigeris = 1;
       }
        strcpy(value10, "");
        filledDsplByLines = 0;
        nauj_strng_ilg = 0; 
        failoGalas = 1;
        if (isve_i_ekr_eil_sk == 20 && (combUodegosIlgis - nauj_strng_ilg) != 0) {failoGalas = 0;}
        stopCounter = 1;
        galoTrigeris = 1; 
    }

    vm_file_close(f_read);

    myFilePosition = (myFilePosition - uodegosIlgis);
    if (uodegosTrigeris == 1) {myFilePosition = myFlPosBackCurr;}

    strcpy(value1, "");
    strcpy(vns_simbl, "");
    strcpy(konv_stringas, "");
    strcpy(knv_vns_simbl, "");
    strcpy(nauj_strng, "");
    strcpy(value10, "");
    strcpy(value21, "");

    return 0;
}

/*****************************************************************************
 * FUNCTION
 *  vertical_scrolling_ucs2_text
 * DESCRIPTION
 *
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void vertical_scrolling_ucs2_text(VMWSTR ascii_string) {
    /* local variables */
    int max_height;
    int font_height;

    font_height = vm_graphic_get_character_height();
    max_height = vm_graphic_get_screen_height();

    if (filledDsplByLines > vm_graphic_get_screen_height() ||
        filledDsplByLines == 0) {
        filledDsplByLines = 0;
        vm_graphic_fill_rect(
            vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
            MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
            vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    }

    draw_result_ucs2_string(MRE_SCREEN_START_X, filledDsplByLines,
                            ascii_string);
    filledDsplByLines += font_height;
}

/*****************************************************************************
 * FUNCTION
 *  draw_result_ucs2_string
 * DESCRIPTION
 *
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
static void draw_result_ucs2_string(int display_string_x_pos,
                                    int display_string_y_pos,
                                    VMWSTR ascii_string) {
    vm_graphic_clear_layer_bg(layer_hdl[0]);
    vm_graphic_textout(vm_graphic_get_layer_buffer(layer_hdl[0]),
                       display_string_x_pos, display_string_y_pos, ascii_string,
                       wstrlen(ascii_string), VM_COLOR_WHITE);
    vm_graphic_flush_layer(layer_hdl, 1);
}

/*****************************************************************************
 * FUNCTION
 *  checkFileExist
 * DESCRIPTION
 *
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void checkFileExist(void) {
    VMINT drv;
    VMCHAR f_name[MRE_STR_SIZE_MAX + 1];
    VMWCHAR f_wname[MRE_STR_SIZE_MAX + 1];
    VMFILE f_read;
    VMWCHAR *FILE_PATH = 0;

    if ((drv = vm_get_removable_driver()) < 0) {
        drv = vm_get_system_driver();
    }
    sprintf(f_name, "%c:\\%s", drv, file_name);
    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    if (f_read < 0) {
        fileNotFound = 1;
        vm_file_close(f_read);
    } else {
        vm_file_close(f_read);
    }

    if (repeatAutoStartErr == 0) {
        vm_wstrcpy(path, f_wname);
    }

    if (fileNotFound == 1 && repeatAutoStartErr == 0) {
        repeatAutoStartErr = 1;

        vm_selector_run(0, FILE_PATH, file);

        repeatAutoStartErr = 0;  // Disable if '#define SUPPORT_BG' is enabled
    } else {
        pageCounter = 1;
        // mre_read_file_display(path); //Enable if '#define SUPPORT_BG' is enabled
    }
}

/*****************************************************************************
 * FUNCTION
 *  mre_draw_black_rectangle
 * DESCRIPTION
 *  This function draws rectangle on screen
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void mre_draw_black_rectangle(void) {
    filledDsplByLines = 0;

    /*local variables */
    VMUINT8 *buffer;

    /* get the target buffer*/
    buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buffer, MRE_SCREEN_START_X, MRE_SCREEN_START_Y,
                         vm_graphic_get_screen_width(),
                         vm_graphic_get_screen_height(), VM_COLOR_BLACK,
                         VM_COLOR_BLACK);
    vm_graphic_flush_layer(layer_hdl, 1);
}
