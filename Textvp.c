#include "Textvp.h"

VMWSTR path[101] = {0};
VMSTR file_name = "default.txt";
int filledDsplByLines = 0;
int myFilePosition = 0;
int myFlPosBackCurr = 0;
int myFlPosBackPrev = 0;
int myFlPosBackTemp = 0;
int repeatAutoStartErr = 0;
int fileNotFound = 0;
int pageCounter = 0;
int failoGalas = 0;
int trigerisR = 0;
int trigerisM = 0;
int stopCounter = 0;
int lastPressedKey = 0;
int failoGalasPriesTai = 0;
int vmSelectrPathLen = 0;

int trigerisC1 = 0;
int trigerisC2 = 0;

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
        checkFileExist(); //Remove if '#define SUPPORT_BG' is enabled
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
		layer_hdl[0] = vm_graphic_create_layer(0, 0,vm_graphic_get_screen_width(),vm_graphic_get_screen_height(),-1);
		vm_graphic_set_clip(0,0,vm_graphic_get_screen_width(),vm_graphic_get_screen_height());
		buffer=vm_graphic_get_layer_buffer(layer_hdl[0]);
                vm_switch_power_saving_mode(turn_off_mode);
		break;
		
	case VM_MSG_PAINT:
                vm_switch_power_saving_mode(turn_off_mode);
		mre_read_file_display(path);
		break;
	case VM_MSG_INACTIVE:
                vm_switch_power_saving_mode(turn_on_mode);
		if( layer_hdl[0] != -1 )
			vm_graphic_delete_layer(layer_hdl[0]);
		
		break;	
	case VM_MSG_QUIT:
		if( layer_hdl[0] != -1 )
			vm_graphic_delete_layer(layer_hdl[0]);
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
	VMWCHAR * FILE_PATH = 0;
        VMCHAR cPageCnter[101] = {0};
        VMCHAR cLastPressedKey[101] = {0};
        VMCHAR cfailoGalas[101] = {0};
        VMCHAR cfailoGalasPriesTai[101] = {0};
        VMCHAR ctrigerisC1[101] = {0};
        VMCHAR ctrigerisC2[101] = {0};
        VMCHAR cmyFilePosition[101] = {0};
        VMCHAR cmyFlPosBackCurr[101] = {0};
        VMCHAR cmyFlPosBackPrev[101] = {0};
        VMCHAR cmyFlPosBackTemp[101] = {0};
        VMCHAR cvmSelectrPathLen[101] = {0};

        int trigerisC1X = 0;
        int trigerisC2X = 0;

 if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT_SOFTKEY) {
       if( layer_hdl[0] != -1 )
			{
				vm_graphic_delete_layer(layer_hdl[0]);
				layer_hdl[0] = -1;
			}
       vm_exit_app();
    }

    //Remove if '#define SUPPORT_BG' is enabled
    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT_SOFTKEY) { 
       mre_draw_black_rectangle();
       vm_selector_run (0, FILE_PATH, file);
       pageCounter = 1;
       lastPressedKey = 0;                 //Gal reikia ivesti numeri 5?
       myFilePosition = 0;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_UP) {
     
       mre_draw_black_rectangle();
       myFilePosition = myFlPosBackPrev;
       mre_read_file_display(path);

       if (failoGalas == 1 && pageCounter != 1 && lastPressedKey == 3){
           trigerisC1X = 1;
       }

       if (failoGalas == 0 && pageCounter != 1 && lastPressedKey == 3){
           trigerisC1X = 1;
           myFilePosition = myFlPosBackCurr; //--------------------------------------------------
       }
       
      trigerisC1 = trigerisC1X;
      if (trigerisC1X == 1) {pageCounter = pageCounter - 1;}

      lastPressedKey = 2;
    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_DOWN) {
       mre_draw_black_rectangle();
       mre_read_file_display(path);


       if (failoGalas == 0 && pageCounter == 1 && failoGalasPriesTai == 0) {
          trigerisC2X = 2;
          //vertical_scrolling_text("Testas 1");
       }

       if (failoGalas == 0 && pageCounter != 1 && lastPressedKey == 3 && failoGalasPriesTai == 0) {
          trigerisC2X = 2;
          //vertical_scrolling_text("Testas 2");

       }
       if (failoGalas == 0 && pageCounter != 1 && lastPressedKey == 2) {
          trigerisC2X = 2;
          //vertical_scrolling_text("Testas 3");

       }
       if (failoGalas == 1 && pageCounter != 1 && lastPressedKey == 2 && failoGalasPriesTai == 0) {
          trigerisC2X = 2;
          //vertical_scrolling_text("Testas 4");
       }
       if (failoGalas == 1 && failoGalasPriesTai == 0 && pageCounter != 1 && lastPressedKey == 3) {
          trigerisC2X = 2;
          failoGalasPriesTai = 1;
          //vertical_scrolling_text("Testas 5");
       }

      trigerisC2 = trigerisC2X;
      if (trigerisC2X == 2) {pageCounter = pageCounter + 1;}

      if (failoGalas != 1 && failoGalasPriesTai == 0) {
      //if (failoGalas != 1) {
         myFlPosBackTemp = myFlPosBackPrev; //------------------------------------------------------------------------
         myFlPosBackPrev = myFlPosBackCurr; //------------------------------------------------------------------------
         myFlPosBackCurr = myFilePosition;  //daroma "kune" ?
      }

      lastPressedKey = 3;

    }

    if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_NUM1) {

       mre_draw_black_rectangle();
       vertical_scrolling_ucs2_text(path);
       sprintf(cPageCnter, "Current page No: %d", pageCounter);
       vertical_scrolling_text(cPageCnter);

       vertical_scrolling_text(" ");
       sprintf(cLastPressedKey, "lastPressedKey: %d", lastPressedKey);
       vertical_scrolling_text(cLastPressedKey);
       sprintf(cfailoGalas, "failoGalas: %d", failoGalas);
       vertical_scrolling_text(cfailoGalas);
       sprintf(cfailoGalasPriesTai, "failoGalasPriesTai: %d", failoGalasPriesTai);
       vertical_scrolling_text(cfailoGalasPriesTai);
       sprintf(ctrigerisC1, "trigerisC1: %d", trigerisC1);
       vertical_scrolling_text(ctrigerisC1);
       sprintf(ctrigerisC2, "trigerisC2: %d", trigerisC2);
       vertical_scrolling_text(ctrigerisC2);
       sprintf(cmyFilePosition, "myFilePosition: %d", myFilePosition);
       vertical_scrolling_text(cmyFilePosition);
       sprintf(cmyFlPosBackCurr, "myFlPosBackCurr: %d", myFlPosBackCurr);
       vertical_scrolling_text(cmyFlPosBackCurr);
       sprintf(cmyFlPosBackPrev, "tmyFlPosBackPrev: %d", myFlPosBackPrev);
       vertical_scrolling_text(cmyFlPosBackPrev);
       sprintf(cmyFlPosBackTemp, "myFlPosBackTemp: %d", myFlPosBackTemp);
       vertical_scrolling_text(cmyFlPosBackTemp);
       sprintf(cvmSelectrPathLen, "vmSelectrPathLen: %d", vmSelectrPathLen);
       vertical_scrolling_text(cvmSelectrPathLen);

       //lastPressedKey = 4;
  
    }


    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_RIGHT) { 
    //mre_draw_black_rectangle();
    //}

    //if (event == VM_KEY_EVENT_UP && keycode == VM_KEY_LEFT) {
    //   mre_draw_black_rectangle();
    //   sprintf(cLastPressedKey, "lastPressedKey: %d", lastPressedKey);
    //   vertical_scrolling_text(cLastPressedKey);
    //   //lastPressedKey = 4;
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

VMINT file(VMWSTR FILE_PATH, VMINT wlen){
        mre_draw_black_rectangle();
	vm_wstrcpy(path, FILE_PATH);
        vmSelectrPathLen = wlen;
        stopCounter = 0;
        failoGalas = 0;
        pageCounter = 1;
        failoGalasPriesTai = 0;
        myFlPosBackPrev = 0;
        myFlPosBackTemp = 0;
	return 0;
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

    if (filledDsplByLines > vm_graphic_get_screen_height() || filledDsplByLines == 0) {
        filledDsplByLines = 0;
        vm_graphic_fill_rect(vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
            MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
            vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    }

    draw_result_string(MRE_SCREEN_START_X, filledDsplByLines, ascii_string);
    filledDsplByLines += font_height;
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
    VMWSTR display_string;
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

    VMCHAR value1[MRE_STR_SIZE_MAX + 23] = {0}; //21
    VMCHAR value21[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR vns_simbl[MRE_STR_SIZE_MAX] = {0};
    VMCHAR konv_stringas[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR knv_vns_simbl[MRE_STR_SIZE_MAX] = {0};
    VMCHAR value10[MRE_STR_SIZE_MAX + 23] = {0};
    VMCHAR nauj_strng[MRE_STR_SIZE_MAX + 23] = {0};

    f_read = vm_file_open(path, MODE_READ, FALSE);
    vm_file_seek(f_read, myFilePosition, BASE_CURR);
    //myFlPosBackCurr = myFilePosition; //-------------------------------------------------------------------

    int i, j, plotis, strng_plot, vns_simbl_plot, trigeris, isve_i_ekr_eil_sk, nauj_strng_ilg, uodegos_ilgis1;
    plotis = 0;
    strng_plot = 0;
    vns_simbl_plot = 0;
    trigeris = 0;
    isve_i_ekr_eil_sk = 0;
    nauj_strng_ilg = 0;
    uodegos_ilgis1 = 0;
       
    for (i = 0; i < 20; i++)  // 20 prasisukimu - 20 tekstiniu ekrano eiluciu, kadangi uodega 
    {
        if (isve_i_ekr_eil_sk == 20) { break; }
        vm_file_read(f_read, value1, 60, &nread); //is failo paimame 60simboliu duomenu bloka
        value1[nread] = '\0';
        myFilePosition = vm_file_tell(f_read);    //issaugome kursoariaus pozicija faile
        strcat(value10, value1);                  //prie uodegos prijungiam 60simboliu duomenu bloka
        //trim_left_spaces(value10, value10);
        //many_space_symbols_to_one(value10, value10);
        vm_ascii_to_ucs2(value21, 123, value10);  // 123
        plotis = vm_graphic_get_string_width(value21);

        if (plotis < 236 || plotis == 236) { continue; }  // jei nesigaunasi pilna eilute, prasisukam - generuojam "dviguba" fragmenta.

        char *ptr = value10;
        while (*ptr != '\0') {

            if (trigeris == 0){                                             
               sprintf(vns_simbl, "%c", *ptr);                              //paimame viena simboli
               vm_ascii_to_ucs2(knv_vns_simbl, 123, vns_simbl);             //konvertuojame simboli
               vns_simbl_plot = vm_graphic_get_string_width(knv_vns_simbl); //matuojam vieno simbolio grafini ploti
               }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 0) {     
               vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);            //konvertuojame nauja stringa
               strng_plot = vm_graphic_get_string_width(konv_stringas);     //matuojame anujo stringo grafini ploti
               trigeris = 1;                                                //ijungiame triger
               continue;                                                    //prasukam cikla !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               }

            if ((strng_plot + vns_simbl_plot) > 243 && trigeris == 1) {     
                vertical_scrolling_text(nauj_strng);                       //isvedame i ekrano eilute nauja stringa
                nauj_strng_ilg = strlen(nauj_strng);                       //skaiciuojame naujo stringo ilgi
                isve_i_ekr_eil_sk = isve_i_ekr_eil_sk + 1;                 //didiname isvestu ekrano eiluciu kounteri
                strcpy(nauj_strng, "");                                    //isvalom nauja stringa
                strng_plot = 0;                                            //uznuliname stringo ploti
                trigeris = 0;                                              //uznuliname trigeri
                continue;                                                  //prasukam cikla !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }

            if (isve_i_ekr_eil_sk == 20) { break; }

            strcat(nauj_strng, vns_simbl);
            vm_ascii_to_ucs2(konv_stringas, 123, nauj_strng);
            strng_plot = vm_graphic_get_string_width(konv_stringas);
            ptr++;
        }

        uodegos_ilgis1 = strlen(value10);
        strcpy(value10, nauj_strng);
        strcpy(nauj_strng, "");
    }

    if ((isve_i_ekr_eil_sk < 20 && strng_plot + vns_simbl_plot) < 240) {
       //trim_left_spaces(value10, value10);
       vertical_scrolling_text(value10);
    }

    //if (*ptr == '\0') { //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (vm_file_is_eof(f_read)) {
    strcpy(value10, "");     
    filledDsplByLines = 0;
    nauj_strng_ilg = 0;
    failoGalas = 1; //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    stopCounter = 1;
   
}
    vm_file_close(f_read);

    myFilePosition = (myFilePosition - (uodegos_ilgis1 - nauj_strng_ilg));
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

    if (filledDsplByLines > vm_graphic_get_screen_height() || filledDsplByLines == 0) {
        filledDsplByLines = 0;
        vm_graphic_fill_rect(vm_graphic_get_layer_buffer(layer_hdl[0]), MRE_SCREEN_START_X,
            MRE_SCREEN_START_Y, vm_graphic_get_screen_width(),
            vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    }

    //draw_result_string(MRE_SCREEN_START_X, filledDsplByLines, ascii_string);
    draw_result_ucs2_string(MRE_SCREEN_START_X, filledDsplByLines, ascii_string);
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
                       display_string_x_pos, display_string_y_pos,
                       ascii_string, wstrlen(ascii_string), VM_COLOR_WHITE);
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
    VMWCHAR * FILE_PATH = 0;

    if ((drv = vm_get_removable_driver()) < 0) { drv = vm_get_system_driver(); }
    sprintf(f_name, "%c:\\%s", drv, file_name);
    vm_ascii_to_ucs2(f_wname, MRE_STR_SIZE_MAX, f_name);
    f_read = vm_file_open(f_wname, MODE_READ, FALSE);

    if (f_read < 0) {
    fileNotFound = 1;
    vm_file_close(f_read);
    }
    else {
    vm_file_close(f_read);
    }

    if (repeatAutoStartErr == 0) {
       vm_wstrcpy(path, f_wname);
    }

    if (fileNotFound == 1 && repeatAutoStartErr == 0) {
    repeatAutoStartErr = 1;

    vm_selector_run (0, FILE_PATH, file);

    //stopCounter = 0;
    //failoGalas = 0;
    //pageCounter = 1;
    //failoGalasPriesTai = 0;
    //myFlPosBackPrev = 0;
    //myFlPosBackTemp = 0;

    repeatAutoStartErr = 0; //Disable if '#define SUPPORT_BG' is enabled
    }
    else {
        //pageCounter = pageCounter + 1;
        pageCounter = 1;
        //mre_read_file_display(path); //Enable if '#define SUPPORT_BG' is enabled
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
void mre_draw_black_rectangle(void)
{
    filledDsplByLines = 0;

	/*local variables */
    VMUINT8 *buffer;

	/* get the target buffer*/
	buffer = vm_graphic_get_layer_buffer(layer_hdl[0]);
    vm_graphic_fill_rect(buffer, MRE_SCREEN_START_X, MRE_SCREEN_START_Y, vm_graphic_get_screen_width(), 
		                 vm_graphic_get_screen_height(), VM_COLOR_BLACK, VM_COLOR_BLACK);
    vm_graphic_flush_layer(layer_hdl, 1); 
}