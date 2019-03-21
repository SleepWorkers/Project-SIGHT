/**********************************************************************************************
 * Filename:       ProjectSIGHT.c
 *
 * Description:    This file contains the implementation of the service.
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


/*********************************************************************
 * INCLUDES
 */
#include <string.h>

#include <icall.h>

/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "ProjectSIGHT.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

// ProjectSIGHT Service UUID
CONST uint8_t ProjectSIGHTUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(PROJECTSIGHT_SERV_UUID), HI_UINT16(PROJECTSIGHT_SERV_UUID)
};

// PulseServiceBPM UUID
CONST uint8_t ProjectSIGHT_PulseServiceBPMUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(PROJECTSIGHT_PULSESERVICEBPM_UUID)
};
// CalorieCount UUID
CONST uint8_t ProjectSIGHT_CalorieCountUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(PROJECTSIGHT_CALORIECOUNT_UUID)
};
// StatusHeartRate UUID
CONST uint8_t ProjectSIGHT_StatusHeartRateUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(PROJECTSIGHT_STATUSHEARTRATE_UUID)
};
// IRCode UUID
CONST uint8_t ProjectSIGHT_IRCodeUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(PROJECTSIGHT_IRCODE_UUID)
};

/*********************************************************************
 * LOCAL VARIABLES
 */

static ProjectSIGHTCBs_t *pAppCBs = NULL;

/*********************************************************************
* Profile Attributes - variables
*/

// Service declaration
static CONST gattAttrType_t ProjectSIGHTDecl = { ATT_BT_UUID_SIZE, ProjectSIGHTUUID };

// Characteristic "PulseServiceBPM" Properties (for declaration)
static uint8_t ProjectSIGHT_PulseServiceBPMProps = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic "PulseServiceBPM" Value variable
static uint8_t ProjectSIGHT_PulseServiceBPMVal[PROJECTSIGHT_PULSESERVICEBPM_LEN] = {0};
// Characteristic "CalorieCount" Properties (for declaration)
static uint8_t ProjectSIGHT_CalorieCountProps = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_NOTIFY;

// Characteristic "CalorieCount" Value variable
static uint8_t ProjectSIGHT_CalorieCountVal[PROJECTSIGHT_CALORIECOUNT_LEN] = {0};

// Characteristic "CalorieCount" CCCD
static gattCharCfg_t *ProjectSIGHT_CalorieCountConfig;
// Characteristic "StatusHeartRate" Properties (for declaration)
static uint8_t ProjectSIGHT_StatusHeartRateProps = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_NOTIFY;

// Characteristic "StatusHeartRate" Value variable
static uint8_t ProjectSIGHT_StatusHeartRateVal[PROJECTSIGHT_STATUSHEARTRATE_LEN] = {0};

// Characteristic "StatusHeartRate" CCCD
static gattCharCfg_t *ProjectSIGHT_StatusHeartRateConfig;
// Characteristic "IRCode" Properties (for declaration)
static uint8_t ProjectSIGHT_IRCodeProps = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_NOTIFY;

// Characteristic "IRCode" Value variable
static uint8_t ProjectSIGHT_IRCodeVal[PROJECTSIGHT_IRCODE_LEN] = {0};

// Characteristic "IRCode" CCCD
static gattCharCfg_t *ProjectSIGHT_IRCodeConfig

static uint8 BPMChar1UserDesp[] = "BPM Value\0";

/*********************************************************************
* Profile Attributes - Table
*/

static gattAttribute_t ProjectSIGHTAttrTbl[] =
{
  // ProjectSIGHT Service Declaration
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8_t *)&ProjectSIGHTDecl
  },
    // PulseServiceBPM Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &ProjectSIGHT_PulseServiceBPMProps
    },
      // PulseServiceBPM Characteristic Value
      {
        { ATT_UUID_SIZE, ProjectSIGHT_PulseServiceBPMUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        ProjectSIGHT_PulseServiceBPMVal
      },
        // Characteristic 1 User Description                            
      {                                                               
        { ATT_BT_UUID_SIZE, characterUUID },                       
          GATT_PERMIT_READ,                                             
          0,                                                            
          BPMChar1UserDesp                                        
      },       
    // CalorieCount Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &ProjectSIGHT_CalorieCountProps
    },
      // CalorieCount Characteristic Value
      {
        { ATT_UUID_SIZE, ProjectSIGHT_CalorieCountUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        ProjectSIGHT_CalorieCountVal
      },
      // CalorieCount CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&ProjectSIGHT_CalorieCountConfig
      },
       
    // StatusHeartRate Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &ProjectSIGHT_StatusHeartRateProps
    },
      // StatusHeartRate Characteristic Value
      {
        { ATT_UUID_SIZE, ProjectSIGHT_StatusHeartRateUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        ProjectSIGHT_StatusHeartRateVal
      },
      // StatusHeartRate CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&ProjectSIGHT_StatusHeartRateConfig
      },
    // IRCode Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &ProjectSIGHT_IRCodeProps
    },
      // IRCode Characteristic Value
      {
        { ATT_UUID_SIZE, ProjectSIGHT_IRCodeUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        ProjectSIGHT_IRCodeVal
      },
      // IRCode CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&ProjectSIGHT_IRCodeConfig
      },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t ProjectSIGHT_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                           uint16_t maxLen, uint8_t method );
static bStatus_t ProjectSIGHT_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                            uint8_t *pValue, uint16_t len, uint16_t offset,
                                            uint8_t method );

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t ProjectSIGHTCBs =
{
  ProjectSIGHT_ReadAttrCB,  // Read callback function pointer
  ProjectSIGHT_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*
 * ProjectSIGHT_AddService- Initializes the ProjectSIGHT service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t ProjectSIGHT_AddService( uint8_t rspTaskId )
{
  uint8_t status;

  // Allocate Client Characteristic Configuration table
  ProjectSIGHT_CalorieCountConfig = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( ProjectSIGHT_CalorieCountConfig == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( LINKDB_CONNHANDLE_INVALID, ProjectSIGHT_CalorieCountConfig );
  // Allocate Client Characteristic Configuration table
  ProjectSIGHT_StatusHeartRateConfig = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( ProjectSIGHT_StatusHeartRateConfig == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( LINKDB_CONNHANDLE_INVALID, ProjectSIGHT_StatusHeartRateConfig );
  // Allocate Client Characteristic Configuration table
  ProjectSIGHT_IRCodeConfig = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( ProjectSIGHT_IRCodeConfig == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( LINKDB_CONNHANDLE_INVALID, ProjectSIGHT_IRCodeConfig );
  // Register GATT attribute list and CBs with GATT Server App
  status = GATTServApp_RegisterService( ProjectSIGHTAttrTbl,
                                        GATT_NUM_ATTRS( ProjectSIGHTAttrTbl ),
                                        GATT_MAX_ENCRYPT_KEY_SIZE,
                                        &ProjectSIGHTCBs );

  return ( status );
}

/*
 * ProjectSIGHT_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
bStatus_t ProjectSIGHT_RegisterAppCBs( ProjectSIGHTCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    pAppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

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
bStatus_t ProjectSIGHT_SetParameter( uint8_t param, uint16_t len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case PROJECTSIGHT_PULSESERVICEBPM_ID:
      if ( len == PROJECTSIGHT_PULSESERVICEBPM_LEN )
      {
        memcpy(ProjectSIGHT_PulseServiceBPMVal, value, len);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case PROJECTSIGHT_CALORIECOUNT_ID:
      if ( len == PROJECTSIGHT_CALORIECOUNT_LEN )
      {
        memcpy(ProjectSIGHT_CalorieCountVal, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( ProjectSIGHT_CalorieCountConfig, (uint8_t *)&ProjectSIGHT_CalorieCountVal, FALSE,
                                    ProjectSIGHTAttrTbl, GATT_NUM_ATTRS( ProjectSIGHTAttrTbl ),
                                    INVALID_TASK_ID,  ProjectSIGHT_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case PROJECTSIGHT_STATUSHEARTRATE_ID:
      if ( len == PROJECTSIGHT_STATUSHEARTRATE_LEN )
      {
        memcpy(ProjectSIGHT_StatusHeartRateVal, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( ProjectSIGHT_StatusHeartRateConfig, (uint8_t *)&ProjectSIGHT_StatusHeartRateVal, FALSE,
                                    ProjectSIGHTAttrTbl, GATT_NUM_ATTRS( ProjectSIGHTAttrTbl ),
                                    INVALID_TASK_ID,  ProjectSIGHT_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case PROJECTSIGHT_IRCODE_ID:
      if ( len == PROJECTSIGHT_IRCODE_LEN )
      {
        memcpy(ProjectSIGHT_IRCodeVal, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( ProjectSIGHT_IRCodeConfig, (uint8_t *)&ProjectSIGHT_IRCodeVal, FALSE,
                                    ProjectSIGHTAttrTbl, GATT_NUM_ATTRS( ProjectSIGHTAttrTbl ),
                                    INVALID_TASK_ID,  ProjectSIGHT_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*
 * ProjectSIGHT_GetParameter - Get a ProjectSIGHT parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t ProjectSIGHT_GetParameter( uint8_t param, uint16_t *len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case PROJECTSIGHT_PULSESERVICEBPM_ID:
      memcpy(value, ProjectSIGHT_PulseServiceBPMVal, PROJECTSIGHT_PULSESERVICEBPM_LEN);
      break;

    case PROJECTSIGHT_CALORIECOUNT_ID:
      memcpy(value, ProjectSIGHT_CalorieCountVal, PROJECTSIGHT_CALORIECOUNT_LEN);
      break;

    case PROJECTSIGHT_STATUSHEARTRATE_ID:
      memcpy(value, ProjectSIGHT_StatusHeartRateVal, PROJECTSIGHT_STATUSHEARTRATE_LEN);
      break;

    case PROJECTSIGHT_IRCODE_ID:
      memcpy(value, ProjectSIGHT_IRCodeVal, PROJECTSIGHT_IRCODE_LEN);
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*********************************************************************
 * @fn          ProjectSIGHT_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t ProjectSIGHT_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                       uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                       uint16_t maxLen, uint8_t method )
{
  bStatus_t status = SUCCESS;

  // See if request is regarding the PulseServiceBPM Characteristic Value
if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_PulseServiceBPMUUID, pAttr->type.len) )
  {
    if ( offset > PROJECTSIGHT_PULSESERVICEBPM_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, PROJECTSIGHT_PULSESERVICEBPM_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the CalorieCount Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_CalorieCountUUID, pAttr->type.len) )
  {
    if ( offset > PROJECTSIGHT_CALORIECOUNT_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, PROJECTSIGHT_CALORIECOUNT_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the StatusHeartRate Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_StatusHeartRateUUID, pAttr->type.len) )
  {
    if ( offset > PROJECTSIGHT_STATUSHEARTRATE_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, PROJECTSIGHT_STATUSHEARTRATE_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the IRCode Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_IRCodeUUID, pAttr->type.len) )
  {
    if ( offset > PROJECTSIGHT_IRCODE_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, PROJECTSIGHT_IRCODE_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has READ permissions.
    *pLen = 0;
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  return status;
}


/*********************************************************************
 * @fn      ProjectSIGHT_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t ProjectSIGHT_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                        uint8_t *pValue, uint16_t len, uint16_t offset,
                                        uint8_t method )
{
  bStatus_t status  = SUCCESS;
  uint8_t   paramID = 0xFF;

  // See if request is regarding a Client Characterisic Configuration
  if ( ! memcmp(pAttr->type.uuid, clientCharCfgUUID, pAttr->type.len) )
  {
    // Allow only notifications.
    status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                             offset, GATT_CLIENT_CFG_NOTIFY);
  }
  // See if request is regarding the PulseServiceBPM Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_PulseServiceBPMUUID, pAttr->type.len) )
  {
    if ( offset + len > PROJECTSIGHT_PULSESERVICEBPM_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == PROJECTSIGHT_PULSESERVICEBPM_LEN)
        paramID = PROJECTSIGHT_PULSESERVICEBPM_ID;
    }
  }
  // See if request is regarding the CalorieCount Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_CalorieCountUUID, pAttr->type.len) )
  {
    if ( offset + len > PROJECTSIGHT_CALORIECOUNT_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == PROJECTSIGHT_CALORIECOUNT_LEN)
        paramID = PROJECTSIGHT_CALORIECOUNT_ID;
    }
  }
  // See if request is regarding the StatusHeartRate Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_StatusHeartRateUUID, pAttr->type.len) )
  {
    if ( offset + len > PROJECTSIGHT_STATUSHEARTRATE_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == PROJECTSIGHT_STATUSHEARTRATE_LEN)
        paramID = PROJECTSIGHT_STATUSHEARTRATE_ID;
    }
  }
  // See if request is regarding the IRCode Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, ProjectSIGHT_IRCodeUUID, pAttr->type.len) )
  {
    if ( offset + len > PROJECTSIGHT_IRCODE_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == PROJECTSIGHT_IRCODE_LEN)
        paramID = PROJECTSIGHT_IRCODE_ID;
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has WRITE permissions.
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  // Let the application know something changed (if it did) by using the
  // callback it registered earlier (if it did).
  if (paramID != 0xFF)
    if ( pAppCBs && pAppCBs->pfnChangeCb )
      pAppCBs->pfnChangeCb(connHandle, paramID, len, pValue); // Call app function from stack task context.

  return status;
}
