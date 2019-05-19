/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "ipd_visu.h"
#include "stdint.h"
#include "ipd_servo.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0    (GUI_ID_USER + 0x00)
#define ID_CHECKBOX_0    (GUI_ID_USER + 0x01)
#define ID_BUTTON_0    (GUI_ID_USER + 0x02)
#define ID_BUTTON_1    (GUI_ID_USER + 0x03)
#define ID_RADIO_0    (GUI_ID_USER + 0x04)
#define ID_TEXT_0    (GUI_ID_USER + 0x05)
#define ID_TEXT_1    (GUI_ID_USER + 0x06)
#define ID_TEXT_2    (GUI_ID_USER + 0x07)
#define ID_GRAPH_0    (GUI_ID_USER + 0x08)
#define ID_TEXT_3    (GUI_ID_USER + 0x09)
#define ID_TEXT_4    (GUI_ID_USER + 0x0A)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static GUI_POINT _aPoint[] = { {50, 50} };	// Some Points to be drawn in the graph
static GUI_POINT _Cursor[] = { {0, 0}, {5, -5}, {5, -10}, {-5, -10}, {-5, -5}, {0, 0} }; // These points describing the cursor
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "MainWindow", ID_FRAMEWIN_0, 0, 0, 480, 272, 0, 0x64, 0 },
  { CHECKBOX_CreateIndirect, "chb_servo", ID_CHECKBOX_0, 260, 151, 170, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "btn_start", ID_BUTTON_0, 261, 179, 200, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "btn_stop", ID_BUTTON_1, 260, 212, 200, 30, 0, 0x0, 0 },
  { RADIO_CreateIndirect, "rdo_function", ID_RADIO_0, 260, 5, 201, 80, 0, 0x1404, 0 },
  { TEXT_CreateIndirect, "txt_val1", ID_TEXT_0, 342, 120, 49, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "txt_val2", ID_TEXT_1, 260, 120, 69, 26, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "txt_info", ID_TEXT_2, 260, 95, 127, 20, 0, 0x64, 0 },
  { GRAPH_CreateIndirect, "gra_values", ID_GRAPH_0, 25, 5, 210, 210, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "txt_serv1", ID_TEXT_3, 11, 227, 100, 19, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "txt_serv2", ID_TEXT_4, 117, 227, 100, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)

/*********************************************************************
*
*   	_DrawCursor (little fancy marker)
*/
static void _DrawCursor(int xOrg, int yOrg, GUI_COLOR color) {
  int i;
  int x0, x1;
  int y0, y1;
  GUI_SetColor(color);
  for (i = 0; i < 5; i++) {
	x0 = xOrg + _Cursor[i].x;
	y0 = yOrg + _Cursor[i].y;
	x1 = xOrg + _Cursor[i + 1].x;
	y1 = yOrg + _Cursor[i + 1].y;
	GUI_DrawLine(x0, y0, x1, y1);
  }
}

/*********************************************************************
*
*   	_cbGraph
*/
static void _cbGraph(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
	// Draw the GRAPH with the default settings
	GRAPH_Callback(pMsg);
	// draw position data as marker
	_DrawCursor(100, 100, GUI_WHITE);
	//_DrawCursor(xVisuPos, yVisuPos, GUI_RED);
	_DrawCursor(x_pos, y_pos, GUI_RED);
	break;
  default:
	// Handle all other messages by the default callback
	GRAPH_Callback(pMsg);
	break;
  }
}


// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  static GRAPH_DATA_Handle hGraphData;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'MainWindow'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, "Image Processing Demo - - - (C) JoHa");
    //
    // Initialization of 'chb_servo'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "tracking enabled");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'btn_start'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_24_1);
    BUTTON_SetText(hItem, "START");
    //
    // Initialization of 'btn_stop'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "STOP");
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'rdo_function'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
    RADIO_SetText(hItem, "disable all", 0);
    RADIO_SetTextColor(hItem, GUI_MAKE_COLOR(0x00000000));
    RADIO_SetFont(hItem, GUI_FONT_20_1);
    RADIO_SetText(hItem, "color detection", 1);
    RADIO_SetText(hItem, "face detection", 2);
    RADIO_SetText(hItem, "read code (QR)", 3);
    //
    // Initialization of 'txt_val1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "Y:???");
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'txt_val2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "X:???");
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    //
    // Initialization of 'txt_info'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetText(hItem, "> no information available");
    //
    // Initialization of 'txt_serv1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetText(hItem, "PAN: ??? DEG");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'txt_serv2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetText(hItem, "TILT: ??? DEG");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    // USER START (Optionally insert additional code for further widget initialization)
    //
    // Initialization of 'txt_info'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
    hGraphData = GRAPH_DATA_XY_Create(GUI_RED, 100, _aPoint, GUI_COUNTOF(_aPoint));
    GRAPH_AttachData(hItem, hGraphData);
    GRAPH_SetGridVis(hItem, 1);
    GRAPH_SetGridDistX(hItem, 10);
    GRAPH_SetGridDistY(hItem, 10);
    GRAPH_SetAutoScrollbar(hItem,GUI_COORD_X,0);
    GRAPH_SetAutoScrollbar(hItem,GUI_COORD_Y,0);
    GRAPH_SetVSizeX(hItem,200);
    GRAPH_SetVSizeY(hItem,200);
    // custom callback for marker
    WM_SetCallback(hItem, _cbGraph);

    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_CHECKBOX_0: // Notifications sent by 'chb_servo'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
    	  // Sending MSG to StateMachine
    	  osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_SERVO, osWaitForever);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'btn_start'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			// Sending MSG to StateMachine
			osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_START, osWaitForever);							 
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'btn_stop'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
    	  // Reset Radio
    	  RADIO_SetValue(WM_GetDialogItem(pMsg->hWin, ID_RADIO_0),0);
    	  // Sending MSG to StateMachine
    	  osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_STOP, osWaitForever);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_RADIO_0: // Notifications sent by 'rdo_function'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
    	  if (RADIO_GetValue(WM_GetDialogItem(pMsg->hWin, ID_RADIO_0)) == 0)
    	  {
    		  osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_DISABLE, osWaitForever);
    	  }
    	  else if (RADIO_GetValue(WM_GetDialogItem(pMsg->hWin, ID_RADIO_0)) == 1)
    	  {
    	      osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_COLOR, osWaitForever);
    	  }
    	  else if (RADIO_GetValue(WM_GetDialogItem(pMsg->hWin, ID_RADIO_0)) == 2)
    	  {
    	      osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_FACE, osWaitForever);
    	  }
    	  else if (RADIO_GetValue(WM_GetDialogItem(pMsg->hWin, ID_RADIO_0)) == 3)
    	  {
    	      osMessagePut(funcCmdQueueHandle, (uint32_t) MSG_CODE, osWaitForever);
    	  }
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateMainWindow
*/
WM_HWIN CreateMainWindow(void);
WM_HWIN CreateMainWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)

// USER END

/*************************** End of file ****************************/
