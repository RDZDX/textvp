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


int mysticFlPstion = 0;
int mysticUdgosIgs = 0;
int mysticNstrinlg = 0;

int trigerisC2X = 0;

int failoGalas = 0;
int failoGalasTemp = 0;
int failoGalasPriesTai = 0;
int max_plotis = 0;

// VMWSTR oneDisplay[20][61];

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

    VMCHAR cMax_plotis[101];
    VMWCHAR cMax_plotisX[101];

    VMCHAR ccurrFlPosition[101];
    VMWCHAR ccurrFlPositionX[101];
    VMCHAR ctempFlPosition[101];
    VMWCHAR ctempFlPositionX[101];
    VMCHAR cprviousFlPosit[101];
    VMWCHAR cprviousFlPositX[101];
    VMCHAR cupFilePosition[101];
    VMWCHAR cupFilePositionX[101];
    VMCHAR cmysticFlPstion[101];
    VMWCHAR cmysticFlPstionX[101];
    VMCHAR cmysticUdgosIgs[101];
    VMWCHAR cmysticUdgosIgsX[101];
    VMCHAR cmysticNstrinlg[101];
    VMWCHAR cmysticNstrinlgX[101];

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
        if (layer_hdl[0] != -1) {
            vm_graphic_delete_layer(layer_hdl[0]);
            layer_hdl[0] = -1;
        }
        vm_free(path);
        vm_exit_app();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
        mre_draw_black_rectangle();
        //lastPressedKey = 0;
        vm_selector_run(0, FILE_PATH, file);
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_DOWN) {
        trigerisC2X = 0;

        mre_draw_black_rectangle();

         failoGalasTemp = failoGalas;
         tempFlPosition = currFlPosition;
         upFilePosition = prviousFlPosit;

        mre_read_file_display(path);

        prviousFlPosit = tempFlPosition;

        if (failoGalas == 0 && pageCounter == 1 && failoGalasPriesTai == 0) {
            trigerisC2X = 2;
        }
        if (failoGalas == 0 && pageCounter != 1 && lastPressedKey == 3 &&
            failoGalasPriesTai == 0) {
            trigerisC2X = 2;
        }
        if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter != 1 &&
            lastPressedKey == 3) {
            trigerisC2X = 2;
            failoGalasPriesTai = 1;
        }
        if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter == 1 &&
            lastPressedKey == 0 && failoGalasTemp == 1) {
            // trigerisC2X = 2; //del dvieju ekranu teksto, konfliktuoja su
            // vieno ekrano tekstu
            failoGalasPriesTai = 1;
        }
        if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter == 1 &&
            lastPressedKey == 0) {
            trigerisC2X = 2;  // del dvieju ekranu teksto, konfliktuoja su vieno
                              // ekrano tekstu
            failoGalasPriesTai = 1;
        }

        if (trigerisC2X == 2) {
            pageCounter = pageCounter + 1;
        }
        lastPressedKey = 3;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_UP) {
        mre_draw_black_rectangle();
        if (lastPressedKey == 0) {
            currFlPosition = upFilePosition;
        }
        if (lastPressedKey == 3) {
            currFlPosition = upFilePosition;
            if (trigerisC2X == 2 && currFlPosition != tempFlPosition) {
                pageCounter = pageCounter - 1;
            }
            // trigerisUp = 1;
            // lastPressedKey = 2; //????
        }
        mre_read_file_display(path);
        trigerisC2X = 0;
        // lastPressedKey = 2;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {
        mre_draw_black_rectangle();
        vertical_scrolling_ucs2_text(path);

        sprintf(cPageCnter, "Current page No: %d", pageCounter);
        vm_ascii_to_ucs2(cPageCnterX, (strlen(cPageCnter) + 1) * 2, cPageCnter);
        vertical_scrolling_ucs2_text(cPageCnterX);

        //sprintf(cMax_plotis, "max_plotis: %d", max_plotis);
        //vm_ascii_to_ucs2(cMax_plotisX, (strlen(cMax_plotis) + 1) * 2, cMax_plotis);
        //vertical_scrolling_ucs2_text(cMax_plotisX);

        sprintf(ccurrFlPosition, "currFlPosition: %d", currFlPosition);
        vm_ascii_to_ucs2(ccurrFlPositionX, (strlen(ccurrFlPosition) + 1) * 2, ccurrFlPosition);
        vertical_scrolling_ucs2_text(ccurrFlPositionX);

        sprintf(ctempFlPosition, "tempFlPosition: %d", tempFlPosition);
        vm_ascii_to_ucs2(ctempFlPositionX, (strlen(ctempFlPosition) + 1) * 2, ctempFlPosition);
        vertical_scrolling_ucs2_text(ctempFlPositionX);

        sprintf(cprviousFlPosit, "prviousFlPosit: %d", prviousFlPosit);
        vm_ascii_to_ucs2(cprviousFlPositX, (strlen(cprviousFlPosit) + 1) * 2, cprviousFlPosit);
        vertical_scrolling_ucs2_text(cprviousFlPositX);

        sprintf(cupFilePosition, "upFilePosition: %d", upFilePosition);
        vm_ascii_to_ucs2(cupFilePositionX, (strlen(cupFilePosition) + 1) * 2, cupFilePosition);
        vertical_scrolling_ucs2_text(cupFilePositionX);

        sprintf(cmysticFlPstion, "mysticFlPstion: %d", mysticFlPstion);
        vm_ascii_to_ucs2(cmysticFlPstionX, (strlen(cmysticFlPstion) + 1) * 2, cmysticFlPstion);
        vertical_scrolling_ucs2_text(cmysticFlPstionX);

        sprintf(cmysticUdgosIgs, "mysticUdgosIgs: %d", mysticUdgosIgs);
        vm_ascii_to_ucs2(cmysticUdgosIgsX, (strlen(cmysticUdgosIgs) + 1) * 2, cmysticUdgosIgs);
        vertical_scrolling_ucs2_text(cmysticUdgosIgsX);

        sprintf(cmysticNstrinlg, "mysticNstrinlg: %d", mysticNstrinlg);
        vm_ascii_to_ucs2(cmysticNstrinlgX, (strlen(cmysticNstrinlg) + 1) * 2, cmysticNstrinlg);
        vertical_scrolling_ucs2_text(cmysticNstrinlgX);
    }

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT) {
    // mre_draw_black_rectangle();
    // }

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT) {
    // mre_draw_black_rectangle();
    // }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM2) {
       //mre_draw_black_rectangle();
       mre_read_file_display(path);
     }

    // if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM3) {
    //
    //    int i = 0;
    //
    //   for (i = 0; i < 21; i++) {
    //        vertical_scrolling_ucs2_text(&oneDisplay[i-1][0]);
    //   }
    // }

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
    failoGalas = 0;
    pageCounter = 1;
    failoGalasPriesTai = 0;
    failoGalasTemp = 0;
    filledDsplByLines = 0;
    currFlPosition = 0;
    tempFlPosition = 0;
    prviousFlPosit = 0;
    upFilePosition = 0;
    lastPressedKey = 0;
    trigerisC2X = 0;
    max_plotis = 0;

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

    // memset(oneDisplay, 0, sizeof(oneDisplay[0][0]) * 20 * 61);

    for (i = 0; i < 20;
         i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega
    {
        if (isve_i_ekr_eil_sk == 20) {break;}

        vm_file_read(f_read, value1, 60, &nread);  // 60
        value1[nread] = '\0';
        currFlPosition = vm_file_tell(f_read);  // Issaugome dabartine kursoriaus pozicija
        mysticFlPstion = currFlPosition;
        strcat(value10, value1);
        vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, value10, value21, (strlen(value10) + 1) * 2);
        sValue21 = (VMWSTR)value21;
        plotis = vm_graphic_get_string_width(sValue21);

        if (plotis < 228 || plotis == 228) {
            continue;
        }  //236 // 231 //230 //229 skirtumas 7 arba 8 pikseliai: simbolio maxplotis + tarpas

        char *ptr = value10;

        // while (*ptr != '\0' || *ptr != '\n') {

        while (*ptr != '\0') {
            sprintf(vns_simbl, "%c", *ptr);
            strcat(nauj_strng, vns_simbl);
            vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, nauj_strng, konv_stringas, (strlen(nauj_strng) + 1) * 2);
            sKonv_stringas = (VMWSTR)konv_stringas;
            strng_plot = vm_graphic_get_string_width(sKonv_stringas);

            if (strng_plot > 235) {  // 238 //237 //236  skirtumas 7 arba 8 pikseliai: simbolio maxplotis + tarpas
                vertical_scrolling_ucs2_text(sTemp_strng);
                nauj_strng_ilg = strlen(nauj_strng) - 1;  // uodegos koordinatems nustatyti
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                strcpy(nauj_strng, "");
                ptr - 2;
                // continue;
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

     currFlPosition = (currFlPosition - uodegosIlgis);
     mysticUdgosIgs = uodegosIlgis;
     mysticNstrinlg = nauj_strng_ilg;

    if (vm_file_is_eof(f_read)) {
        if (isve_i_ekr_eil_sk < 20 && strng_plot < 240) {
            vertical_scrolling_ucs2_text(sKonv_stringas);
            currFlPosition = myFlPosBackCurr;
        }

        strcpy(value10, "");
        filledDsplByLines = 0;
        nauj_strng_ilg = 0;
        failoGalas = 1;
        if (isve_i_ekr_eil_sk == 20 && (combUodegosIlgis - nauj_strng_ilg) != 0) {failoGalas = 0;}
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
    // if (filledDsplByLines > vm_graphic_get_screen_height() ||
    // filledDsplByLines == 0) {
    //     filledDsplByLines = 0;
    //     vm_graphic_fill_rect(
    //         vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
    //         MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
    //         vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    // }
    draw_result_ucs2_string(MRE_SCREEN_START_X, filledDsplByLines, ucs2_string);
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
                                    VMWSTR ucs2_string) {
    vm_graphic_clear_layer_bg(layer_hdl[0]);

    vm_graphic_textout_by_baseline(vm_graphic_get_layer_buffer(layer_hdl[0]),
                                   display_string_x_pos, display_string_y_pos,
                                   ucs2_string, wstrlen(ucs2_string),
                                   VM_COLOR_WHITE, 12);
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
