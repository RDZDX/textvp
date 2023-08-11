#include "Textvp.h"

VMWSTR path;
VMCHAR file_name[101] = "default.txt";

int filledDsplByLines = 0;
int currFlPosition = 0;
int tempFlPosition = 0;
int prviousFlPosit = 0;
int upFilePosition = 0;
int pageCounter = 0;
int lastPressedKey = 0;

int failoGalasPriesTai = 0;

VMWSTR oneDisplay[20][61];

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
    checkFileExist();
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
            //vm_free(path);
            //vm_free(w_filepath);
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
    VMCHAR cPageCnter[101];
    VMWCHAR cPageCnterX[101];

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
        if (layer_hdl[0] != -1) {
            vm_graphic_delete_layer(layer_hdl[0]);
            layer_hdl[0] = -1;
        }
        vm_free(path);
        //vm_free(w_filepath);
        vm_exit_app();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
        mre_draw_black_rectangle();
        //lastPressedKey = 0;
        vm_selector_run(0, FILE_PATH, file);
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_DOWN) {

       mre_draw_black_rectangle();

       tempFlPosition = currFlPosition;
       upFilePosition = prviousFlPosit;

       mre_read_file_display(path);

       prviousFlPosit = tempFlPosition;

       if (currFlPosition != tempFlPosition) {
          pageCounter = pageCounter + 1;
       }

       if (currFlPosition == tempFlPosition && failoGalasPriesTai == 0 && pageCounter != 1) {
          pageCounter = pageCounter + 1;
          failoGalasPriesTai = 1;
       }

       if (currFlPosition > 0 && currFlPosition == prviousFlPosit && failoGalasPriesTai == 0 && pageCounter == 1) {
          pageCounter = pageCounter + 1;
          failoGalasPriesTai = 1;
       }

       if (currFlPosition != 0 && currFlPosition == tempFlPosition && lastPressedKey == 2) {
          pageCounter = pageCounter + 1;
       }

      lastPressedKey = 3;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_UP) {
        mre_draw_black_rectangle();

        if (pageCounter > 2 && currFlPosition != tempFlPosition) {
            currFlPosition = upFilePosition;
        }
        else if (pageCounter > 2 && currFlPosition == tempFlPosition) {
                currFlPosition = upFilePosition;
        }
        else{}

        if (pageCounter < 3) {
            currFlPosition = 0;
        }

        //mre_read_file_display(path);

        if (pageCounter != 1 && currFlPosition != tempFlPosition) {
           pageCounter = pageCounter - 1;
        }

        mre_read_file_display(path);
        lastPressedKey = 2;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {
        mre_draw_black_rectangle();
        vertical_scrolling_ucs2_text(path);

        sprintf(cPageCnter, "Page #%d", pageCounter);
        vm_ascii_to_ucs2(cPageCnterX, (strlen(cPageCnter) + 1) * 2, cPageCnter);
        vertical_scrolling_ucs2_text(cPageCnterX);
    }

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT) {
    // mre_draw_black_rectangle();
    // }

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT) {
    // mre_draw_black_rectangle();
    // }

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM2) {
       //mre_draw_black_rectangle();
       //mre_read_file_display(path);
       //fromArrToDisplay();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM3) {
    //    mre_draw_black_rectangle();
    //
    //   int u = 0;
    //   for (u = 0; u < 21; u++) {
    //       vertical_scrolling_ucs2_text((VMWSTR)&oneDisplay[u][0]);
    //   }
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM4) {
    //    mre_draw_black_rectangle();
    //    fromArrToDisplay();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM5) {
    //    launchMyApp();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM6) {
    //    vm_camera_startup();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM7) {
    //    vm_start_native_browser(L"www.google.com");
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM8) {
    //    vm_start_IImageviewer(L"E:\\default1.jpg");
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM9) {
    //   vm_audio_play_beep();
    //}

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_OK) {
    //    vm_vibrator_once();
    // }
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

VMINT file(VMWCHAR *FILE_PATH, VMINT wlen) {

    mre_draw_black_rectangle();
    path = vm_realloc(path, (wlen + 1) * 2);
    vm_wstrcpy(path, FILE_PATH);
    pageCounter = 1;
    failoGalasPriesTai = 0;
    filledDsplByLines = 0;
    currFlPosition = 0;
    tempFlPosition = 0;
    prviousFlPosit = 0;
    upFilePosition = 0;
    lastPressedKey = 0;

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

    mre_draw_black_rectangle();
 
    VMFILE f_read;
    VMUINT nread;

    VMWSTR sValue21 = {0};
    VMWSTR sKonv_stringas = {0};
    VMWSTR sTemp_strng = {0};
    VMCHAR value1[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR vns_simbl[MRE_STR_SIZE_MAX] = {0};
    VMCHAR value10[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR nauj_strng[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR value21[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR konv_stringas[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR knv_vns_simblX[MRE_STR_SIZE_MAX] = {0};
    VMWCHAR knv_vns_simbl[MRE_STR_SIZE_MAX] = {0};

    int myFlPosBackCurr = 0;
    int myFlPosBackTemp = 0;
    int myFlPosBackPrev = 0;

    f_read = vm_file_open(path, MODE_READ, FALSE);

    vm_file_seek(f_read, currFlPosition, BASE_CURR);  // Permetame kursoriu i pozicija

    myFlPosBackCurr = currFlPosition;

    int i, plotis, strng_plot, isve_i_ekr_eil_sk, nauj_strng_ilg, combUodegosIlgis, uodegosIlgis;
    
    plotis = 0;
    strng_plot = 0;
    isve_i_ekr_eil_sk = 0;
    nauj_strng_ilg = 0;
    combUodegosIlgis = 0;
    uodegosIlgis = 0;

    //memset(oneDisplay, 0, sizeof(oneDisplay[0][0]) * 20 * 61);

    for (i = 0; i < 20;
         i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega
    {
        if (isve_i_ekr_eil_sk == 20) {break;}

        vm_file_read(f_read, value1, 60, &nread);  // 60
        value1[nread] = '\0';
        currFlPosition = vm_file_tell(f_read);  // Issaugome dabartine kursoriaus pozicija
        strcat(value10, value1);
        vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, value10, value21, (strlen(value10) + 1) * 2);
        sValue21 = (VMWSTR)value21;
        plotis = vm_graphic_get_string_width(sValue21);

        //240 - (7+1) = 232; 240 + 3 = 243; 243 - (7+1) = 235; 235 - 7 = 228
        //skirtumas 7 arba 8 pikseliai: simbolio maxplotis + tarpas

        if (plotis < 228 || plotis == 228) {
            continue;
        }

        char *ptr = value10;

        // while (*ptr != '\0' || *ptr != '\n') {

        while (*ptr != '\0') {
            sprintf(vns_simbl, "%c", *ptr);
            strcat(nauj_strng, vns_simbl);
            vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, nauj_strng, konv_stringas, (strlen(nauj_strng) + 1) * 2);
            sKonv_stringas = (VMWSTR)konv_stringas;
            strng_plot = vm_graphic_get_string_width(sKonv_stringas);

            //240 - (7+1) = 232; 240 + 3 = 243; 243 - (7+1) = 235
            //skirtumas 7 arba 8 pikseliai: simbolio maxplotis + tarpas

            if (strng_plot > 235) {
                vertical_scrolling_ucs2_text(sTemp_strng);
                //vm_wstrcpy((VMWSTR)&oneDisplay[isve_i_ekr_eil_sk - 1][61], sKonv_stringas);
                nauj_strng_ilg = strlen(nauj_strng) - 1;  // uodegos koordinatems nustatyti
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                strcpy(nauj_strng, "");
                ptr - 2;
            }

            if (isve_i_ekr_eil_sk == 20) {
                break;
            }

            sTemp_strng = sKonv_stringas;

            ptr++;
        }

        combUodegosIlgis = strlen(value10);
        uodegosIlgis = combUodegosIlgis - nauj_strng_ilg;
        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
        if (vm_file_is_eof(f_read)) { break; }
    }
 
     currFlPosition = (currFlPosition - uodegosIlgis) + 1;

    if (vm_file_is_eof(f_read)) {
                                                 //< 240
        if (isve_i_ekr_eil_sk < 20 && strng_plot == 235 || isve_i_ekr_eil_sk < 20 && strng_plot < 235) {
            vertical_scrolling_ucs2_text(sKonv_stringas);
            //vm_wstrcpy((VMWSTR)&oneDisplay[isve_i_ekr_eil_sk - 1][61], sKonv_stringas);
            currFlPosition = myFlPosBackCurr;
        }

        strcpy(value10, "");
        filledDsplByLines = 0;
        nauj_strng_ilg = 0;
    }

    vm_file_close(f_read);

    uodegosIlgis = 0;
    nauj_strng_ilg = 0;
    combUodegosIlgis = 0;

    strcpy(value1, "");
    strcpy(vns_simbl, "");
    strcpy(nauj_strng, "");
    strcpy(value10, "");
    strcpy(value21, "");
    strcpy(konv_stringas, "");
    strcpy(knv_vns_simblX, "");

    //vm_audio_play_beep();

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
void vertical_scrolling_ucs2_text(VMWSTR ucs2_string) {
    int max_height;
    int font_height;
    int i;

    font_height = 16;
    // font_height = vm_graphic_get_character_height();
    max_height = vm_graphic_get_screen_height();
    vm_graphic_clear_layer_bg(layer_hdl[0]);
    vm_graphic_textout_by_baseline(vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
    filledDsplByLines, ucs2_string, wstrlen(ucs2_string), VM_COLOR_WHITE, 12);
    vm_graphic_flush_layer(layer_hdl, 1);
    filledDsplByLines += font_height;
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

    mre_draw_black_rectangle();

    VMINT drv;
    VMCHAR f_name[MRE_STR_SIZE_MAX + 1];
    VMWCHAR f_wname[MRE_STR_SIZE_MAX + 1];
    VMFILE f_read;
    VMWCHAR *FILE_PATH = 0;
    int size = 0;

    if ((drv = vm_get_removable_driver()) < 0) {
        drv = vm_get_system_driver();
    }

    sprintf(f_name, "%c:\\%s", drv, file_name);
    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    pageCounter = 1;

    if (f_read < 0) {
        vm_file_close(f_read);
        vm_selector_run(0, FILE_PATH, file);
    } else {
        vm_file_close(f_read);
        size = (strlen(f_name) + 1) * 2;
        path = vm_malloc(size);
        vm_wstrcpy(path, f_wname);
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

    VMUINT8 *buffer;

    buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buffer, MRE_SCREEN_START_X, MRE_SCREEN_START_Y,
                         vm_graphic_get_screen_width(),
                         vm_graphic_get_screen_height(), VM_COLOR_BLACK,
                         VM_COLOR_BLACK);
    vm_graphic_flush_layer(layer_hdl, 1);
}

/*****************************************************************************
 * FUNCTION
 *  fromArrToDisplay
 * DESCRIPTION
 *  
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void fromArrToDisplay(void) {

    VMWCHAR s[MRE_STR_SIZE_MAX + 23];
    VMUINT8 *buf;
    int w;
    VMINT g_mre_curr_y = 0;

    buf = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buf, MRE_SCREEN_START_X, MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
    vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);

    vm_wstrcpy(s, (VMWSTR)&oneDisplay[0][0]);
    w = vm_graphic_get_string_width(s);
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[1][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[2][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[3][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[4][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[5][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[6][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[7][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[8][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[9][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[10][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[11][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[12][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[13][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[14][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[15][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[16][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[17][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[18][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    memset(s, 0, MRE_STR_SIZE_MAX);
    vm_wstrcpy(s, (VMWSTR)&oneDisplay[19][0]);
    g_mre_curr_y = g_mre_curr_y + vm_graphic_get_character_height();
    vm_graphic_textout(buf, 0, g_mre_curr_y, s, wstrlen(s), VM_COLOR_WHITE);

    vm_graphic_flush_layer(layer_hdl, 1);
}

/*****************************************************************************
 * FUNCTION
 *  launchMyApp
 * DESCRIPTION
 *  
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void launchMyApp(void)
{

        //VMCHAR filepath[101] = "E:\\mre\\test.vxp";
        VMCHAR filepath[101] = "E:\\Videos\\Received\\gr_ugnis.3gp";
        //VMCHAR filepath[101] = "E:\\default1.jpg";
        //VMCHAR filepath[101] = "E:\\test.mp3";

        VMWCHAR filepath1[101];
        VMWSTR w_filepath;
        VMFILE fd = 0;
        VMINT size;
        vm_ascii_to_ucs2(filepath1, 256, filepath);
        size = (wstrlen(filepath1) + 1) * 2;
        w_filepath = vm_malloc(size);
        vm_wstrcpy(w_filepath, filepath1);
        fd = vm_file_open(w_filepath, MODE_READ, 0);
        vm_file_close(fd);
        
        if(fd >= 0)
        {
            //vm_start_app(w_filepath, 0, 1);
            vm_video_play_by_filepath(w_filepath);
            //vm_audio_play_file(w_filepath, 0);

            //vm_free(path);
            //vm_free(w_filepath);
            //vm_exit_app();
            //mmi_popup_display_simple((WCHAR*)L"spp send end", MMI_EVENT_SUCCESS, GRP_ID_ROOT, NULL);

            return;
        }
}