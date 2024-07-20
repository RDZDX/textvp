//240x320 20      (320 / 16)
//240x240 15      (240 / 16)
//167x220 13.75   (220 / 16)

//gauti ekrano auksti
//gauti srifto auksti
//isskaiciuoti eiluciu skaiciu
//isskaiciuoti islygiavimo auksti?
//gauti max simbolio ploti?

//vm_graphic_get_screen_height
//vm_graphic_get_screen_width
//vm_graphic_get_string_baseline

//vm_font_set_font_size
//vm_font_set_font_style

#include "Textvp.h"

VMWCHAR file_pathw[100];
VMUINT8 *buffer;
VMFILE f_read;

int filledDsplByLines = 0;
int dynamicPosition = 0;
int fiksedPosition = 0;
int prviousFlPosit = 0;
int endFlPosition = 0;
int pageCounter = 0;
int lastPressedKey = 0;
VMBOOL endPressedKey = VM_FALSE;
VMBOOL failoGalasPriesTai = VM_FALSE;
int lapu_kiekis = 0;
int simbl_kiek_pirm_lape = 0;
int x5_puslapiu_adr = 0;
VMBOOL xPressedKey = VM_FALSE; // ???????????????????????????????????????
int x10_procentu_lapu = 0;
int x10_procentu_adr = 0;
VMBOOL trigeris_end = VM_FALSE;
VMBOOL plusPage = VM_FALSE;
int simblKiekEinLape = 0;
VMINT trigeris = 1;
VMBOOL trigeris1 = VM_FALSE;
VMBOOL trigeris2 = VM_FALSE;
VMBOOL trigeris5 = VM_FALSE;

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
//    vm_font_set_font_style(FALSE, FALSE, TRUE);
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

    if (message == VM_MSG_CREATE && param) {vm_wstrcpy(file_pathw, (VMWSTR)param);}

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
            if (trigeris1 == VM_TRUE) {trigeris2 = VM_TRUE;}
            if (trigeris == 0) {trigeris1 = VM_TRUE;}
            if (trigeris2 == VM_TRUE) {vm_exit_app();}
            else {mre_read_file_display(file_pathw);}

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

    VMCHAR cPageCnter[101] = {0};
    VMWCHAR cPageCnterX[101];
    VMCHAR cpercentPosition[101] = {0};
    VMWCHAR cpercentPositionX[101];

    int percentData; 

    VMBOOL trigerisq = VM_FALSE;     //trigeris nustatymui "fiksedPosition = 0" po uzkrauto puslapio       //bool
    VMBOOL countertriger = VM_FALSE; //trigeris didinti +1 kounteri ar ne                                  //bool

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
        if (layer_hdl[0] != -1) {
            vm_graphic_delete_layer(layer_hdl[0]);
            layer_hdl[0] = -1;
        }
        vm_exit_app();
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) {
        vm_selector_run(0, 0, file);
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_DOWN) {

       //Jei ne failo galas pries uzkrovima
       if (fiksedPosition != dynamicPosition) {
          prviousFlPosit = fiksedPosition;
       }

       fiksedPosition = dynamicPosition;

       mre_read_file_display(file_pathw);

       //Jei ne failo galas po uzkrovimo
       if (fiksedPosition != dynamicPosition) {
          countertriger = VM_TRUE;
       }

       //Jei failo galas ir failoGalasPriesTai == 0 && pageCounter != 1 arba dvieju lapu tekstas
       if (fiksedPosition == dynamicPosition && failoGalasPriesTai == VM_FALSE && pageCounter != 1 || fiksedPosition == dynamicPosition && prviousFlPosit == 0 && failoGalasPriesTai == VM_FALSE) {
          countertriger = VM_TRUE;
          failoGalasPriesTai = VM_TRUE;
       }

       if (dynamicPosition > 0 && dynamicPosition == prviousFlPosit && failoGalasPriesTai == VM_FALSE && pageCounter == 1) {
          countertriger = VM_TRUE;
          failoGalasPriesTai = VM_TRUE;
       }

       //Jei antras lapas ir lastPressedKey == 2 ?
       if (dynamicPosition != 0 && dynamicPosition == fiksedPosition && lastPressedKey == 2) {
          countertriger = VM_TRUE;
       }

       if (dynamicPosition == 0 && fiksedPosition == 0 && prviousFlPosit == 0) {
          countertriger = VM_FALSE;
       }

      if (pageCounter == lapu_kiekis) { countertriger = VM_FALSE; }

      //vieno lapo tekstas
      if (countertriger == VM_TRUE) {pageCounter = pageCounter + 1;}

      if (xPressedKey == VM_TRUE) {xPressedKey = VM_FALSE;}

      lastPressedKey = 3;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_UP) {

        if (fiksedPosition == prviousFlPosit && pageCounter != lapu_kiekis && xPressedKey == VM_FALSE || prviousFlPosit == 0 && dynamicPosition != 0 ) {
            dynamicPosition = 0;
            trigerisq = VM_TRUE;
        }
        else{
            dynamicPosition = prviousFlPosit;
        }

        if (pageCounter != 1 && fiksedPosition != dynamicPosition && lastPressedKey != 2) {
           pageCounter = pageCounter - 1;
        }

        mre_read_file_display(file_pathw);

        if (trigerisq == VM_TRUE) {
           fiksedPosition = 0;
           trigerisq = VM_FALSE;
        }

        lastPressedKey = 2;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {

        //percentData = (dynamicPosition * 100) / endFlPosition;
        percentData = (simblKiekEinLape * 100) / endFlPosition;

        if (failoGalasPriesTai == VM_TRUE) { percentData = 100; }
        if (lapu_kiekis < 0) { lapu_kiekis = 1 ; }

        if (endPressedKey == VM_TRUE) {
           endPressedKey = VM_FALSE;
           pageCounter = lapu_kiekis;
        }

        vertical_scrolling_ucs2_text(file_pathw);

       if (plusPage == VM_TRUE ) {
          sprintf(cPageCnter, "Page # %d of %d", pageCounter + 1, lapu_kiekis + 1);
       } else {
          sprintf(cPageCnter, "Page # %d of %d", pageCounter, lapu_kiekis);
       }

        vm_ascii_to_ucs2(cPageCnterX, (strlen(cPageCnter) + 1) * 2, cPageCnter);
        vertical_scrolling_ucs2_text(cPageCnterX);

        percentData = (dynamicPosition * 100) / endFlPosition;
        if (failoGalasPriesTai == VM_TRUE) { percentData = 100; }
        if (pageCounter == lapu_kiekis) { percentData = 100; }

        sprintf(cpercentPosition, "Percent: %d", percentData);
        vm_ascii_to_ucs2(cpercentPositionX, (strlen(cpercentPosition) + 1) * 2, cpercentPosition);
        vertical_scrolling_ucs2_text(cpercentPositionX);
        filledDsplByLines = 0;  
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM9) {

       if (endFlPosition > 380) {
       //if (endFlPosition > 1200) {
          dynamicPosition = endFlPosition - 380;
          fiksedPosition = endFlPosition - 380;
          prviousFlPosit = endFlPosition - 380;
          percentData = 100;
          failoGalasPriesTai = VM_TRUE;
          mre_read_file_display(file_pathw);
          endPressedKey = VM_TRUE;
          trigeris_end = VM_TRUE;
       }

    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM7) {

        dynamicPosition = 0;
        fiksedPosition = 0;
        prviousFlPosit = 0;
        lapu_kiekis = 0;
        failoGalasPriesTai = VM_FALSE;
        lastPressedKey = 0;
        mre_read_file_display(file_pathw);
        pageCounter = 1;
        trigeris_end = VM_FALSE;

    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM8) {

       x5_puslapiu_adr = dynamicPosition + (simbl_kiek_pirm_lape * 4);

       if (x5_puslapiu_adr < endFlPosition - 380 && endFlPosition > 380 ) {
          dynamicPosition = x5_puslapiu_adr;
          fiksedPosition = x5_puslapiu_adr;
          prviousFlPosit = x5_puslapiu_adr;
          pageCounter = pageCounter + 5;
          mre_read_file_display(file_pathw);
          xPressedKey = VM_TRUE;
       }

       if (x5_puslapiu_adr >= endFlPosition - 380 && trigeris_end == VM_FALSE) {
          dynamicPosition = endFlPosition - 380;
          fiksedPosition = endFlPosition - 380;
          prviousFlPosit = endFlPosition - 380;
          percentData = 100;
          failoGalasPriesTai = VM_TRUE;
          mre_read_file_display(file_pathw);
          endPressedKey = VM_TRUE;
          trigeris_end = VM_TRUE;
          pageCounter = lapu_kiekis;
       }

    }

 if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM6) {

       x10_procentu_lapu = (lapu_kiekis * 9) / 100;
       x10_procentu_adr = dynamicPosition + (simbl_kiek_pirm_lape * x10_procentu_lapu);

       if (x10_procentu_lapu >= 1 && x10_procentu_adr < endFlPosition - 380) {
          dynamicPosition = x10_procentu_adr;
          fiksedPosition = x10_procentu_adr;
          prviousFlPosit = x10_procentu_adr;
          pageCounter = pageCounter + x10_procentu_lapu + 1;
          mre_read_file_display(file_pathw);
          xPressedKey = VM_TRUE;
       }

       if (x10_procentu_adr >= endFlPosition - 380 && trigeris_end == VM_FALSE) {
          dynamicPosition = endFlPosition - 380;
          fiksedPosition = endFlPosition - 380;
          prviousFlPosit = endFlPosition - 380;
          percentData = 100;
          failoGalasPriesTai = VM_TRUE;
          mre_read_file_display(file_pathw);
          endPressedKey = VM_TRUE;
          trigeris_end = VM_TRUE;
       }

    }
 
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

    trigeris = 1;
    trigeris1 = VM_FALSE;
    trigeris2 = VM_FALSE;
    trigeris5 = VM_FALSE;

    vm_wstrcpy(file_pathw, FILE_PATH);
    pageCounter = 1;
    failoGalasPriesTai = VM_FALSE;
    filledDsplByLines = 0;
    dynamicPosition = 0;
    fiksedPosition = 0;
    prviousFlPosit = 0;
    lastPressedKey = 0;
    lapu_kiekis = 0;
    simbl_kiek_pirm_lape = 0;
    x5_puslapiu_adr = 0;
    xPressedKey = VM_FALSE;
    x10_procentu_lapu = 0;
    x10_procentu_adr = 0;
    trigeris_end = VM_FALSE;
    simblKiekEinLape = 0;
    f_read = vm_file_open(file_pathw, MODE_READ, FALSE);
    vm_file_seek(f_read, 0, BASE_END);
    endFlPosition = vm_file_tell(f_read);
    vm_file_close(f_read);

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

    VMUINT nread;

    VMWCHAR sKonv_stringas[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR value1[60 + 1] = {0};
    VMCHAR vns_simbl[1 + 1] = {0};
    VMCHAR value10[MRE_STR_SIZE_MAX + 23] = {0}; //uodega max 15 simboliu ilgio? 20 ?
    VMCHAR nauj_strng[60 + 1] = {0};
    VMCHAR konv_stringas[MRE_STR_SIZE_MAX + 23] = {0};      // change to unicode mod
    //VMWCHAR konv_stringas[MRE_STR_SIZE_MAX + 23];         // change to ascii mod
    int myFlPosBackCurr = 0;
    int i, plotis, strng_plot, isve_i_ekr_eil_sk, ilgism;
    char *ptr;
 
    if(trigeris5 == VM_FALSE) {mre_draw_black_rectangle();}

    f_read = vm_file_open(path, MODE_READ, FALSE);

    vm_file_seek(f_read, dynamicPosition, BASE_CURR);  // Permetame kursoriu i pozicija

    myFlPosBackCurr = dynamicPosition;
   
    plotis = 0;
    strng_plot = 0;
    isve_i_ekr_eil_sk = 0;
    plusPage = VM_FALSE;
    ilgism = 0;
    i = 0;


    //20 = vm_graphic_get_screen_height[320] / simbolio aukstis [16]

    for (i = 0; i < 20; i++) { // constants: 20 text lines on 320' display
          
        if (ilgism < 61) {
           vm_file_read(f_read, value1, 61, &nread);  // constants: on 240' display on one text line 60 slimest symbols "." or 15 widest symbols "--"
           value1[nread] = '\0';
           dynamicPosition = vm_file_tell(f_read);  // Issaugome dabartine kursoriaus pozicija faile
           strcat(value10, value1);
           ilgism = strlen(value10);
        }

        //char *ptr = value10;
        ptr = value10;

        while (*ptr != '\0') {

            if (*ptr != '\n') { 
               sprintf(vns_simbl, "%c", *ptr);
               strcat(nauj_strng, vns_simbl);
            }

            ilgism = strlen(nauj_strng);

            if (isve_i_ekr_eil_sk < 20 && ilgism > 14 || isve_i_ekr_eil_sk < 20 && *ptr == '\n' || isve_i_ekr_eil_sk < 20 && vm_file_is_eof(f_read)) {
               vm_chset_convert(VM_CHSET_UTF8, VM_CHSET_UCS2, nauj_strng, konv_stringas, (ilgism + 1) * 2);  // change to unicode mod
               //vm_ascii_to_ucs2(konv_stringas, (ilgism + 1) * 2, nauj_strng);                              // change to ascii mod
               //vm_ascii_to_ucs2(sKonv_stringas, (strlen(konv_stringas) + 1) * 2, konv_stringas);           // change to ascii mod
               vm_wstrcpy(sKonv_stringas, (VMWSTR)konv_stringas);                                            // change to unicode mod
               strng_plot = vm_graphic_get_string_width(sKonv_stringas);
            }

            // 235 = vm_graphic_get_screen_width[=240] - simbolio plotis / 3 + 2[=8/3+2]

            if (strng_plot > 235 && isve_i_ekr_eil_sk < 20 || *ptr == '\n' && isve_i_ekr_eil_sk < 20) {

                vertical_scrolling_ucs2_text(sKonv_stringas);
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;
                strcpy(nauj_strng, "");
                strng_plot = 0;
            }
            ptr++;
        }

        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
        if (vm_file_is_eof(f_read) || isve_i_ekr_eil_sk == 20) {break;}
    }

    dynamicPosition = dynamicPosition - ilgism;
    if (endFlPosition > 0 && dynamicPosition > endFlPosition) {dynamicPosition = endFlPosition;}

    simblKiekEinLape = dynamicPosition;

    if (vm_file_is_eof(f_read)) {
                                               
        if (isve_i_ekr_eil_sk < 20 && strng_plot != 0 && sKonv_stringas != L'\0') {

            vertical_scrolling_ucs2_text(sKonv_stringas);
            dynamicPosition = myFlPosBackCurr;
            if (isve_i_ekr_eil_sk == 0 && vm_wstrlen(sKonv_stringas) < 7 && dynamicPosition != 0) {
               plusPage = VM_TRUE;
            }
        }

        if (endFlPosition == dynamicPosition) {dynamicPosition = myFlPosBackCurr;}

        strcpy(value10, "");
    }

    vm_file_close(f_read);

    if (lapu_kiekis == 0) {

       lapu_kiekis = endFlPosition / dynamicPosition;
       if (((float)endFlPosition / dynamicPosition) - lapu_kiekis != 0) {lapu_kiekis = lapu_kiekis + 1;}

    }

    if (simbl_kiek_pirm_lape == 0) {

       simbl_kiek_pirm_lape = dynamicPosition;

    }

    filledDsplByLines = 0;
    trigeris5 = VM_TRUE;
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
    int font_height = 16;
    //int i;
    int abc = 0;

    // 12 = vm_graphic_get_string_baseline

    if (filledDsplByLines == 0) {
       abc = 2;
       mre_draw_black_rectangle();
    }

    max_height = vm_graphic_get_screen_height();
    vm_graphic_clear_layer_bg(layer_hdl[0]);
    vm_graphic_textout_by_baseline(buffer, MRE_SCREEN_START_X, filledDsplByLines + abc, ucs2_string, vm_wstrlen(ucs2_string), VM_COLOR_WHITE, 12);
    //vm_graphic_textout_by_baseline(buffer, MRE_SCREEN_START_X, filledDsplByLines + abc, ucs2_string, vm_wstrlen(ucs2_string), VM_COLOR_BLACK, 12);
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

    VMWCHAR appName[100];

    create_app_txt_filename(appName, "txt");
    //create_auto_full_path_name(file_pathw, appName);
    if (vm_wstrlen(file_pathw) == 0) {create_auto_full_path_name(file_pathw, appName);}

    f_read = vm_file_open(file_pathw, MODE_READ, FALSE);

    pageCounter = 1;

    if (f_read < 0) {
        vm_file_close(f_read);
        trigeris = vm_selector_run(0, 0, file);
    } else {
        vm_file_seek(f_read, 0, BASE_END);
        endFlPosition = vm_file_tell(f_read);
        vm_file_close(f_read);
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

    vm_graphic_fill_rect(buffer, MRE_SCREEN_START_X, MRE_SCREEN_START_Y, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    //vm_graphic_fill_rect(buffer, MRE_SCREEN_START_X, MRE_SCREEN_START_Y, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_COLOR_WHITE, VM_COLOR_WHITE);
    vm_graphic_flush_layer(layer_hdl, 1);
}
/*****************************************************************************
 * FUNCTION
 *  create_app_txt_filename
 * DESCRIPTION
 *  
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void create_app_txt_filename(VMWSTR text, VMSTR extt) {

    VMWCHAR fullPath[100];
    VMWCHAR appName[100];
    VMWCHAR wfile_extension[4];

    vm_get_exec_filename(fullPath);
    vm_get_filename(fullPath, appName);
    vm_ascii_to_ucs2(wfile_extension, 8, extt);
    vm_wstrncpy(text, appName, vm_wstrlen(appName) - 3);
    vm_wstrcat(text, wfile_extension);

}
/*****************************************************************************
 * FUNCTION
 *  create_auto_full_path_name
 * DESCRIPTION
 *  
 * PARAMETERS
 *
 * RETURNS
 *
 *****************************************************************************/
void create_auto_full_path_name(VMWSTR result, VMWSTR fname) {

    VMINT drv;
    VMCHAR fAutoFileName[100];
    VMWCHAR wAutoFileName[100];

    if ((drv = vm_get_removable_driver()) < 0) {
       drv = vm_get_system_driver();
    }

    sprintf(fAutoFileName, "%c:\\", drv);
    vm_ascii_to_ucs2(wAutoFileName, (strlen(fAutoFileName) + 1) * 2, fAutoFileName);
    vm_wstrcat(wAutoFileName, fname);
    vm_wstrcpy(result, wAutoFileName);

}