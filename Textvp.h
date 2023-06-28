/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL? CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *  mre_file_text_op.h
 * 
 * Project:
 * --------
 *  MRE
 * 
 * Description:
 * ------------
 *  Sample code for creating a file writing on it diplaying its content and modifying time.
 * 
 * Author:
 * -------
 *  Shailendra Singh (mtk33172)
 * 
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Log$
 * 
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _VRE_APP_WIZARDTEMPLATE_
#define	_VRE_APP_WIZARDTEMPLATE_

#define MRE_LOG_ON

#define MRE_SPACE_BTW_LN            (10)
#define MRE_STR_SIZE_MAX            (100)
#define MRE_SET_X                   (0)
#define MRE_SET_Y                   (0)
#define MRE_SET_SRC_LEFT_TOP_X      (0)
#define MRE_SET_SRC_LEFT_TOP_Y      (0)
#define MRE_SET_VAL                 (0)
#define MRE_SET_MARGIN              (2)
#define MRE_FILE_CREATE_FAILED  	(-5)
#define MRE_TEXT_BOX_FAILED	        (-2)
#define MRE_FILE_OPEN_FAILED        (-3)
#define MRE_FILE_NOT_WRITTEN        (-4)
#define MRE_TEXTBOX_CANCEL          (2)
#define MRE_ERROR                   (-1)
#define MRE_SCILENT                 (100)
#define MRE_GET_FILE_TIME_FAILED    (-6)
#define	SUPPORT_BG
#define MRE_DEF_STRING_SIZE	        (30)
#define MRE_INTIAL_VALUE		(0)

typedef enum mre_iput_type_textbox
{
    INPUT_TYPE1, 
    INPUT_TYPE2, 
    INPUT_TYPE3,
    TOTAL_INPUT_TYPE 
}mre_iput_type_textbox;

/* included files */
#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "string.h"
#include "stdio.h"
#include "vmlog.h"
#include "vmmullang.h"
/* ---------------------------------------------------------------------------
 * global variables
 * ------------------------------------------------------------------------ */


VMINT		layer_hdl[1];				////layer handle array.

VMINT g_mre_curr_x;
VMINT g_mre_curr_y;
VMWSTR g_mre_textbox_text;
VMINT g_mre_textbox_state;
VMINT g_mre_subcontext;
VMINT g_mre_drv;


/* ---------------------------------------------------------------------------
 * local variables
 * ------------------------------------------------------------------------ */



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
void handle_sysevt (VMINT message, VMINT param);

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
void handle_keyevt (VMINT event, VMINT keycode);

/*****************************************************************************
 * FUNCTION
 *  handle_penevt
 * DESCRIPTION
 *  This function handles touch panel events 
 * PARAMETERS
 *  event				[IN]      event no
 *  x					[IN]      x cordinate of cursor point on screen
 *  y					[IN]      y cordinate of cursor point on screen
 * RETURNS
 *	none
*****************************************************************************/
void handle_penevt (VMINT event, VMINT x, VMINT y);
/*****************************************************************************
 * FUNCTION
 *  mre_create_file
 * DESCRIPTION
 *  This function creates a file with given name in a drive set earlier 
 * PARAMETERS
 *  file name				[IN]      name of file
 * RETURNS
 *	result                  [OUT]     some code for error and success   
*****************************************************************************/
VMINT mre_create_file(VMSTR file_name);
/*****************************************************************************
 * FUNCTION
 *  mre_start_menu
 * DESCRIPTION
 *  This function displays menu list on the screen for selection 
 * PARAMETERS
 *  none
 * RETURNS
 *	none
*****************************************************************************/
void mre_start_menu(void);
/*****************************************************************************
 * FUNCTION
 *  mre_write_file
 * DESCRIPTION
 *  This function writes on the file given 
 * PARAMETERS
 *  file name				[IN]      name of file
 * RETURNS
 *	result                  [OUT]     some code for error and success   
*****************************************************************************/
VMINT mre_write_file(VMSTR file_name);
/*****************************************************************************
 * FUNCTION
 *  mre_show_text
 * DESCRIPTION
 *  This function takes text string and displays it on the screen 
 * PARAMETERS
 *  text				[IN]      Text string in ASCII or GB2312 format
 * RETURNS
 *	none
*****************************************************************************/
void mre_show_text(VMSTR text);
/*****************************************************************************
 * FUNCTION
 *  mre_textbox_handle
 * DESCRIPTION
 *  This function takes text string and saves it global variable 
 * PARAMETERS
 *  state               [IN]      state of input text box
 *  text				[IN]      Text string in ASCII or GB2312 format
 * RETURNS
 *	none
*****************************************************************************/
void mre_textbox_handle(VMINT state, VMWSTR text);
/*****************************************************************************
 * FUNCTION
 *  mre_submenu
 * DESCRIPTION
 *  This function displays sub menu list on the screen for selection 
 * PARAMETERS
 *  none
 * RETURNS
 *	none
*****************************************************************************/
void mre_submenu(void);
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
VMINT mre_read_file_display(VMSTR file_name);
/*****************************************************************************
 * FUNCTION
 *  mre_file_result
 * DESCRIPTION
 *  This function decides if error found then displays error 
 *  otherwise remain scilent 
 * PARAMETERS
 *  result				[IN]      result
 * RETURNS
 *	none
*****************************************************************************/
void mre_file_result(VMINT result);
/*****************************************************************************
 * FUNCTION
 *  mre_check_modify_time
 * DESCRIPTION
 *  This function displays file's modified time 
 * PARAMETERS
 *  file name				[IN]      name of file
 * RETURNS
 *	result                  [OUT]     some code for error and success 
*****************************************************************************/
VMINT mre_check_modify_time(VMSTR file_name);
/*****************************************************************************
 * FUNCTION
 *  mre_text_box_display_result
 * DESCRIPTION
 *  This function takes text string and displays it on the screen 
 * PARAMETERS
 *  state               [IN]      state of input text box
 *  text				[IN]      Text string in ASCII or GB2312 format
 * RETURNS
 *	none
*****************************************************************************/
void mre_text_box_display_result(VMINT state, VMWSTR text);
/*****************************************************************************
 * FUNCTION
 *  mre_set_subcontext
 * DESCRIPTION
 *  This function sets flag for context 
 * PARAMETERS
 *  val			         [IN]      it is true or false
 * RETURNS
 *	none
*****************************************************************************/
void mre_set_subcontext(VMINT val);
/*****************************************************************************
 * FUNCTION
 *  mre_get_subcontext
 * DESCRIPTION
 *  This function gets flag for context 
 * PARAMETERS
 *  none
 * RETURNS
 *	g_mre_subcontext    [OUT]      it is true or false
*****************************************************************************/
VMINT mre_get_subcontext(void);
/*****************************************************************************
 * FUNCTION
 *  mre_set_textbox_text
 * DESCRIPTION
 *  This function saves the text of input textbox in a global variable 
 * PARAMETERS
 *  text			         [IN]      text from input textbox
 * RETURNS
 *	none
*****************************************************************************/
void mre_set_textbox_text(VMWSTR text);
/*****************************************************************************
 * FUNCTION
 *  mre_get_textbox_text
 * DESCRIPTION
 *  This function returns pointer to text of input textbox saved in a global 
 *  variable 
 * PARAMETERS
 *  none
 * RETURNS
 *	g_mre_textbox_text    [OUT]      it is pointer to text stored in global 
 *                                   vaiable
*****************************************************************************/
VMWSTR mre_get_textbox_text(void);
/*****************************************************************************
 * FUNCTION
 *  mre_set_textbox_state
 * DESCRIPTION
 *  This function saves the state of input textbox in a global variable 
 * PARAMETERS
 *  state			         [IN]      it is ok or cancel
 * RETURNS
 *	none
*****************************************************************************/
void mre_set_textbox_state(VMINT state);
/*****************************************************************************
 * FUNCTION
 *  mre_get_textbox_state
 * DESCRIPTION
 *  This function returns the state of input textbox saved in a global variable 
 * PARAMETERS
 *  none
 * RETURNS
 *	g_mre_textbox_state    [OUT]      it is ok or cancel
*****************************************************************************/
VMINT mre_get_textbox_state(void);
/*****************************************************************************
 * FUNCTION
 *  mre_get_drv
 * DESCRIPTION
 *  This function returns a no corresponding to a drive found
 * PARAMETERS
 *  none
 * RETURNS
 *  g_mre_drv            [OUT]      drive found on device
*****************************************************************************/
VMINT mre_get_drv(void);
/*****************************************************************************
 * FUNCTION
 *  mre_set_drv
 * DESCRIPTION
 *  This function stores a no corresponding to a drive found
 * PARAMETERS
 *  none
 * RETURNS
 *  none
*****************************************************************************/
void mre_set_drv(void);
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
void mre_set_global_data (void);
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
void mre_set_curr_x (VMINT x);
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
VMINT mre_get_curr_x (void);
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
void mre_set_curr_y (VMINT y);
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
VMINT mre_get_curr_y (void);
/*****************************************************************************
 * FUNCTION
 *  mre_show_input_textbox
 * DESCRIPTION
 *  This function displays input textbox
 * PARAMETERS
 *  input_type			  [IN]      type of input textbox
 * RETURNS
 *	none
*****************************************************************************/
VMINT mre_show_input_textbox(VMINT input_type);
/*****************************************************************************
 * FUNCTION
 *  draw_http_result_string
 * DESCRIPTION
 *  This function displayes state of http connection and response head, body on screen
 * PARAMETERS
 *  none
 * RETURNS
 *	none
*****************************************************************************/
static void draw_http_result_string(int x, int y, VMSTR ascii_string);
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
void vertical_scrolling_text(VMSTR ascii_string);

void handle_exitevt(void* ctx);

void mre_draw_rectangle(void);

void testDimensions (void);

void testDimensions1 (void);

VMINT mre_read_file_to_array(VMSTR file_name);

void trim_left_spaces(char *reslt_data, char *inp_data);

void trim_right_spaces(char *reslt_data, char *inp_data);

void clean_text(char *reslt_data, char *inp_data);

void many_space_symbols_to_one(char *reslt_data, char *inp_data);

void myTest1(void);

void myTest2(void);

#endif


