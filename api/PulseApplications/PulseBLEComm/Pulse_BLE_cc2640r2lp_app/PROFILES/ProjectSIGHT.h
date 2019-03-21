/**********************************************************************************************
 * Filename:       ProjectSIGHT.h
 *
 * Description:    This file contains the ProjectSIGHT service definitions and
 *                 prototypes.
 *
 * Copyright (c) 2015-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *************************************************************************************************/


#ifndef _PROJECTSIGHT_H_
#define _PROJECTSIGHT_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
* CONSTANTS
*/
// Service UUID
#define PROJECTSIGHT_SERV_UUID 0x2A37

//  Characteristic defines
#define PROJECTSIGHT_PULSESERVICEBPM_ID   0
#define PROJECTSIGHT_PULSESERVICEBPM_UUID  0x2BAD
#define PROJECTSIGHT_PULSESERVICEBPM_LEN  4

//  Characteristic defines
#define PROJECTSIGHT_CALORIECOUNT_ID   2
#define PROJECTSIGHT_CALORIECOUNT_UUID 0xBEEF
#define PROJECTSIGHT_CALORIECOUNT_LEN  4

//  Characteristic defines
#define PROJECTSIGHT_STATUSHEARTRATE_ID   3
#define PROJECTSIGHT_STATUSHEARTRATE_UUID 0xBEFF
#define PROJECTSIGHT_STATUSHEARTRATE_LEN  4

//  Characteristic defines
#define PROJECTSIGHT_IRCODE_ID   5
#define PROJECTSIGHT_IRCODE_UUID 0xBEEE
#define PROJECTSIGHT_IRCODE_LEN  5

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

// Callback when a characteristic value has changed
typedef void (*ProjectSIGHTChange_t)(uint16_t connHandle, uint8_t paramID, uint16_t len, uint8_t *pValue);

typedef struct
{
  ProjectSIGHTChange_t        pfnChangeCb;  // Called when characteristic value changes
  ProjectSIGHTChange_t        pfnCfgChangeCb;
} ProjectSIGHTCBs_t;



/*********************************************************************
 * API FUNCTIONS
 */


/*
 * ProjectSIGHT_AddService- Initializes the ProjectSIGHT service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t ProjectSIGHT_AddService( uint8_t rspTaskId);

/*
 * ProjectSIGHT_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t ProjectSIGHT_RegisterAppCBs( ProjectSIGHTCBs_t *appCallbacks );

/*
 * ProjectSIGHT_SetParameter - Set a ProjectSIGHT parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t ProjectSIGHT_SetParameter(uint8_t param, uint16_t len, void *value);

/*
 * ProjectSIGHT_GetParameter - Get a ProjectSIGHT parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t ProjectSIGHT_GetParameter(uint8_t param, uint16_t *len, void *value);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _PROJECTSIGHT_H_ */