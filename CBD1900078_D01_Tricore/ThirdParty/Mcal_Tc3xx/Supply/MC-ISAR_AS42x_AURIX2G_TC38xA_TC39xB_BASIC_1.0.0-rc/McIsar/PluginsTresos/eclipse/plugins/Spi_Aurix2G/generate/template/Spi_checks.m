[!/*
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Spi_checks.m                                                  **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-09-03                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Spi.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Spi Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!//[cover parentID={1B009FD4-5CDB-48ff-B5D9-9E9E257B7717}][/cover][!//

[!AUTOSPACING!]
[!/*****************************************************************************
TRACEABILITY : [cover parentID={FE329A07-6B91-4eb2-B384-C558592F7B95}][/cover]
MACRO: Spi_CGVerifyChannelConfig
Macro to verify channel specific configuration errors
******************************************************************************/!]
[!MACRO "Spi_CGVerifyChannelConfig"!][!//
[!NOCODE!][!//

  [!// Verify no channel is EB when SpiChannelBuffersAllowed is 0
  [!IF "(num:i(SpiGeneral/SpiChannelBuffersAllowed) = num:i(0)) and (count(SpiDriver/SpiChannel/*[SpiChannelType = 'EB']) > num:i(0))"!]
    [!ERROR!]
     If 'SpiChannelBuffersAllowed = 0', then EB channels are not allowed to be configured.
      ([!"node:path(SpiDriver/SpiChannel/*[SpiChannelType = 'EB'])"!])
    [!ENDERROR!]
  [!ENDIF!]

  [!// Verify no channel is IB when SpiChannelBuffersAllowed is 1
  [!IF "(num:i(SpiGeneral/SpiChannelBuffersAllowed) = num:i(1)) and (count(SpiDriver/SpiChannel/*[SpiChannelType = 'IB']) > num:i(0))"!]
    [!ERROR!]
     If 'SpiChannelBuffersAllowed = 1', then IB channels are not allowed to be configured.
      ([!"node:path(SpiDriver/SpiChannel/*[SpiChannelType = 'EB'])"!])
    [!ENDERROR!]
  [!ENDIF!]

  [!// Verify there must be atleast a EB and IB channel when SpiChannelBuffersAllowed is 2
  [!IF "(num:i(SpiGeneral/SpiChannelBuffersAllowed) = num:i(2)) and
    ((count(SpiDriver/SpiChannel/*[SpiChannelType = 'EB']) = num:i(0)) or (count(SpiDriver/SpiChannel/*[SpiChannelType = 'IB']) = num:i(0)))"!]
    [!ERROR!]
     If 'SpiChannelBuffersAllowed = 2', then both EB and IB channels should be configured, else the SpiChannelAllowed should be modified.
     (Number of IB channels [!"count(SpiDriver/SpiChannel/*[SpiChannelType = 'IB'])"!]) and
     (Number of EB channels [!"count(SpiDriver/SpiChannel/*[SpiChannelType = 'EB'])"!])
    [!ENDERROR!]
  [!ENDIF!]

  [!// Verify if default data size should be less than data width
  [!LOOP "SpiDriver/SpiChannel/*"!]
  [!// If default data exists check data width
    [!IF "node:exists(./SpiDefaultData/*[1])"!]
      [!IF "((node:value(./SpiDefaultData/*[1]) > (bit:shl(num:i(1),node:value(./SpiDataWidth)) - num:i(1))))"!]
        [!ERROR!]
          Default value is more than the specified Channel data width.
          ([!"node:path(./SpiDefaultData/*[1])"!])
        [!ENDERROR!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!][!// end of  LOOP "SpiDriver/SpiChannel/*"

  [!// Verify used channel exists
  [!LOOP "SpiDriver/SpiJob/*/SpiChannelList/*"!]
    [!IF "not(node:exists(node:value(./SpiChannelAssignment)))"!]
      [!ERROR!]
         SpiChannel reference in the Job container does not exists.
         ([!"node:path(.)"!])
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDLOOP!][!// end of LOOP "SpiDriver/SpiJob/*/SpiChannelList/*"

  [!// Verify each job is defined as synchronous or asynchornous job and size limit for EB channels when level delivered is 2
  [!IF "num:i(SpiGeneral/SpiLevelDelivered) = num:i(2)"!]
    [!LOOP "SpiDriver/SpiJob/*[count(./SpiHwUnitSynchronous/*) != num:i(1)]"!]
      [!ERROR!]
        For SpiLevelDelivered 2, it is mandatory to specify the type of the job (sync/async).
        ([!"node:path(./SpiHwUnitSynchronous)"!])
      [!ENDERROR!]
    [!ENDLOOP!]
  [!ENDIF!][!// end of IF "num:i(SpiGeneral/SpiLevelDelivered) = num:i(2)"

  [!// Verify all channels are assigned to job
  [!LOOP "SpiDriver/SpiChannel/*"!]
    [!VAR "Spi_IBChnlName"="node:name(.)"!]
    [!IF "count(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]) = num:i(0)"!]
    [!ERROR!]
    Channel [!"$Spi_IBChnlName"!] is not assigned to any Job, ([!"node:path(.)"!])
    [!ENDERROR!]
    [!ENDIF!]
  [!ENDLOOP!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={461DFA9E-C597-4c37-AA9B-36D9424DCAD1}][/cover]
MACRO: Spi_CGVerifyJobConfig
Macro to verify Job specific configuration errors
******************************************************************************/!]
[!MACRO "Spi_CGVerifyJobConfig"!][!//
[!NOCODE!][!//

[!// Verify if a job type is asynchornous when level delivered is 0
[!IF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(0))"!]
[!// Level delivered is 0
  [!LOOP "SpiDriver/SpiJob/*/SpiHwUnitSynchronous/*[node:value(.) = 'ASYNCHRONOUS']"!]

  [!// For all job's type is asynchronous generates error
    [!ERROR!]
      For SpiLevelDelivered 0, all Jobs should be configured as Synchronous.
      ([!"node:path(.)"!])
      (Hint - Also removing the container SpiHwUnitSynchronous, ensures that all are Synchronous(default) in LEVEL 0)
    [!ENDERROR!]

  [!ENDLOOP!]
[!ENDIF!][!// end of IF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(0))"

[!// Verify if a job type is synchornous when level delivered is 1
[!IF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(1))"!]
  [!LOOP "SpiDriver/SpiJob/*/SpiHwUnitSynchronous/*[node:value(.) = 'SYNCHRONOUS']"!]
    [!ERROR!]
      For SpiLevelDelivered 1, all jobs should be configured as Asynchronous.
      ([!"node:path(.)"!])
      (Hint - Also removing the container SpiHwUnitSynchronous, ensures that all are Asynchronous(default) in LEVEL 1)
    [!ENDERROR!]
  [!ENDLOOP!]
[!ENDIF!][!// end of IF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(1))"

[!//  Verify a channel exists having same channel ID it should be unique across channel
[!LOOP "SpiDriver/SpiJob/*/SpiChannelList/*"!]
  [!IF "count(./../*[SpiChannelIndex = node:current()/SpiChannelIndex]) > num:i(1)"!]
    [!ERROR!]
      SpiChannelIndex '[!"node:current()/SpiChannelIndex"!]' is defined more than once, it should be unique. Update the channel Index for the following node.
      ([!"node:path(.)"!])
    [!ENDERROR!]
  [!ENDIF!]
[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiJob/*/SpiChannelList/*"

[!// Verify for a job sum of all assigned channel's data length is smaller than 8190 due to move counter limitation
[!IF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(2))"!]
[!LOOP "SpiDriver/SpiJob/*[./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS']"!]
  [!VAR "Spi_JobName" = "node:name(.)"!]
  [!IF "./SpiFrameBasedCS = 'false'"!]
      [!VAR "SumOfChannelLengthPerJob" = "num:i(0)"!]
      [!LOOP "./SpiChannelList/*"!]
          [!// add data length for a channel from SpiIbNBuffers assigned to the current job
          [!VAR "SumOfChannelLengthPerJob" = "$SumOfChannelLengthPerJob + num:i(node:value(node:ref(./SpiChannelAssignment)/SpiIbNBuffers))"!]
      [!ENDLOOP!]
      [!// sum is greater than 8190 generate error
      [!IF "$SumOfChannelLengthPerJob > num:i(8190)"!]
          [!ERROR!]
              Data buffers size of all the channels in the asynchonous job [!"$Spi_JobName"!] is greater than 8190 ([!"num:i($SumOfChannelLengthPerJob)"!]), when frame based chip select is false.
          ([!"node:path(.)"!])
          [!ENDERROR!]
      [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiJob/*"
[!ELSEIF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(1))"!]
[!LOOP "SpiDriver/SpiJob/*"!]
  [!VAR "Spi_JobName" = "node:name(.)"!]
  [!IF "./SpiFrameBasedCS = 'false'"!]
      [!VAR "SumOfChannelLengthPerJob" = "num:i(0)"!]
      [!LOOP "./SpiChannelList/*"!]
          [!// add data length for a channel from SpiIbNBuffers assigned to the current job
          [!VAR "SumOfChannelLengthPerJob" = "$SumOfChannelLengthPerJob + num:i(node:value(node:ref(./SpiChannelAssignment)/SpiIbNBuffers))"!]
      [!ENDLOOP!]
      [!// sum is greater than 8190 generate error
      [!IF "$SumOfChannelLengthPerJob > num:i(8190)"!]
          [!ERROR!]
              Data buffers size of all the channels in the asynchonous job [!"$Spi_JobName"!] is greater than 8190 ([!"num:i($SumOfChannelLengthPerJob)"!]), when frame based chip select is false.
          ([!"node:path(.)"!])
          [!ENDERROR!]
      [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiJob/*"
[!ENDIF!]


[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={BC338B54-07B6-47ba-8FC3-E5188077D158}][/cover]
MACRO: Spi_CGVerifyExternalDeviceConfig
Macro to verify External device specific configuration errors
******************************************************************************/!]
[!MACRO "Spi_CGVerifyExternalDeviceConfig"!][!//
[!NOCODE!][!//

[!// For all configured external devices
[!LOOP "SpiDriver/SpiExternalDevice/*"!]

  [!// Chip select is on and no configuration for CS exists generate error
  [!IF "((node:value(./SpiEnableCs) = 'true') and (count(./SpiCsSelection/*) = num:i(0)))"!]
    [!ERROR!]
      If SpiEnableCS is true, then the paramter SpiCsSelection should specify the kind of Chip Select.
        ([!"node:path(./SpiCsSelection)"!])
    [!ENDERROR!]
  [!ENDIF!]

  [!// Chip select is on and no configuration for CS exists verify configuration
  [!IF "((node:value(./SpiEnableCs) = 'true') and (count(./SpiCsSelection/*) = num:i(1)))"!]

    [!// CS is via GPIO and no configuration of GPIO exists generate error
    [!IF "(node:value(./SpiCsSelection/*[1]) = 'CS_VIA_GPIO') and (count(./SpiCsGpio/*) = num:i(0))"!]
      [!ERROR!]
        If SpiEnableCS is true and CS_VIA_GPIO is selected, then the paramter SpiCsGpio should specify the Port Pin.
          ([!"node:path(./SpiCsGpio)"!])
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDIF!]

  [!VAR "Spi_MacTempQSPIHw"="./SpiHwUnit"!]
  [!VAR "Spi_MacTempQSPIChannel"="./SpiCsIdentifier"!]
  [!VAR "Spi_MacCsPol"="./SpiCsPolarity"!]

  [!// check if CS polarity for a QSPI hardware unit is same else generate error
  [!LOOP "../*[(SpiHwUnit = $Spi_MacTempQSPIHw) and (SpiCsIdentifier = $Spi_MacTempQSPIChannel)]"!]
    [!IF "./SpiCsPolarity != $Spi_MacCsPol"!]
      [!ERROR!]
        CS polarity is configured as both 'active HIGH' and 'active LOW', for the same QSPI Hw unit, i.e., [!"$Spi_MacTempQSPIHw"!], [!"$Spi_MacTempQSPIChannel"!]
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDLOOP!][!// end of LOOP "../*[(SpiHwUnit = $Spi_MacTempQSPIHw) and (SpiCsIdentifier = $Spi_MacTempQSPIChannel)]"

  [!VAR "Spi_DeviceExistsFlag" = "num:i(0)"!]
  [!VAR "Spi_CurrentDeviceName" = "node:name(.)"!]
      [!LOOP "../../SpiJob/*"!]
        [!IF "node:name(node:ref(./SpiDeviceAssignment)) = $Spi_CurrentDeviceName"!]
           [!VAR "Spi_DeviceExistsFlag" = "num:i(1)"!]
           [!BREAK!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$Spi_DeviceExistsFlag = num:i(0)"!]
        [!ERROR!]
            All configured External device should be assigned to atleast one job [!"$Spi_CurrentDeviceName"!] is not assigned to any sequence
        [!ENDERROR!]
    [!ENDIF!]

[!ENDLOOP!][!// End of LOOP "SpiDriver/SpiExternalDevice/*"



[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGVerifySpiHwConfig
TRACEABILITY : [cover parentID={912CC3F7-A0B2-4ef6-91F4-DDBA3A860844}][/cover]
Macro to verify Spi Hw configuration errors
******************************************************************************/!]
[!MACRO "Spi_CGVerifySpiHwConfig"!][!//
[!NOCODE!][!//

[!// For all QSPIx kernel
[!FOR "QspiIndex" = "0" TO "5"!]

  [!// Check if a QSPIx unit is assigned to a external device and the configuration for QSPIx exists else generate error
  [!IF "(count(SpiDriver/SpiExternalDevice/*[SpiHwUnit = concat('QSPI',$QspiIndex)]) > num:i(0))
        and (count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]) = num:i(0))"!]
    [!ERROR!]
      QSPI[!"$QspiIndex"!] hw is used in the SpiExternal device. Add the Qspi[!"$QspiIndex"!] configuration in SpiHwConfigurationQspi[!"$QspiIndex"!] container.
      ([!"node:path(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi)"!])
    [!ENDERROR!]
  [!ENDIF!]

  [!// Check for all configured QSPIx when level delivered is 1
  [!IF "(num:i(SpiGeneral/SpiLevelDelivered) = num:i(1)) and
        (count(SpiDriver/SpiExternalDevice/*[SpiHwUnit = concat('QSPI',$QspiIndex)]) > num:i(0))"!]

    [!// If DMA channel is not configured for the QSPIx generate error
    [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*) = num:i(0)"!]
      [!ERROR!]
        For SpiLevelDelivered 1, All the jobs are asynchronous and are handled via DMA. Hence DMA configuration should be present for QSPI[!"$QspiIndex"!]
        ([!"node:path(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi)"!])
      [!ENDERROR!]
    [!ENDIF!]

    [!// If RX DMA channel refference configured for the QSPIx does not exists generate error
    [!IF "not(node:exists(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelReceptionRef)))"!]
      [!ERROR!]
        DMA Rx Channel reference does not exist for the QSPI[!"$QspiIndex"!].
        ([!"node:path(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelReceptionRef)"!])
      [!ENDERROR!]
    [!ENDIF!]

    [!// If TX DMA channel refference configured for the QSPIx does not exists generate error
    [!IF "not(node:exists(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelTransmissionRef)))"!]
      [!ERROR!]
        DMA Tx Channel reference does not exist for the QSPI[!"$QspiIndex"!].
        ([!"node:path(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelTransmissionRef)"!])
      [!ENDERROR!]
    [!ENDIF!]

  [!ENDIF!][!// end if to check level delivered and QSPIx is configured

  [!// If level delivered is 2
  [!IF "num:i(SpiGeneral/SpiLevelDelivered) = num:i(2)"!]

    [!// For all asynchornous jobs
    [!LOOP "SpiDriver/SpiJob/*[./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS']"!]

      [!// If DMA channel is not configured for the QSPIx generate error
      [!IF "(node:ref(./SpiDeviceAssignment)/SpiHwUnit = concat('QSPI',$QspiIndex))
        and (count(../../../SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*) = num:i(0))"!]
        [!ERROR!]
           For SpiLevelDelivered 2, The jobs configured as asynchronous, are handled via DMA. Hence DMA configuration should be present for QSPI[!"$QspiIndex"!]
          ([!"node:path(../../../SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi)"!])
        [!ENDERROR!]
      [!ENDIF!]

      [!// If RX DMA channel refference configured for the QSPIx does not exists generate error
      [!IF "(node:ref(./SpiDeviceAssignment)/SpiHwUnit = concat('QSPI',$QspiIndex))
        and not(node:exists(node:value(../../../SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelReceptionRef)))"!]
        [!ERROR!]
          DMA Rx Channel reference does not exist for the QSPI[!"$QspiIndex"!].
          ([!"node:path(../../../SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelReceptionRef)"!])
        [!ENDERROR!]
      [!ENDIF!]

      [!// If TX DMA channel refference configured for the QSPIx does not exists generate error
      [!IF "(node:ref(./SpiDeviceAssignment)/SpiHwUnit = concat('QSPI',$QspiIndex))
        and not(node:exists(node:value(../../../SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelTransmissionRef)))"!]
        [!ERROR!]
          DMA Tx Channel reference does not exist for the QSPI[!"$QspiIndex"!].
          ([!"node:path(../../../SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = concat('QSPI',$QspiIndex)]/SpiHwDmaConfigurationQspi/*/SpiHwDmaChannelTransmissionRef)"!])
        [!ENDERROR!]
      [!ENDIF!]

    [!ENDLOOP!][!// end of LOOP "SpiDriver/SpiJob/*[./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS']"

  [!ENDIF!][!// end of IF "num:i(SpiGeneral/SpiLevelDelivered) = num:i(2)"

[!ENDFOR!][!// end of FOR "QspiIndex" = "0" TO "5"

[!VAR "DMAChnl"="''"!]

[!// For all configured QSPIx
[!LOOP "SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*/SpiHwDmaConfigurationQspi/*"!]

  [!// If DMA channel for RX and TX is same generate error
  [!IF "(./SpiHwDmaChannelReceptionRef) = (./SpiHwDmaChannelTransmissionRef)"!]
    [!ERROR!]
      Same Dma channel should not be configured for both Tx and Rx
      [!"node:path(.)"!]
    [!ENDERROR!]
  [!ENDIF!]

  [!// If RX DMA channel is same for other some other QSPIx generate error
  [!IF "contains($DMAChnl,./SpiHwDmaChannelReceptionRef)"!]
    [!ERROR!]
      Dma channel should not be shared across the QSPI Hw unit
      [!"node:path(./SpiHwDmaChannelReceptionRef)"!]
    [!ENDERROR!]

  [!// If TX DMA channel is same for other some other QSPIx generate error
  [!ELSEIF "contains($DMAChnl,./SpiHwDmaChannelTransmissionRef)"!]
    [!ERROR!]
      Dma channel should not be shared across the QSPI Hw unit
      [!"node:path(./SpiHwDmaChannelTransmissionRef)"!]
    [!ENDERROR!]
  [!ENDIF!]

  [!VAR "DMAChnl"="concat($DMAChnl,',',node:value(./SpiHwDmaChannelTransmissionRef))"!]
  [!VAR "DMAChnl"="concat($DMAChnl,',',node:value(./SpiHwDmaChannelReceptionRef))"!]

  [!ENDLOOP!][!// end of LOOP "SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*/SpiHwDmaConfigurationQspi/*"

  [!VAR "Spi_FlagPin" = "num:i(0)"!]
  [!LOOP "SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*"!]
    [!IF "node:value(./SpiHwConfigKernel) = 'QSPI2'"!]
        [!VAR "Spi_FlagPin" = "$Spi_FlagPin + num:i(1)"!]
    [!ENDIF!]
    [!IF "node:value(./SpiHwConfigKernel) = 'QSPI4'"!]
        [!VAR "Spi_FlagPin" = "$Spi_FlagPin + num:i(1)"!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!IF "$Spi_FlagPin = num:i(2)"!]
    [!IF "(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI2']/SpiHWPinMRSTQspix = 'MRST2CN_PORT21_PIN2') and
                (SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI4']/SpiHWPinMRSTQspix = 'MRST4CN_PORT21_PIN2') "!]
                [!ERROR!]
                    Same pins are configured for two QSPI please select another pin "SpiHWPinMRSTQspix"
                [!ENDERROR!]
    [!ENDIF!]
    [!IF "(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI2']/SpiHWPinMRSTQspix = 'MRST2CP_PORT21_PIN3') and
                (SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI4']/SpiHWPinMRSTQspix = 'MRST4CP_PORT21_PIN3') "!]
                [!ERROR!]
                    Same pin are configured for QSPI 2 and 4 please select another pin "SpiHWPinMRSTQspix"
                [!ENDERROR!]
    [!ENDIF!]
  [!ENDIF!]

  [!FOR "Spi_KernelID"="0" TO "5"!]
    [!LOOP "SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel= concat('QSPI',$Spi_KernelID)]"!]
        [!IF "count(../../../../SpiDriver/SpiExternalDevice/*[SpiHwUnit = concat('QSPI',$Spi_KernelID)]) = num:i(0)"!]
                [!ERROR!]
                    QSPI[!"num:i($Spi_KernelID)"!] is configured but not been assigned to any external device
                [!ENDERROR!]
        [!ENDIF!]
    [!ENDLOOP!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={60238BED-58F7-43b5-8F91-812120982C1A}][/cover]
MACRO: Spi_CGVerifySequenceConfig
Macro to verify sequence configuration errors
******************************************************************************/!]
[!MACRO "Spi_CGVerifySequenceConfig"!][!//
[!NOCODE!][!//

[!// If a job is assigned to the sequence and the job does not exists generate error
[!LOOP "SpiDriver/SpiSequence/*/SpiJobAssignment/*"!]
  [!IF "not(node:exists(node:value(.)))"!]
    [!ERROR!]
      Job assigned to the Sequence '[!"node:name(../..)"!]' does not exists.
      ([!"node:path(.)"!])
    [!ENDERROR!]
  [!ENDIF!]
[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiSequence/*/SpiJobAssignment/*"

[!// For all sequnce
[!LOOP "SpiDriver/SpiSequence/*"!]

  [!// Level delivered is 1
  [!IF "../../../SpiGeneral/SpiLevelDelivered = num:i(2)"!]
    [!VAR "Spi_MacSync" = "0"!]
    [!VAR "Spi_MacAsync" = "0"!]

    [!// If a sequence is assigned two types of jobs generate error
    [!LOOP "./SpiJobAssignment/*"!]
      [!IF "node:ref(.)/SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!VAR "Spi_MacAsync" = "$Spi_MacAsync + 1"!]
      [!ELSEIF "node:ref(.)/SpiHwUnitSynchronous/*[1] = 'SYNCHRONOUS'"!]
        [!VAR "Spi_MacSync" = "$Spi_MacSync + 1"!]
      [!ENDIF!]
    [!ENDLOOP!][!// end of LOOP "./SpiJobAssignment/*"

    [!//[cover parentID={CE3CCE56-8C66-483b-B81B-859A53AE8734}][/cover][!//
    [!IF "($Spi_MacSync > num:i(0)) and ($Spi_MacAsync > num:i(0))"!]
      [!ERROR!]
         In Sequence '[!"node:name(.)"!]', both the Synchronous and Asynchronous jobs are configured,
         Num_Sync_Jobs (=[!"num:i($Spi_MacSync)"!]) and Num_Async_Jobs (=[!"num:i($Spi_MacAsync)"!])
      [!ENDERROR!]
    [!ENDIF!][!// enf of IF "($Spi_MacSync > num:i(0)) and ($Spi_MacAsync > num:i(0))"

  [!ENDIF!][!// end of IF "../../../SpiGeneral/SpiLevelDelivered = num:i(2)"

  [!// If job in a sequence belongs to different QSPIx hardware unit generate error
  [!VAR "Spi_MacHwString" = "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit"!]
  [!LOOP "./SpiJobAssignment/*"!]

    [!IF "not(node:exists(node:value(.)))"!]
      [!ERROR!]
        Job assigned to the Sequence '[!"node:name(../..)"!]' does not exists.
        ([!"node:path(.)"!])
      [!ENDERROR!]
    [!ELSE!]
      [!//[cover parentID={7CFEF673-5AB5-4fa0-ABAD-1538FC54B78A}]Check if the job belongs to the same QSPIx hardware unit to which other jobs assigned to same seuence belongs to [/cover][!//
      [!IF "not(text:contains($Spi_MacHwString,node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit)
       and  text:contains(node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit,$Spi_MacHwString))"!]
         [!ERROR!]
            All the jobs assigned to a sequence '[!"node:name(../..)"!]' should be on the same QSPI Hw.
            Job '[!"node:value(../*[1])"!]' is on '[!"$Spi_MacHwString"!]',
            whereas, Job '[!"node:value(.)"!]' is on '[!"node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit"!]'
         [!ENDERROR!]
      [!ENDIF!]

    [!ENDIF!][!// end of IF "not(node:exists(node:value(.)))"
  [!ENDLOOP!][!// end of LOOP "./SpiJobAssignment/*"
[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiSequence/*"

[!LOOP "SpiDriver/SpiJob/*"!]
    [!VAR "Spi_JobExistsFlag" = "num:i(0)"!]
    [!VAR "Spi_CurrentJobName" = "node:name(.)"!]
    [!LOOP "../../SpiSequence/*"!]
        [!LOOP "SpiJobAssignment/*"!]
            [!IF "node:name(node:ref(node:current())) = $Spi_CurrentJobName"!]
               [!VAR "Spi_JobExistsFlag" = "num:i(1)"!]
               [!BREAK!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!ENDLOOP!]
    [!IF "$Spi_JobExistsFlag = num:i(0)"!]
        [!ERROR!]
            All jobs should be assigned to atleast one sequence [!"$Spi_CurrentJobName"!] is not assigned to any sequence
        [!ENDERROR!]
    [!ENDIF!]
[!ENDLOOP!]

[!//[cover parentID={EACFD16F-5FB3-4ac0-98D4-C9923B3CBEF2}][/cover]
[!//Verify jobs assigned to a sequence is in order of decreasing order of priority
[!IF "(node:value(SpiGeneral/SpiLevelDelivered) = num:i(1)) or (node:value(SpiGeneral/SpiLevelDelivered) = num:i(2))"!]
    [!LOOP "SpiDriver/SpiSequence/*"!]
    [!VAR "Spi_priorityCmp" = "num:i(4)"!]
        [!LOOP "./SpiJobAssignment/*"!]
            [!VAR "Spi_priority" = "num:i(node:value(node:ref(node:value(.))/SpiJobPriority))"!]
            [!IF "$Spi_priorityCmp < $Spi_priority"!]
                [!ERROR!]
                    All jobs in a sequence should be assigned in order of decreasing priority
                [!ENDERROR!]
            [!ELSE!]
                [!VAR "Spi_priorityCmp" = "$Spi_priority"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!ENDLOOP!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={71CC259D-FC61-48bf-905F-9EC7FA89286A}][/cover]
MACRO: Spi_CGVerifyChannelSharingConfig
Macro to verify channel sharing configuration errors
******************************************************************************/!]
[!MACRO "Spi_CGVerifyChannelSharingConfig"!][!//
[!NOCODE!][!//

[!// check for channels not being shared across cores
[!LOOP "SpiDriver/SpiChannel/*"!]
  [!VAR "Spi_MacIBChannel" = "node:name(.)"!]
  [!VAR "Spi_MacIBChannelHw" = "''"!]
  [!VAR "Spi_MacIBChannelCore" = "''"!]
  [!VAR "Spi_MacFlag" = "num:i(0)"!]

  [!// For all jobs
  [!LOOP "../../SpiJob/*"!]
    [!LOOP "./SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $Spi_MacIBChannel]"!]
      [!IF "$Spi_MacFlag = num:i(0)"!]
        [!VAR "Spi_MacFlag" = "num:i(1)"!]
        [!VAR "Spi_MacIBChannelHw" = "node:value(node:ref(../../SpiDeviceAssignment)/SpiHwUnit)"!]
        [!VAR "Spi_MacIBChannelJob" = "node:name(../..)"!]
        [!VAR "Spi_ChannelkernelIDVer" = "substring-after($Spi_MacIBChannelHw, 'I')"!]
        [!VAR "Spi_MacIBChannelCore" = "text:split($QSPICore_config,',')[position() = $Spi_ChannelkernelIDVer + 1]"!]
      [!ENDIF!]
      [!VAR "Spi_MacIBChannelHw" = "node:value(node:ref(../../SpiDeviceAssignment)/SpiHwUnit)"!]
      [!VAR "Spi_ChannelkernelIDVer" = "substring-after($Spi_MacIBChannelHw, 'I')"!]
      [!VAR "Spi_MacIBChannelCore1" = "text:split($QSPICore_config,',')[position() = $Spi_ChannelkernelIDVer + 1]"!]
      [!IF "not(text:contains($Spi_MacIBChannelCore,$Spi_MacIBChannelCore1)
               and  text:contains(node:ref(../../SpiDeviceAssignment)/SpiHwUnit,$Spi_MacIBChannelHw))"!]
        [!ERROR!]
          Channels should not be shared between different cores.
          Channel [!"$Spi_MacIBChannel"!] present on [!"$Spi_MacIBChannelJob"!] core ID - ([!"$Spi_MacIBChannelCore"!]) and also present on [!"node:name(../..)"!] core ID - ([!"$Spi_MacIBChannelCore1"!]) which are on different core.
        [!ENDERROR!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDLOOP!][!// end of LOOP "../../SpiJob/*"

[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={68E033B5-8F3E-4d85-8ABF-57BD1350550A}][/cover]
MACRO: Spi_CGCalculateIBSizeAsyncQSPIz
Macro to Calculate the IB buffer size of a given QSPIz
******************************************************************************/!]
[!MACRO "Spi_CGCalculateIBSizeAsyncQSPIz", "Spi_OutQspiIndex" = ""!][!//
[!NOCODE!][!//

[!VAR "Spi_MacIB8Bit" = "num:i(0)"!]
[!VAR "Spi_MacIB16Bit" = "num:i(0)"!]
[!VAR "Spi_MacIB32Bit" = "num:i(0)"!]

[!// For all IB channels
[!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
  [!VAR "Spi_MacChannelName" = "node:name(.)"!]
  [!VAR "Spi_MacFlag" = "num:i(0)"!]

[!IF "../../../SpiGeneral/SpiLevelDelivered = num:i(1)"!]
[!// IB channels belonging to asynchornous job
  [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_MacChannelName]"!]

    [!// If job blongs to input QSPIx hardware unit
    [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQspiIndex) and (not(text:contains(text:split($Spi_MasterChnllstNum,','), $Spi_MacChannelName)))"!]
      [!// set flag for IB channel size should be accounted for current QSPIx hardware unit
      [!VAR "Spi_MacFlag" = "num:i(1)"!][!//
      [!VAR "Spi_MasterChnllstNum" = "concat($Spi_MasterChnllstNum,$Spi_MacChannelName,',')"!]
      [!BREAK!]
    [!ENDIF!]

  [!ENDLOOP!][!// end of LOOP "../../SpiJob/SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_MacChannelName]"
[!ENDIF!]
[!IF "../../../SpiGeneral/SpiLevelDelivered = num:i(2)"!]
  [!// IB channels belonging to asynchornous job
  [!LOOP "../../SpiJob/*[SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS']/SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_MacChannelName]"!]

    [!// If job blongs to input QSPIx hardware unit
    [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQspiIndex) and (not(text:contains(text:split($Spi_MasterChnllstNum,','), $Spi_MacChannelName)))"!]
      [!// set flag for IB channel size should be accounted for current QSPIx hardware unit
      [!VAR "Spi_MacFlag" = "num:i(1)"!][!//
      [!VAR "Spi_MasterChnllstNum" = "concat($Spi_MasterChnllstNum,$Spi_MacChannelName,',')"!]
      [!BREAK!]
    [!ENDIF!]

  [!ENDLOOP!][!// end of LOOP "../../SpiJob/*[SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS']/SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_MacChannelName]"
[!ENDIF!]

  [!// if flag is set
  [!IF "$Spi_MacFlag = num:i(1)"!]

    [!// if data length is greater than the max length generate error
    [!IF "./SpiIbNBuffers > num:i(65535)"!]
        [!ERROR!]
            IB channels defined for async transmission should have length equal or less than 65535.
        [!ENDERROR!]
    [!ENDIF!]

    [!// data width is 8
    [!IF "./SpiDataWidth < num:i(9)"!]
      [!// number of 8 bits buffer configured
      [!VAR "Spi_MacIB8Bit" = "$Spi_MacIB8Bit + num:i(./SpiIbNBuffers)"!]
      [!// 8-bit alignment for even boundary address
      [!IF "num:i(./SpiIbNBuffers) mod num:i(4) != num:i(0)"!]
        [!VAR "Spi_MacIB8Bit" = "$Spi_MacIB8Bit + (num:i(4) - num:i(./SpiIbNBuffers) mod num:i(4))"!]
      [!ENDIF!]
    [!// data width is 16
    [!ELSEIF "./SpiDataWidth < num:i(17)"!]
      [!// number of 16 bits buffer configured
      [!VAR "Spi_MacIB16Bit" = "$Spi_MacIB16Bit + num:i(./SpiIbNBuffers)"!]
      [!// 16-bit alignment for even boundary address
      [!IF "num:i(./SpiIbNBuffers) mod num:i(2) != num:i(0)"!]
        [!VAR "Spi_MacIB16Bit" = "$Spi_MacIB16Bit + ( num:i(./SpiIbNBuffers) mod num:i(2))"!]
      [!ENDIF!]
    [!// data width is 32
    [!ELSE!]
    [!// number of 32 bits buffer configured
    [!VAR "Spi_MacIB32Bit" = "$Spi_MacIB32Bit + num:i(./SpiIbNBuffers)"!]
    [!ENDIF!][!// end of IF "./SpiDataWidth < num:i(9)"

  [!ENDIF!][!// end of IF "$Spi_MacFlag = num:i(1)"

[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"

[!// 16 bit is 2 bytes
[!VAR "Spi_MacIB16Bit" = "$Spi_MacIB16Bit * num:i(2)"!]
[!// 32 bit is 4 bytes
[!VAR "Spi_MacIB32Bit" = "$Spi_MacIB32Bit * num:i(4)"!]

[!VAR "Spi_MacMaxIBSize"="num:i(0)"!]
[!VAR "Spi_MacMaxIBSize"="$Spi_MacIB8Bit"!]

[!/* ALign for 16-bit */!]
[!IF "$Spi_MacIB16Bit != num:i(0)"!]

  [!IF "($Spi_MacMaxIBSize mod num:i(2)) != num:i(0)"!]
    [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + ($Spi_MacMaxIBSize mod num:i(2))"!]
  [!ENDIF!]
  [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + $Spi_MacIB16Bit"!]

 [!ENDIF!][!// end of IF "$Spi_MacIB16Bit != num:i(0)"

[!/* Align for 32-bit */!]
[!IF "$Spi_MacIB32Bit != num:i(0)"!]

  [!IF "($Spi_MacMaxIBSize mod num:i(4)) != num:i(0)"!]
    [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + (num:i(4) - ($Spi_MacMaxIBSize mod num:i(4)))"!]
  [!ENDIF!]
  [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + $Spi_MacIB32Bit"!]

 [!ENDIF!][!// end of IF "$Spi_MacIB32Bit != num:i(0)"

[!/* Align for Receive buffer */!]
[!IF "($Spi_MacMaxIBSize mod num:i(4)) != num:i(0)"!]
[!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + (num:i(4) - ($Spi_MacMaxIBSize mod num:i(4)))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGCalculateIBSize
Macro to Calculate the IB buffer size of all synchronous QSPIz
******************************************************************************/!]
[!MACRO "Spi_CGCalculateIBSize", "Spi_OutQspiIndex" = ""!][!//
[!NOCODE!][!//

[!VAR "Spi_MacIB8Bit" = "num:i(0)"!]
[!VAR "Spi_MacIB16Bit" = "num:i(0)"!]
[!VAR "Spi_MacIB32Bit" = "num:i(0)"!]

[!// For all IB channels
[!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
  [!VAR "Spi_MacChannelName" = "node:name(.)"!]
  [!VAR "Spi_MacFlag" = "num:i(0)"!]

[!IF "../../../SpiGeneral/SpiLevelDelivered = num:i(2)"!]
    [!// IB channels belonging to synchornous job
    [!LOOP "../../SpiJob/*[SpiHwUnitSynchronous/*[1] = 'SYNCHRONOUS']/SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_MacChannelName]"!]
        [!// - checking if the channel belongs to same QSPI instance for which IB size is being calculated only then Spi_MacFlag is set
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQspiIndex) and (not(text:contains(text:split($Spi_MasterChnllstNum,','), $Spi_MacChannelName)))"!]
            [!// set flag for IB channel size should be accounted for current QSPIx hardware unit
            [!VAR "Spi_MacFlag" = "num:i(1)"!][!//
            [!VAR "Spi_MasterChnllstNum" = "concat($Spi_MasterChnllstNum,$Spi_MacChannelName,',')"!]
            [!BREAK!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]
[!IF "../../../SpiGeneral/SpiLevelDelivered = num:i(0)"!]
    [!// IB channels belonging to synchornous job
    [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_MacChannelName]"!]
        [!// - checking if the channel belongs to same QSPI instance for which IB size is being calculated only then Spi_MacFlag is set
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQspiIndex) and (not(text:contains(text:split($Spi_MasterChnllstNum,','), $Spi_MacChannelName)))"!]
            [!// set flag for IB channel size should be accounted for current QSPIx hardware unit
            [!VAR "Spi_MacFlag" = "num:i(1)"!][!//
            [!VAR "Spi_MasterChnllstNum" = "concat($Spi_MasterChnllstNum,$Spi_MacChannelName,',')"!]
            [!BREAK!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]

  [!IF "$Spi_MacFlag = num:i(1)"!]

    [!//
    [!IF "./SpiDataWidth < num:i(9)"!]
      [!VAR "Spi_MacIB8Bit" = "$Spi_MacIB8Bit + num:i(./SpiIbNBuffers)"!]
      [!// 8-bit alignment for even boundary address
      [!IF "num:i(./SpiIbNBuffers) mod num:i(4) != num:i(0)"!]
        [!VAR "Spi_MacIB8Bit" = "$Spi_MacIB8Bit + ( num:i(./SpiIbNBuffers) mod num:i(4))"!]
      [!ENDIF!]
    [!ELSEIF "./SpiDataWidth < num:i(17)"!]
      [!VAR "Spi_MacIB16Bit" = "$Spi_MacIB16Bit + num:i(./SpiIbNBuffers)"!]
      [!// 16-bit alignment for even boundary address
      [!IF "num:i(./SpiIbNBuffers) mod num:i(2) != num:i(0)"!]
        [!VAR "Spi_MacIB16Bit" = "$Spi_MacIB16Bit + ( num:i(./SpiIbNBuffers) mod num:i(2))"!]
      [!ENDIF!]
    [!ELSE!]
      [!VAR "Spi_MacIB32Bit" = "$Spi_MacIB32Bit + num:i(./SpiIbNBuffers)"!]
    [!ENDIF!]

  [!ENDIF!][!// end of IF "$Spi_MacFlag = num:i(1)"

[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"

[!VAR "Spi_MacIB16Bit" = "$Spi_MacIB16Bit * num:i(2)"!]
[!VAR "Spi_MacIB32Bit" = "$Spi_MacIB32Bit * num:i(4)"!]

[!VAR "Spi_MacMaxIBSize"="num:i(0)"!]
[!VAR "Spi_MacMaxIBSize"="$Spi_MacIB8Bit"!]

[!/* ALign for 16-bit */!]
[!IF "$Spi_MacIB16Bit != num:i(0)"!]
  [!IF "($Spi_MacMaxIBSize mod num:i(2)) != num:i(0)"!]
    [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + ($Spi_MacMaxIBSize mod num:i(2))"!]
  [!ENDIF!]
  [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + $Spi_MacIB16Bit"!]
[!ENDIF!]

[!/* Align for 32-bit */!]
[!IF "$Spi_MacIB32Bit != num:i(0)"!]
  [!IF "($Spi_MacMaxIBSize mod num:i(4)) != num:i(0)"!]
    [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + (num:i(4) - ($Spi_MacMaxIBSize mod num:i(4)))"!]
  [!ENDIF!]
  [!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + $Spi_MacIB32Bit"!]
[!ENDIF!]


[!/* Align for Receive buffer */!]
[!IF "($Spi_MacMaxIBSize mod num:i(4)) != num:i(0)"!]
[!VAR "Spi_MacMaxIBSize"="$Spi_MacMaxIBSize + (num:i(4) - ($Spi_MacMaxIBSize mod num:i(4)))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={0CCC6E78-533B-4b48-8F4C-B2576154EEAA}][/cover]
MACRO: Spi_CGIsQSPIzUsed
Macro to Check if particular QSPI is available
******************************************************************************/!]
[!MACRO "Spi_CGIsQSPIzUsed"!][!//
[!NOCODE!][!//

[!VAR "Spi_MacQspi0Used"="num:i(0)"!]
[!VAR "Spi_MacQspi1Used"="num:i(0)"!]
[!VAR "Spi_MacQspi2Used"="num:i(0)"!]
[!VAR "Spi_MacQspi3Used"="num:i(0)"!]
[!VAR "Spi_MacQspi4Used"="num:i(0)"!]
[!VAR "Spi_MacQspi5Used"="num:i(0)"!]

[!VAR "Spi_MacQspi0HwType"="num:i(2)"!]
[!VAR "Spi_MacQspi1HwType"="num:i(2)"!]
[!VAR "Spi_MacQspi2HwType"="num:i(2)"!]
[!VAR "Spi_MacQspi3HwType"="num:i(2)"!]
[!VAR "Spi_MacQspi4HwType"="num:i(2)"!]
[!VAR "Spi_MacQspi5HwType"="num:i(2)"!]

[!// for level delivered 0 set hardware type for QSPIx to be 0 i.e synchornous
[!IF "SpiGeneral/SpiLevelDelivered = num:i(0)"!]
  [!VAR "Spi_MacQspi0HwType"="num:i(0)"!]
  [!VAR "Spi_MacQspi1HwType"="num:i(0)"!]
  [!VAR "Spi_MacQspi2HwType"="num:i(0)"!]
  [!VAR "Spi_MacQspi3HwType"="num:i(0)"!]
  [!VAR "Spi_MacQspi4HwType"="num:i(0)"!]
  [!VAR "Spi_MacQspi5HwType"="num:i(0)"!]
[!// for level delivered 1 set hardware type for QSPIx to be 0 i.e asynchornous
[!ELSEIF "SpiGeneral/SpiLevelDelivered = num:i(1)"!]
  [!VAR "Spi_MacQspi0HwType"="num:i(1)"!]
  [!VAR "Spi_MacQspi1HwType"="num:i(1)"!]
  [!VAR "Spi_MacQspi2HwType"="num:i(1)"!]
  [!VAR "Spi_MacQspi3HwType"="num:i(1)"!]
  [!VAR "Spi_MacQspi4HwType"="num:i(1)"!]
  [!VAR "Spi_MacQspi5HwType"="num:i(1)"!]
[!ENDIF!]

[!// for all jobs
[!LOOP "SpiDriver/SpiJob/*"!]

  [!// If job belongs to QSPI0 hardware unit
  [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI0'"!]
    [!// set QSPI used to true i.e 1
    [!VAR "Spi_MacQspi0Used"="num:i(1)"!]
    [!// level deliverd is 2 then update haedware type as per job type
    [!IF "../../../SpiGeneral/SpiLevelDelivered = 2"!]
      [!// level delived is asynchonous
      [!IF "./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!// hardware type is 0 then it asynchonous job cant be assigned to it generate error
        [!IF "$Spi_MacQspi0HwType = num:i(0)"!]
          [!ERROR!]
            QSPI0 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Asynchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!// if hardware type is 2 then update as per job type
        [!ELSE!]
          [!VAR "Spi_MacQspi0HwType"="num:i(1)"!]
        [!ENDIF!]
      [!ELSE!]
        [!// hardware type is 0 then it asynchonous job cant be assigned to it generate error
        [!IF "$Spi_MacQspi0HwType = num:i(1)"!]
          [!ERROR!]
            QSPI0 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Synchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!// if hardware type is 2 then update as per job type
        [!ELSE!]
          [!VAR "Spi_MacQspi0HwType"="num:i(0)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!][!// end of IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI0'"

  [!// similarly check for job belonging to QSPI1 hardware unit
  [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI1'"!]
    [!VAR "Spi_MacQspi1Used"="num:i(1)"!]
    [!IF "../../../SpiGeneral/SpiLevelDelivered = 2"!]
      [!IF "./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!IF "$Spi_MacQspi1HwType = num:i(0)"!]
          [!ERROR!]
            QSPI1 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Asynchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi1HwType"="num:i(1)"!]
        [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi1HwType = num:i(1)"!]
          [!ERROR!]
            QSPI1 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Synchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi1HwType"="num:i(0)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]

  [!// similarly check for job belonging to QSPI2 hardware unit
  [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI2'"!]
    [!VAR "Spi_MacQspi2Used"="num:i(1)"!]
    [!IF "../../../SpiGeneral/SpiLevelDelivered = 2"!]
      [!IF "./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!IF "$Spi_MacQspi2HwType = num:i(0)"!]
          [!ERROR!]
            QSPI2 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Asynchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi2HwType"="num:i(1)"!]
        [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi2HwType = num:i(1)"!]
          [!ERROR!]
            QSPI2 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Synchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi2HwType"="num:i(0)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]

  [!// similarly check for job belonging to QSPI3 hardware unit
  [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI3'"!]
    [!VAR "Spi_MacQspi3Used"="num:i(1)"!]
    [!IF "../../../SpiGeneral/SpiLevelDelivered = 2"!]
      [!IF "./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!IF "$Spi_MacQspi3HwType = num:i(0)"!]
          [!ERROR!]
            QSPI3 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Asynchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi3HwType"="num:i(1)"!]
        [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi3HwType = num:i(1)"!]
          [!ERROR!]
            QSPI3 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Synchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi3HwType"="num:i(0)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]

  [!// similarly check for job belonging to QSPI4 hardware unit
  [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI4'"!]
    [!VAR "Spi_MacQspi4Used"="num:i(1)"!]
    [!IF "../../../SpiGeneral/SpiLevelDelivered = 2"!]
      [!IF "./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!IF "$Spi_MacQspi4HwType = num:i(0)"!]
          [!ERROR!]
            QSPI4 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Asynchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi4HwType"="num:i(1)"!]
        [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi4HwType = num:i(1)"!]
          [!ERROR!]
            QSPI4 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Synchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi4HwType"="num:i(0)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]

  [!// similarly check for job belonging to QSPI5 hardware unit
  [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI5'"!]
    [!VAR "Spi_MacQspi5Used"="num:i(1)"!]
    [!IF "../../../SpiGeneral/SpiLevelDelivered = 2"!]
      [!IF "./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'"!]
        [!IF "$Spi_MacQspi5HwType = num:i(0)"!]
          [!ERROR!]
            QSPI5 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Asynchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi5HwType"="num:i(1)"!]
        [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi5HwType = num:i(1)"!]
          [!ERROR!]
            QSPI5 is configured as both Synchronous and Asynchronous BUS.
            (Hint - one of the Job where it is defined as Synchronous bus is [!"node:name(.)"!])
          [!ENDERROR!]
        [!ELSE!]
          [!VAR "Spi_MacQspi5HwType"="num:i(0)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={15845FB1-B3D1-44fb-AAD5-0360944420D4}][/cover]
MACRO: Spi_CGDmaTcsCount
Macro to count the Max DMA TCS count for a QSPIx hardware unit
******************************************************************************/!]
[!MACRO "Spi_CGDmaTcsCount"!][!//
[!NOCODE!][!//
[!VAR "Spi_DmaMaxTcsNumQspi0"="num:i(0)"!]
[!VAR "Spi_DmaMaxTcsNumQspi1"="num:i(0)"!]
[!VAR "Spi_DmaMaxTcsNumQspi2"="num:i(0)"!]
[!VAR "Spi_DmaMaxTcsNumQspi3"="num:i(0)"!]
[!VAR "Spi_DmaMaxTcsNumQspi4"="num:i(0)"!]
[!VAR "Spi_DmaMaxTcsNumQspi5"="num:i(0)"!]

[!// for all jobs
[!LOOP "SpiDriver/SpiJob/*"!]

    [!// if job is assigned to QSPI0 hardware unit
    [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI0'"!]
      [!// if current max TCS count is smaller than the current count update
      [!IF "count(./SpiChannelList/*) > $Spi_DmaMaxTcsNumQspi0"!]
        [!VAR "Spi_DmaMaxTcsNumQspi0"="count(./SpiChannelList/*)"!]
      [!ENDIF!]
    [!ENDIF!]

    [!// Similar for job assigned to QSPI1 hardware unit
    [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI1'"!]
      [!IF "count(./SpiChannelList/*) > $Spi_DmaMaxTcsNumQspi1"!]
        [!VAR "Spi_DmaMaxTcsNumQspi1"="count(./SpiChannelList/*)"!]
      [!ENDIF!]
    [!ENDIF!]

    [!// Similar for job assigned to QSPI2 hardware unit
    [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI2'"!]
      [!IF "count(./SpiChannelList/*) > $Spi_DmaMaxTcsNumQspi2"!]
        [!VAR "Spi_DmaMaxTcsNumQspi2"="count(./SpiChannelList/*)"!]
      [!ENDIF!]
    [!ENDIF!]

    [!// Similar for job assigned to QSPI3 hardware unit
    [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI3'"!]
      [!IF "count(./SpiChannelList/*) > $Spi_DmaMaxTcsNumQspi3"!]
        [!VAR "Spi_DmaMaxTcsNumQspi3"="count(./SpiChannelList/*)"!]
      [!ENDIF!]
    [!ENDIF!]

    [!// Similar for job assigned to QSPI4 hardware unit
    [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI4'"!]
      [!IF "count(./SpiChannelList/*) > $Spi_DmaMaxTcsNumQspi4"!]
        [!VAR "Spi_DmaMaxTcsNumQspi4"="count(./SpiChannelList/*)"!]
      [!ENDIF!]
    [!ENDIF!]

    [!// Similar for job assigned to QSPI5 hardware unit
    [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI5'"!]
      [!IF "count(./SpiChannelList/*) > $Spi_DmaMaxTcsNumQspi5"!]
        [!VAR "Spi_DmaMaxTcsNumQspi5"="count(./SpiChannelList/*)"!]
      [!ENDIF!]
    [!ENDIF!]

[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiJob/*"

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={B4840521-8066-4ebb-AC0B-240E7AD59BBC}][/cover]
MACRO: Spi_CGStoreSequence_ID
Macro to store Symbolic names for Sequences in template variables
******************************************************************************/!]
[!MACRO "Spi_CGStoreSequence_ID"!][!//
[!NOCODE!][!//
  [!// Symbolic list for synchornous sequence for each hardware unit
  [!VAR "Spi_SeqSyncQSPI0"="''"!]
  [!VAR "Spi_SeqSyncQSPI1"="''"!]
  [!VAR "Spi_SeqSyncQSPI2"="''"!]
  [!VAR "Spi_SeqSyncQSPI3"="''"!]
  [!VAR "Spi_SeqSyncQSPI4"="''"!]
  [!VAR "Spi_SeqSyncQSPI5"="''"!]

  [!// Count of synchronous sequence in each unit
  [!VAR "Spi_SeqSyncQSPI0Count"="num:i(0)"!]
  [!VAR "Spi_SeqSyncQSPI1Count"="num:i(0)"!]
  [!VAR "Spi_SeqSyncQSPI2Count"="num:i(0)"!]
  [!VAR "Spi_SeqSyncQSPI3Count"="num:i(0)"!]
  [!VAR "Spi_SeqSyncQSPI4Count"="num:i(0)"!]
  [!VAR "Spi_SeqSyncQSPI5Count"="num:i(0)"!]

  [!// Symbolic list for asynchornous sequence for each hardware unit
  [!VAR "Spi_SeqAsyncQSPI0"="''"!]
  [!// Count of asynchonous sequence in each unit
  [!VAR "Spi_SeqAsyncQSPI0Count"="num:i(0)"!]
  [!VAR "Spi_SeqAsyncQSPI1"="''"!]
  [!VAR "Spi_SeqAsyncQSPI1Count"="num:i(0)"!]
  [!VAR "Spi_SeqAsyncQSPI2"="''"!]
  [!VAR "Spi_SeqAsyncQSPI2Count"="num:i(0)"!]
  [!VAR "Spi_SeqAsyncQSPI3"="''"!]
  [!VAR "Spi_SeqAsyncQSPI3Count"="num:i(0)"!]
  [!VAR "Spi_SeqAsyncQSPI4"="''"!]
  [!VAR "Spi_SeqAsyncQSPI4Count"="num:i(0)"!]
  [!VAR "Spi_SeqAsyncQSPI5"="''"!]
  [!VAR "Spi_SeqAsyncQSPI5Count"="num:i(0)"!]

 [!// for all sequence
[!LOOP "SpiDriver/SpiSequence/*"!]

  [!// if level delivered is 1 or 2 and asynchronous job assigned to the sequence
  [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
         and (node:ref(./SpiJobAssignment/*[1])/SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'))"!]
    [!// job belongs to QSPI0
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI0'"!]
      [!// add count for asynchonous sequence and add node name to the list
      [!VAR "Spi_SeqAsyncQSPI0Count"="$Spi_SeqAsyncQSPI0Count + num:i(1)"!]
      [!VAR "Spi_SeqAsyncQSPI0"="concat($Spi_SeqAsyncQSPI0,node:name(.),',')"!]
    [!ENDIF!]
    [!// Similar for job belongs to QSPI1
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI1'"!]
      [!VAR "Spi_SeqAsyncQSPI1Count"="$Spi_SeqAsyncQSPI1Count + num:i(1)"!]
      [!VAR "Spi_SeqAsyncQSPI1"="concat($Spi_SeqAsyncQSPI1,node:name(.),',')"!]
    [!ENDIF!]

    [!// Similar for job belongs to QSPI2
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI2'"!]
      [!VAR "Spi_SeqAsyncQSPI2Count"="$Spi_SeqAsyncQSPI2Count + num:i(1)"!]
      [!VAR "Spi_SeqAsyncQSPI2"="concat($Spi_SeqAsyncQSPI2,node:name(.),',')"!]
    [!ENDIF!]

    [!// Similar for job belongs to QSPI3
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI3'"!]
      [!VAR "Spi_SeqAsyncQSPI3Count"="$Spi_SeqAsyncQSPI3Count + num:i(1)"!]
      [!VAR "Spi_SeqAsyncQSPI3"="concat($Spi_SeqAsyncQSPI3,node:name(.),',')"!]
    [!ENDIF!]

    [!// Similar for job belongs to QSPI4
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI4'"!]
      [!VAR "Spi_SeqAsyncQSPI4Count"="$Spi_SeqAsyncQSPI4Count + num:i(1)"!]
      [!VAR "Spi_SeqAsyncQSPI4"="concat($Spi_SeqAsyncQSPI4,node:name(.),',')"!]
    [!ENDIF!]

    [!// Similar for job belongs to QSPI5
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI5'"!]
      [!VAR "Spi_SeqAsyncQSPI5Count"="$Spi_SeqAsyncQSPI5Count + num:i(1)"!]
      [!VAR "Spi_SeqAsyncQSPI5"="concat($Spi_SeqAsyncQSPI5,node:name(.),',')"!]
    [!ENDIF!]

  [!ENDIF!][!// end of level delivered 1 or 2 and asynchonous sequences

  [!// Similar for level deliverd is 0 or 2 for synchornous job assigned to the sequence
  [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(0)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
         and (node:ref(./SpiJobAssignment/*[1])/SpiHwUnitSynchronous/*[1] = 'SYNCHRONOUS'))"!]

    [!// if the sequence belong to the QSPI 0
    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI0'"!]
      [!VAR "Spi_SeqSyncQSPI0Count"="$Spi_SeqSyncQSPI0Count + num:i(1)"!]
      [!VAR "Spi_SeqSyncQSPI0"="concat($Spi_SeqSyncQSPI0,node:name(.),',')"!]
    [!ENDIF!]

    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI1'"!]
      [!VAR "Spi_SeqSyncQSPI1Count"="$Spi_SeqSyncQSPI1Count + num:i(1)"!]
      [!VAR "Spi_SeqSyncQSPI1"="concat($Spi_SeqSyncQSPI1,node:name(.),',')"!]
    [!ENDIF!]

    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI2'"!]
      [!VAR "Spi_SeqSyncQSPI2Count"="$Spi_SeqSyncQSPI2Count + num:i(1)"!]
      [!VAR "Spi_SeqSyncQSPI2"="concat($Spi_SeqSyncQSPI2,node:name(.),',')"!]
    [!ENDIF!]

    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI3'"!]
        [!VAR "Spi_SeqSyncQSPI3Count"="$Spi_SeqSyncQSPI3Count + num:i(1)"!]
        [!VAR "Spi_SeqSyncQSPI3"="concat($Spi_SeqSyncQSPI3,node:name(.),',')"!]
    [!ENDIF!]

    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI4'"!]
        [!VAR "Spi_SeqSyncQSPI4Count"="$Spi_SeqSyncQSPI4Count + num:i(1)"!]
        [!VAR "Spi_SeqSyncQSPI4"="concat($Spi_SeqSyncQSPI4,node:name(.),',')"!]
    [!ENDIF!]

    [!IF "(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment))/SpiHwUnit = 'QSPI5'"!]
        [!VAR "Spi_SeqSyncQSPI5Count"="$Spi_SeqSyncQSPI5Count + num:i(1)"!]
        [!VAR "Spi_SeqSyncQSPI5"="concat($Spi_SeqSyncQSPI5,node:name(.),',')"!]
    [!ENDIF!]

[!ENDIF!][!// end of level delivered 0 or 2 and asynchonous sequences

[!ENDLOOP!][!// end of LOOP "SpiDriver/SpiSequence/*"

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={12751F77-B67F-427a-A0C0-E72F5EE05A52}][/cover]
MACRO: Spi_CGStoreJob_ID
Macro to store Symbolic names for Jobs in template variables
******************************************************************************/!]
[!MACRO "Spi_CGStoreJob_ID"!][!//
[!NOCODE!][!//

  [!// Symbolic list for synchornous job for each hardware unit
  [!VAR "Spi_JobSyncQSPI0"="''"!]
  [!// Count of synchonous job in each unit
  [!VAR "Spi_JobSyncQSPI0Count"="num:i(0)"!]
  [!VAR "Spi_JobSyncQSPI1"="''"!]
  [!VAR "Spi_JobSyncQSPI1Count"="num:i(0)"!]
  [!VAR "Spi_JobSyncQSPI2"="''"!]
  [!VAR "Spi_JobSyncQSPI2Count"="num:i(0)"!]
  [!VAR "Spi_JobSyncQSPI3"="''"!]
  [!VAR "Spi_JobSyncQSPI3Count"="num:i(0)"!]
  [!VAR "Spi_JobSyncQSPI4"="''"!]
  [!VAR "Spi_JobSyncQSPI4Count"="num:i(0)"!]
  [!VAR "Spi_JobSyncQSPI5"="''"!]
  [!VAR "Spi_JobSyncQSPI5Count"="num:i(0)"!]

  [!// Symbolic list for synchornous job for each hardware unit
  [!VAR "Spi_JobAsyncQSPI0"="''"!]
  [!// Count of asynchonous job in each unit
  [!VAR "Spi_JobAsyncQSPI0Count"="num:i(0)"!]
  [!VAR "Spi_JobAsyncQSPI1"="''"!]
  [!VAR "Spi_JobAsyncQSPI1Count"="num:i(0)"!]
  [!VAR "Spi_JobAsyncQSPI2"="''"!]
  [!VAR "Spi_JobAsyncQSPI2Count"="num:i(0)"!]
  [!VAR "Spi_JobAsyncQSPI3"="''"!]
  [!VAR "Spi_JobAsyncQSPI3Count"="num:i(0)"!]
  [!VAR "Spi_JobAsyncQSPI4"="''"!]
  [!VAR "Spi_JobAsyncQSPI4Count"="num:i(0)"!]
  [!VAR "Spi_JobAsyncQSPI5"="''"!]
  [!VAR "Spi_JobAsyncQSPI5Count"="num:i(0)"!]

[!LOOP "SpiDriver/SpiJob/*"!]
  [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
         and (./SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'))"!]

    [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI0'"!]
      [!VAR "Spi_JobAsyncQSPI0Count"="$Spi_JobAsyncQSPI0Count + num:i(1)"!]
      [!VAR "Spi_JobAsyncQSPI0"="concat($Spi_JobAsyncQSPI0,node:name(.),',')"!]
    [!ENDIF!]
    [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI1'"!]
      [!VAR "Spi_JobAsyncQSPI1Count"="$Spi_JobAsyncQSPI1Count + num:i(1)"!]
      [!VAR "Spi_JobAsyncQSPI1"="concat($Spi_JobAsyncQSPI1,node:name(.),',')"!]
    [!ENDIF!]
    [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI2'"!]
      [!VAR "Spi_JobAsyncQSPI2Count"="$Spi_JobAsyncQSPI2Count + num:i(1)"!]
      [!VAR "Spi_JobAsyncQSPI2"="concat($Spi_JobAsyncQSPI2,node:name(.),',')"!]
    [!ENDIF!]
    [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI3'"!]
      [!VAR "Spi_JobAsyncQSPI3Count"="$Spi_JobAsyncQSPI3Count + num:i(1)"!]
      [!VAR "Spi_JobAsyncQSPI3"="concat($Spi_JobAsyncQSPI3,node:name(.),',')"!]
    [!ENDIF!]
    [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI4'"!]
      [!VAR "Spi_JobAsyncQSPI4Count"="$Spi_JobAsyncQSPI4Count + num:i(1)"!]
      [!VAR "Spi_JobAsyncQSPI4"="concat($Spi_JobAsyncQSPI4,node:name(.),',')"!]
    [!ENDIF!]
    [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI5'"!]
      [!VAR "Spi_JobAsyncQSPI5Count"="$Spi_JobAsyncQSPI5Count + num:i(1)"!]
      [!VAR "Spi_JobAsyncQSPI5"="concat($Spi_JobAsyncQSPI5,node:name(.),',')"!]
    [!ENDIF!]
  [!ENDIF!]

  [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(0)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
         and (./SpiHwUnitSynchronous/*[1] = 'SYNCHRONOUS'))"!]

        [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI0'"!]
            [!VAR "Spi_JobSyncQSPI0Count"="$Spi_JobSyncQSPI0Count + num:i(1)"!]
            [!VAR "Spi_JobSyncQSPI0"="concat($Spi_JobSyncQSPI0,node:name(.),',')"!]
        [!ENDIF!]
        [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI1'"!]
            [!VAR "Spi_JobSyncQSPI1Count"="$Spi_JobSyncQSPI1Count + num:i(1)"!]
            [!VAR "Spi_JobSyncQSPI1"="concat($Spi_JobSyncQSPI1,node:name(.),',')"!]
        [!ENDIF!]
                [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI2'"!]
            [!VAR "Spi_JobSyncQSPI2Count"="$Spi_JobSyncQSPI2Count + num:i(1)"!]
            [!VAR "Spi_JobSyncQSPI2"="concat($Spi_JobSyncQSPI2,node:name(.),',')"!]
        [!ENDIF!]
                [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI3'"!]
            [!VAR "Spi_JobSyncQSPI3Count"="$Spi_JobSyncQSPI3Count + num:i(1)"!]
            [!VAR "Spi_JobSyncQSPI3"="concat($Spi_JobSyncQSPI3,node:name(.),',')"!]
        [!ENDIF!]
                [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI4'"!]
            [!VAR "Spi_JobSyncQSPI4Count"="$Spi_JobSyncQSPI4Count + num:i(1)"!]
            [!VAR "Spi_JobSyncQSPI4"="concat($Spi_JobSyncQSPI4,node:name(.),',')"!]
        [!ENDIF!]
        [!IF "(node:ref(./SpiDeviceAssignment))/SpiHwUnit = 'QSPI5'"!]
            [!VAR "Spi_JobSyncQSPI5Count"="$Spi_JobSyncQSPI5Count + num:i(1)"!]
            [!VAR "Spi_JobSyncQSPI5"="concat($Spi_JobSyncQSPI5,node:name(.),',')"!]
        [!ENDIF!]
  [!ENDIF!]

[!ENDLOOP!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={C61C6035-D797-48e8-BA95-75460C3067EC}][/cover]
MACRO: Spi_CGStoreChannel_ID
Macro to store Symbolic names for Channels in template variables
******************************************************************************/!]
[!MACRO "Spi_CGStoreChannel_ID"!][!//
[!NOCODE!][!//

  [!VAR "Spi_ChnlSyncQSPIx"="''"!]
  [!VAR "Spi_ChnlSyncQSPIxCount"="num:i(0)"!]

  [!VAR "Spi_MasterChnlList" = "''"!]
  [!VAR "Spi_ChnlSyncQSPI0"="''"!]
  [!VAR "Spi_ChnlSyncQSPI0Count"="num:i(0)"!]
  [!VAR "Spi_ChnlSyncQSPI1"="''"!]
  [!VAR "Spi_ChnlSyncQSPI1Count"="num:i(0)"!]
  [!VAR "Spi_ChnlSyncQSPI2"="''"!]
  [!VAR "Spi_ChnlSyncQSPI2Count"="num:i(0)"!]
  [!VAR "Spi_ChnlSyncQSPI3"="''"!]
  [!VAR "Spi_ChnlSyncQSPI3Count"="num:i(0)"!]
  [!VAR "Spi_ChnlSyncQSPI4"="''"!]
  [!VAR "Spi_ChnlSyncQSPI4Count"="num:i(0)"!]
  [!VAR "Spi_ChnlSyncQSPI5"="''"!]
  [!VAR "Spi_ChnlSyncQSPI5Count"="num:i(0)"!]

  [!VAR "Spi_ChnlAsyncQSPI0"="''"!]
  [!VAR "Spi_ChnlAsyncQSPI0Count"="num:i(0)"!]
  [!VAR "Spi_ChnlAsyncQSPI1"="''"!]
  [!VAR "Spi_ChnlAsyncQSPI1Count"="num:i(0)"!]
  [!VAR "Spi_ChnlAsyncQSPI2"="''"!]
  [!VAR "Spi_ChnlAsyncQSPI2Count"="num:i(0)"!]
  [!VAR "Spi_ChnlAsyncQSPI3"="''"!]
  [!VAR "Spi_ChnlAsyncQSPI3Count"="num:i(0)"!]
  [!VAR "Spi_ChnlAsyncQSPI4"="''"!]
  [!VAR "Spi_ChnlAsyncQSPI4Count"="num:i(0)"!]
  [!VAR "Spi_ChnlAsyncQSPI5"="''"!]
  [!VAR "Spi_ChnlAsyncQSPI5Count"="num:i(0)"!]

  [!VAR "Spi_EBChnl"="''"!]
  [!VAR "Spi_EBChnlCount"="num:i(0)"!]

  [!VAR "Spi_EBChnl0Async"="''"!]
  [!VAR "Spi_EBChnlCount0Async"="num:i(0)"!]
    [!VAR "Spi_EBChnl1Async"="''"!]
  [!VAR "Spi_EBChnlCount1Async"="num:i(0)"!]
    [!VAR "Spi_EBChnl2Async"="''"!]
  [!VAR "Spi_EBChnlCount2Async"="num:i(0)"!]
    [!VAR "Spi_EBChnl3Async"="''"!]
  [!VAR "Spi_EBChnlCount3Async"="num:i(0)"!]
    [!VAR "Spi_EBChnl4Async"="''"!]
  [!VAR "Spi_EBChnlCount4Async"="num:i(0)"!]
    [!VAR "Spi_EBChnl5Async"="''"!]
  [!VAR "Spi_EBChnlCount5Async"="num:i(0)"!]

    [!VAR "Spi_EBChnl0Sync"="''"!]
  [!VAR "Spi_EBChnlCount0Sync"="num:i(0)"!]
    [!VAR "Spi_EBChnl1Sync"="''"!]
  [!VAR "Spi_EBChnlCount1Sync"="num:i(0)"!]
    [!VAR "Spi_EBChnl2Sync"="''"!]
  [!VAR "Spi_EBChnlCount2Sync"="num:i(0)"!]
    [!VAR "Spi_EBChnl3Sync"="''"!]
  [!VAR "Spi_EBChnlCount3Sync"="num:i(0)"!]
    [!VAR "Spi_EBChnl4Sync"="''"!]
  [!VAR "Spi_EBChnlCount4Sync"="num:i(0)"!]
    [!VAR "Spi_EBChnl5Sync"="''"!]
  [!VAR "Spi_EBChnlCount5Sync"="num:i(0)"!]

[!IF "(SpiGeneral/SpiChannelBuffersAllowed = num:i(0)) or (SpiGeneral/SpiChannelBuffersAllowed = num:i(2))"!]
  [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
    [!VAR "Spi_IBChnlName"="node:name(.)"!]
    [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
           and (../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'))"!]
      [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI0')
            and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
        [!VAR "Spi_ChnlAsyncQSPI0Count"="$Spi_ChnlAsyncQSPI0Count + num:i(1)"!]
        [!VAR "Spi_ChnlAsyncQSPI0"="concat($Spi_ChnlAsyncQSPI0,node:name(.),',')"!]
        [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
      [!ENDIF!]
      [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI1')
            and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
        [!VAR "Spi_ChnlAsyncQSPI1Count"="$Spi_ChnlAsyncQSPI1Count + num:i(1)"!]
        [!VAR "Spi_ChnlAsyncQSPI1"="concat($Spi_ChnlAsyncQSPI1,node:name(.),',')"!]
        [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
      [!ENDIF!]
      [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI2')
            and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
        [!VAR "Spi_ChnlAsyncQSPI2Count"="$Spi_ChnlAsyncQSPI2Count + num:i(1)"!]
        [!VAR "Spi_ChnlAsyncQSPI2"="concat($Spi_ChnlAsyncQSPI2,node:name(.),',')"!]
        [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
      [!ENDIF!]
      [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI3')
            and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
        [!VAR "Spi_ChnlAsyncQSPI3Count"="$Spi_ChnlAsyncQSPI3Count + num:i(1)"!]
        [!VAR "Spi_ChnlAsyncQSPI3"="concat($Spi_ChnlAsyncQSPI3,node:name(.),',')"!]
        [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
      [!ENDIF!]
      [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI4')
             and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
        [!VAR "Spi_ChnlAsyncQSPI4Count"="$Spi_ChnlAsyncQSPI4Count + num:i(1)"!]
        [!VAR "Spi_ChnlAsyncQSPI4"="concat($Spi_ChnlAsyncQSPI4,node:name(.),',')"!]
        [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
      [!ENDIF!]
      [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI5')
             and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
        [!VAR "Spi_ChnlAsyncQSPI5Count"="$Spi_ChnlAsyncQSPI5Count + num:i(1)"!]
        [!VAR "Spi_ChnlAsyncQSPI5"="concat($Spi_ChnlAsyncQSPI5,node:name(.),',')"!]
        [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
      [!ENDIF!]
    [!ENDIF!]

    [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(0)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
           and (../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiHwUnitSynchronous/*[1] = 'SYNCHRONOUS'))"!]
         [!VAR "Spi_ChnlSyncQSPIxCount"="$Spi_ChnlSyncQSPIxCount + num:i(1)"!]
        [!VAR "Spi_ChnlSyncQSPIx"="concat($Spi_ChnlSyncQSPIx,node:name(.),',')"!]
        [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI0')
               and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
            [!VAR "Spi_ChnlSyncQSPI0Count"="$Spi_ChnlSyncQSPI0Count + num:i(1)"!]
            [!VAR "Spi_ChnlSyncQSPI0"="concat($Spi_ChnlSyncQSPI0,node:name(.),',')"!]
            [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
        [!ENDIF!]

        [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI1')
              and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
            [!VAR "Spi_ChnlSyncQSPI1Count"="$Spi_ChnlSyncQSPI1Count + num:i(1)"!]
            [!VAR "Spi_ChnlSyncQSPI1"="concat($Spi_ChnlSyncQSPI1,node:name(.),',')"!]
            [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
        [!ENDIF!]

        [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI2')
               and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
            [!VAR "Spi_ChnlSyncQSPI2Count"="$Spi_ChnlSyncQSPI2Count + num:i(1)"!]
            [!VAR "Spi_ChnlSyncQSPI2"="concat($Spi_ChnlSyncQSPI2,node:name(.),',')"!]
            [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
        [!ENDIF!]

        [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI3')
               and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
            [!VAR "Spi_ChnlSyncQSPI3Count"="$Spi_ChnlSyncQSPI3Count + num:i(1)"!]
            [!VAR "Spi_ChnlSyncQSPI3"="concat($Spi_ChnlSyncQSPI3,node:name(.),',')"!]
            [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
        [!ENDIF!]

        [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI4')
               and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
            [!VAR "Spi_ChnlSyncQSPI4Count"="$Spi_ChnlSyncQSPI4Count + num:i(1)"!]
            [!VAR "Spi_ChnlSyncQSPI4"="concat($Spi_ChnlSyncQSPI4,node:name(.),',')"!]
            [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
        [!ENDIF!]

        [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_IBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI5')
               and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
            [!VAR "Spi_ChnlSyncQSPI5Count"="$Spi_ChnlSyncQSPI5Count + num:i(1)"!]
            [!VAR "Spi_ChnlSyncQSPI5"="concat($Spi_ChnlSyncQSPI5,node:name(.),',')"!]
            [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
        [!ENDIF!]

    [!ENDIF!]
  [!ENDLOOP!]
[!ENDIF!]

[!IF "(SpiGeneral/SpiChannelBuffersAllowed = num:i(1)) or (SpiGeneral/SpiChannelBuffersAllowed = num:i(2))"!]
   [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
         [!VAR "Spi_EBChnlName"="node:name(.)"!]
        [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
           and (../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiHwUnitSynchronous/*[1] = 'ASYNCHRONOUS'))"!]
            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI0')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount0Async"="$Spi_EBChnlCount0Async + num:i(1)"!]
                [!VAR "Spi_EBChnl0Async"="concat($Spi_EBChnl0Async,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI1')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount1Async"="$Spi_EBChnlCount1Async + num:i(1)"!]
                [!VAR "Spi_EBChnl1Async"="concat($Spi_EBChnl1Async,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI2')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount2Async"="$Spi_EBChnlCount2Async + num:i(1)"!]
                [!VAR "Spi_EBChnl2Async"="concat($Spi_EBChnl2Async,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI3')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount3Async"="$Spi_EBChnlCount3Async + num:i(1)"!]
                [!VAR "Spi_EBChnl3Async"="concat($Spi_EBChnl3Async,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI4')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount4Async"="$Spi_EBChnlCount4Async + num:i(1)"!]
                [!VAR "Spi_EBChnl4Async"="concat($Spi_EBChnl4Async,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI5')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount5Async"="$Spi_EBChnlCount5Async + num:i(1)"!]
                [!VAR "Spi_EBChnl5Async"="concat($Spi_EBChnl5Async,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]
        [!ENDIF!]

    [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(0)) or ((../../../SpiGeneral/SpiLevelDelivered = num:i(2))
           and (../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiHwUnitSynchronous/*[1] = 'SYNCHRONOUS'))"!]
            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI0')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount0Sync"="$Spi_EBChnlCount0Sync + num:i(1)"!]
                [!VAR "Spi_EBChnl0Sync"="concat($Spi_EBChnl0Sync,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI1')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount1Sync"="$Spi_EBChnlCount1Sync + num:i(1)"!]
                [!VAR "Spi_EBChnl1Sync"="concat($Spi_EBChnl1Sync,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI2')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount2Sync"="$Spi_EBChnlCount2Sync + num:i(1)"!]
                [!VAR "Spi_EBChnl2Sync"="concat($Spi_EBChnl2Sync,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI3')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount3Sync"="$Spi_EBChnlCount3Sync + num:i(1)"!]
                [!VAR "Spi_EBChnl3Sync"="concat($Spi_EBChnl3Sync,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI4')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount4Sync"="$Spi_EBChnlCount4Sync + num:i(1)"!]
                [!VAR "Spi_EBChnl4Sync"="concat($Spi_EBChnl4Sync,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]

            [!IF "((node:ref(../../SpiJob/*[SpiChannelList/*[node:name(node:ref(SpiChannelAssignment)) = $Spi_EBChnlName]]/SpiDeviceAssignment))/SpiHwUnit = 'QSPI5')
                   and (not(text:contains(text:split($Spi_MasterChnlList,','), node:name(.))))"!]
                [!VAR "Spi_EBChnlCount5Sync"="$Spi_EBChnlCount5Sync + num:i(1)"!]
                [!VAR "Spi_EBChnl5Sync"="concat($Spi_EBChnl5Sync,node:name(.),',')"!]
                [!VAR "Spi_MasterChnlList" = "concat($Spi_MasterChnlList,node:name(.),',')"!]
            [!ENDIF!]
        [!ENDIF!]

    [!ENDLOOP!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY :  [cover parentID={36CCF821-7699-469f-BEF0-336AEA780CDD}][/cover]
MACRO: Spi_CGGetSharedSequence
Macro to get the sequences which shres the jobs
******************************************************************************/!]
[!MACRO "Spi_CGGetSharedSequence", "Spi_OutSequence" = ""!][!//
[!NOCODE!][!//

[!// let list of sequence which is being sharing a job with input sequence contains itself
[!VAR "Spi_MacSeqShareStr" = "''"!][!//
[!VAR "Spi_MacSeqShareStr"="concat($Spi_MacSeqShareStr,$Spi_OutSequence,',')"!]

[!// for input sequence node
[!SELECT "as:modconf('Spi')[1]/SpiDriver/SpiSequence/*[node:name(.) = $Spi_OutSequence]"!]
  [!// for each job assigned to it
  [!LOOP "./SpiJobAssignment/*"!]
    [!VAR "Spi_MacTempJob"="node:value(.)"!]
    [!// check all other sequence
    [!LOOP "../../../../SpiSequence/*"!]
      [!// if the other sequnce share same job assigned to input sequence
      [!LOOP "./SpiJobAssignment/*[node:value(.) = $Spi_MacTempJob]"!]
        [!// if the sequnce name is not already in the list
        [!IF "not(text:contains(text:split($Spi_MacSeqShareStr,','),node:name(../..)))"!]
          [!// add the sequence name to the list
          [!VAR "Spi_MacSeqShareStr"="concat($Spi_MacSeqShareStr,node:name(../..),',')"!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
  [!ENDLOOP!]
[!ENDSELECT!]

[!FOR "Index"="2" TO "count(text:split($Spi_MacSeqShareStr,','))"!]
[!CODE!][!//
[!//[cover parentID={4292AEDF-1347-4540-A7B6-6E8F66C1681A}][/cover][!//
  SpiConf_SpiSequence_[!"text:split($Spi_MacSeqShareStr,',')[num:i($Index)]"!],
[!ENDCODE!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={8F335064-9A88-4d2d-98E6-4A21D91BEA50}][/cover]
MACRO: Spi_CGGenerateSequenceConfigSyncOrAsync
Macro to generates the sequence configuration
******************************************************************************/!]
[!MACRO "Spi_CGGenerateSequenceConfigSyncOrAsync", "Spi_OutSeqQSPIxCount" = "", "Spi_OutSeqQSPIx" = "","SyncOrAsyncSeq" = ""!][!//
[!NOCODE!][!//

[!FOR "Spi_LoopCntr" = "num:i(1)" TO "$Spi_OutSeqQSPIxCount"!]
  [!SELECT "SpiDriver/SpiSequence/*[node:name(.) = text:split($Spi_OutSeqQSPIx,',')[position() = $Spi_LoopCntr]]"!]
[!CODE!][!//
  /* Sequence:[!"node:name(.)"!] */
  {
    SpiConf_SpiSequence_[!"node:name(.)"!],
[!ENDCODE!]
    [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or (../../../SpiGeneral/SpiLevelDelivered = num:i(2))"!]
      [!IF "node:exists(./SpiSeqEndNotification/*[1])"!]
        [!IF "not(num:isnumber(./SpiSeqEndNotification/*[1])) and (./SpiSeqEndNotification/*[1] != 'NULL_PTR')"!]
[!CODE!]
[!//
    /* Notification function */
    &[!"./SpiSeqEndNotification/*[1]"!],
[!ENDCODE!]
         [!ELSEIF "num:isnumber(./SpiSeqEndNotification/*[1])"!]
[!CODE!][!//
    /* Notification function */
    [!"num:inttohex(./SpiSeqEndNotification/*[1],8)"!],
[!ENDCODE!]
        [!ELSE!]
[!CODE!][!//
    /* Notification function */
    NULL_PTR,
[!ENDCODE!]
        [!ENDIF!]
      [!ELSE!]
[!CODE!][!//
    /* Notification function */
    NULL_PTR,
[!ENDCODE!]
      [!ENDIF!]
    [!ENDIF!]
[!CODE!][!//
    /* Job linked list */
    [!"node:name(.)"!]_JobLinkPtr_Physical,
[!IF "(../../../SpiGeneral/SpiLevelDelivered) != num:i(0)"!][!//
    /* Seq linked list, with jobs shared */
    [!"node:name(.)"!]_SeqSharePtr,
[!ENDIF!][!//
    /* No. of jobs in Seq */
    [!"num:i(count(./SpiJobAssignment/*))"!]U,
[!ENDCODE!]
    [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or (../../../SpiGeneral/SpiLevelDelivered = num:i(2))"!]
      [!IF "../../../SpiGeneral/SpiInterruptibleSeqAllowed = 'true'"!]
        [!IF "./SpiInterruptibleSequence = 'true'"!]
[!CODE!][!//
    /* Seq Interruptible or not */
    SPI_SEQ_INT_TRUE,
[!ENDCODE!]
        [!ELSE!]
[!CODE!][!//
    /* Seq Interruptible or not */
    SPI_SEQ_INT_FALSE,
[!ENDCODE!]
        [!ENDIF!]
      [!ENDIF!]
   [!ENDIF!]
   [!VAR "Spi_MacHwmoduleUsed"="0"!]
   [!LOOP "./SpiJobAssignment/*"!]
     [!IF "node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit = 'QSPI0'"!]
       [!VAR "Spi_MacHwmoduleUsed"="bit:bitset($Spi_MacHwmoduleUsed,0)"!]
     [!ELSEIF "node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit = 'QSPI1'"!]
       [!VAR "Spi_MacHwmoduleUsed"="bit:bitset($Spi_MacHwmoduleUsed,1)"!]
     [!ELSEIF "node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit = 'QSPI2'"!]
       [!VAR "Spi_MacHwmoduleUsed"="bit:bitset($Spi_MacHwmoduleUsed,2)"!]
     [!ELSEIF "node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit = 'QSPI3'"!]
       [!VAR "Spi_MacHwmoduleUsed"="bit:bitset($Spi_MacHwmoduleUsed,3)"!]
     [!ELSEIF "node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit = 'QSPI4'"!]
       [!VAR "Spi_MacHwmoduleUsed"="bit:bitset($Spi_MacHwmoduleUsed,4)"!]
     [!ELSEIF "node:ref(node:ref(.)/SpiDeviceAssignment)/SpiHwUnit = 'QSPI5'"!]
       [!VAR "Spi_MacHwmoduleUsed"="bit:bitset($Spi_MacHwmoduleUsed,5)"!]
     [!ELSE!]
        [!ERROR!]
           Undefined QSPI Hw module
        [!ENDERROR!]
     [!ENDIF!]
   [!ENDLOOP!]
[!CODE!][!//
    /* Hw Module Used ([!"num:inttobin($Spi_MacHwmoduleUsed,6)"!])*/
    [!"num:inttohex(num:i($Spi_MacHwmoduleUsed),2)"!]U,
[!ENDCODE!]
[!CODE!][!//
    /* Sync sequence = 0x00 or Async sequence = 0x01 */
    [!"num:inttohex(num:i($SyncOrAsyncSeq),2)"!]U
[!ENDCODE!]
  [!ENDSELECT!]
[!CODE!][!//
  }[!//
[!ENDCODE!]
      [!IF "num:i($Spi_MacTotalSeqCount) != num:i(1)"!]
[!CODE!][!//
,
[!ENDCODE!]
        [!VAR "Spi_MacTotalSeqCount"="$Spi_MacTotalSeqCount - num:i(1)"!]
      [!ENDIF!]
    [!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={8348D60C-1549-4a07-B063-31476B84CAC8}][/cover]
MACRO: Spi_CGGenerateSequenceConfig
Macro to fetch sequences in order of synchronous and asynchronous for a QSPIx belonging to a core
******************************************************************************/!]
[!MACRO "Spi_CGGenerateSequenceConfig", "CPUID" = ""!][!//
[!NOCODE!][!//






[!VAR "Spi_MacTotalSeqCount"="num:i(0)"!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(0)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
  [!VAR "Spi_MacTotalSeqCount"="$Spi_MacTotalSeqCount + $Spi_SeqSyncQSPI0Count + $Spi_SeqSyncQSPI1Count + $Spi_SeqSyncQSPI2Count + $Spi_SeqSyncQSPI3Count + $Spi_SeqSyncQSPI4Count + $Spi_SeqSyncQSPI5Count"!]
[!ENDIF!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(1)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
  [!VAR "Spi_MacTotalSeqCount"="($Spi_MacTotalSeqCount + $Spi_SeqAsyncQSPI0Count + $Spi_SeqAsyncQSPI1Count + $Spi_SeqAsyncQSPI2Count + $Spi_SeqAsyncQSPI3Count + $Spi_SeqAsyncQSPI4Count + $Spi_SeqAsyncQSPI5Count)"!]
[!ENDIF!]

[!/************* For Synchronous and ASYNCHRONOUS QSPI0 **************************/!]


    [!IF "$QSPI0CoreID = $CPUID"!]
          [!IF "$Spi_SeqSyncQSPI0Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Sequence[s] */
 [!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqSyncQSPI0Count","Spi_OutSeqQSPIx" = "$Spi_SeqSyncQSPI0","SyncOrAsyncSeq" = "num:i(0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_SeqAsyncQSPI0Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Sequence[s] on QSPI0 */
[!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqAsyncQSPI0Count","Spi_OutSeqQSPIx" = "$Spi_SeqAsyncQSPI0","SyncOrAsyncSeq" = "num:i(1)"!][!//
          [!ENDIF!]
    [!ENDIF!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI1 **************************/!]


    [!IF "$QSPI1CoreID = $CPUID"!]
          [!IF "$Spi_SeqSyncQSPI1Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Sequence[s] */
 [!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqSyncQSPI1Count","Spi_OutSeqQSPIx" = "$Spi_SeqSyncQSPI1","SyncOrAsyncSeq" = "num:i(0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_SeqAsyncQSPI1Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Sequence[s] on QSPI1 */
[!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqAsyncQSPI1Count","Spi_OutSeqQSPIx" = "$Spi_SeqAsyncQSPI1","SyncOrAsyncSeq" = "num:i(1)"!][!//
          [!ENDIF!]
    [!ENDIF!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI2 **************************/!]


    [!IF "$QSPI2CoreID = $CPUID"!]
          [!IF "$Spi_SeqSyncQSPI2Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Sequence[s] */
 [!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqSyncQSPI2Count","Spi_OutSeqQSPIx" = "$Spi_SeqSyncQSPI2","SyncOrAsyncSeq" = "num:i(0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_SeqAsyncQSPI2Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Sequence[s] on QSPI2 */
[!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqAsyncQSPI2Count","Spi_OutSeqQSPIx" = "$Spi_SeqAsyncQSPI2","SyncOrAsyncSeq" = "num:i(1)"!][!//
          [!ENDIF!]
    [!ENDIF!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI3 **************************/!]


    [!IF "$QSPI3CoreID = $CPUID"!]
          [!IF "$Spi_SeqSyncQSPI3Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Sequence[s] */
 [!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqSyncQSPI3Count","Spi_OutSeqQSPIx" = "$Spi_SeqSyncQSPI3","SyncOrAsyncSeq" = "num:i(0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_SeqAsyncQSPI3Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Sequence[s] on QSPI3 */
[!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqAsyncQSPI3Count","Spi_OutSeqQSPIx" = "$Spi_SeqAsyncQSPI3","SyncOrAsyncSeq" = "num:i(1)"!][!//
          [!ENDIF!]
    [!ENDIF!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI4 **************************/!]


    [!IF "$QSPI4CoreID = $CPUID"!]
          [!IF "$Spi_SeqSyncQSPI4Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Sequence[s] */
 [!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqSyncQSPI4Count","Spi_OutSeqQSPIx" = "$Spi_SeqSyncQSPI4","SyncOrAsyncSeq" = "num:i(0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_SeqAsyncQSPI4Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Sequence[s] on QSPI4 */
[!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqAsyncQSPI4Count","Spi_OutSeqQSPIx" = "$Spi_SeqAsyncQSPI4","SyncOrAsyncSeq" = "num:i(1)"!][!//
          [!ENDIF!]
    [!ENDIF!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI5 **************************/!]


    [!IF "$QSPI5CoreID = $CPUID"!]
          [!IF "$Spi_SeqSyncQSPI5Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Sequence[s] */
 [!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqSyncQSPI5Count","Spi_OutSeqQSPIx" = "$Spi_SeqSyncQSPI5","SyncOrAsyncSeq" = "num:i(0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_SeqAsyncQSPI5Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Sequence[s] on QSPI5 */
[!ENDCODE!]
        [!CALL "Spi_CGGenerateSequenceConfigSyncOrAsync","Spi_OutSeqQSPIxCount" = "$Spi_SeqAsyncQSPI5Count","Spi_OutSeqQSPIx" = "$Spi_SeqAsyncQSPI5","SyncOrAsyncSeq" = "num:i(1)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGCalcBaudAndDelayParams
Macro to Calculate the baudrate and delay params
******************************************************************************/!]
[!//[cover parentID={F7257FD1-B681-46ad-A55A-684B86DD2C2A}][/cover][!//
[!MACRO "Spi_CGCalcBaudAndDelayParams", "Spi_OutDevice" = ""!][!//
[!NOCODE!][!//
[!//[cover parentID={CDF9652F-C9C6-48da-A1CA-0DF593D0CE1C}] SystemClock [/cover][!//
[!SELECT "as:modconf('Spi')[1]/SpiDriver/SpiExternalDevice/*[node:name(.) = $Spi_OutDevice]"!]
[!/******** Baudrate Calculation **********/!]
  [!VAR "Spi_MacQspiFreq"="node:value(node:ref(../../SpiSystemClock)/McuPllDistributionSettingConfig/McuQspiFrequency)"!]
  [!VAR "Spi_MacBaudParamA"="num:i(1)"!]
  [!VAR "Spi_MacBaudParamB"="num:i(1)"!]
  [!VAR "Spi_MacBaudParamC"="num:i(1)"!]
  [!VAR "Spi_MacBaudParamABC"="num:i(2)"!]
  [!VAR "Spi_MacBaudParamTQ"="num:i(0)"!]
  [!VAR "Spi_MacBaudParamQ"="num:i(0)"!]
  [!IF "node:value(./SpiAutoCalcBaudParams) = 'true'"!]
    [!VAR "Spi_MacBaudRate"="node:value(./SpiBaudrate)"!]
    [!VAR "Spi_MacLoopBreak"="num:i(0)"!]
    [!FOR "Spi_MacBaudParamABC"="2" TO "10"!]
      [!FOR "Spi_MacBaudParamQ"="0" TO "63"!]
        [!IF "(($Spi_MacBaudParamABC)*($Spi_MacBaudParamQ + 1)) >= num:i(4)"!]
          [!IF "(($Spi_MacBaudParamABC)*($Spi_MacBaudRate)*($Spi_MacBaudParamQ + 1)) > $Spi_MacQspiFreq"!]
            [!BREAK!]
          [!ENDIF!]
          [!FOR "Spi_MacBaudParamTQ"="0" TO "255"!]
            [!VAR "Spi_MacTempValue"="($Spi_MacBaudParamABC)*($Spi_MacBaudRate)*($Spi_MacBaudParamTQ + 1)*($Spi_MacBaudParamQ + 1)"!]
            [!IF "$Spi_MacTempValue = $Spi_MacQspiFreq"!]
               [!VAR "Spi_MacLoopBreak"="1"!]
               [!BREAK!]
            [!ELSEIF "$Spi_MacTempValue > $Spi_MacQspiFreq"!]
               [!BREAK!]
            [!ENDIF!]
          [!ENDFOR!]
          [!IF "num:i($Spi_MacLoopBreak)=num:i(1)"!]
            [!BREAK!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDFOR!]
      [!IF "num:i($Spi_MacLoopBreak)=num:i(1)"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDFOR!]
    [!IF "num:i($Spi_MacLoopBreak)=num:i(0)"!]
      [!ERROR!]
        Autocalculation for the spcified baudrate([!"$Spi_MacBaudRate"!]Hz) could not be done for the given frequence(FQspi = [!"$Spi_MacQspiFreq"!]Hz)
      [!ENDERROR!]
    [!ENDIF!]
    [!VAR "Spi_MacBaudParamABC"="$Spi_MacBaudParamABC - 1"!]
    [!VAR "Spi_MacBaudParamC"="num:i(1)"!]
    [!VAR "Spi_MacBaudParamB"="num:i(($Spi_MacBaudParamABC - $Spi_MacBaudParamC) div num:i(2))"!]
    [!VAR "Spi_MacBaudParamA"="num:i($Spi_MacBaudParamABC - ($Spi_MacBaudParamB + $Spi_MacBaudParamC))"!]
    [!IF "$Spi_MacBaudParamB > $Spi_MacBaudParamC"!]
      [!VAR "Spi_MacBaudParamB"="$Spi_MacBaudParamB + $Spi_MacBaudParamC"!]
      [!VAR "Spi_MacBaudParamC"="$Spi_MacBaudParamB - $Spi_MacBaudParamC"!]
      [!VAR "Spi_MacBaudParamB"="$Spi_MacBaudParamB - $Spi_MacBaudParamC"!]
    [!ENDIF!]
  [!ELSE!]
    [!VAR "Spi_MacBaudParamA"="node:value(./SpiBaudrateParams/*[1]/SpiBaudParamA)"!]
    [!VAR "Spi_MacBaudParamB"="node:value(./SpiBaudrateParams/*[1]/SpiBaudParamB)"!]
    [!VAR "Spi_MacBaudParamC"="node:value(./SpiBaudrateParams/*[1]/SpiBaudParamC)"!]
    [!VAR "Spi_MacBaudParamTQ"="node:value(./SpiBaudrateParams/*[1]/SpiBaudParamTQ)"!]
    [!VAR "Spi_MacBaudParamQ"="node:value(./SpiBaudrateParams/*[1]/SpiBaudParamQ)"!]
    [!VAR "Spi_MacBaudRate"="$Spi_MacQspiFreq div (($Spi_MacBaudParamTQ + num:i(1))*($Spi_MacBaudParamQ + 1)*($Spi_MacBaudParamA + num:i(1) + $Spi_MacBaudParamB + $Spi_MacBaudParamC))"!]
  [!ENDIF!]
  [!//[cover parentID={2F755E2F-9953-439a-A64A-C57C01DA3D60}][/cover][!//
  [!IF "./SpiInternalLoopBackSupport = 'true'"!]
    [!VAR "Spi_MacLoopBack"="num:i(1)"!]
  [!ELSE!]
    [!VAR "Spi_MacLoopBack"="num:i(0)"!]
  [!ENDIF!]

  [!IF "./SpiParitySupport != 'UNUSED'"!]
    [!VAR "Spi_MacParitysupport"="num:i(1)"!]
  [!ELSE!]
    [!VAR "Spi_MacParitysupport"="num:i(0)"!]
  [!ENDIF!]

  [!IF "./SpiDataShiftEdge = 'TRAILING'"!]
    [!VAR "Spi_MacShiftEdge"="num:i(0)"!]
  [!ELSE!]
    [!VAR "Spi_MacShiftEdge"="num:i(1)"!]
  [!ENDIF!]

  [!IF "./SpiShiftClockIdleLevel = 'LOW'"!]
    [!VAR "Spi_MacClkIdleLevel"="num:i(0)"!]
  [!ELSE!]
    [!VAR "Spi_MacClkIdleLevel"="num:i(1)"!]
  [!ENDIF!]

[!CODE!][!//
    Spi_BaudRateAndClockParam(  /* Baudrate = [!"$Spi_MacBaudRate"!]Hz */
     ([!"num:inttohex($Spi_MacBaudParamTQ,2)"!]U), ([!"num:inttohex($Spi_MacLoopBack,2)"!]U),          /* TQ , LoopBack */
     ([!"num:inttohex($Spi_MacBaudParamQ,2)"!]U), ([!"num:inttohex($Spi_MacBaudParamA,2)"!]U),          /*  Q , A        */
     ([!"num:inttohex($Spi_MacBaudParamB,2)"!]U), ([!"num:inttohex($Spi_MacBaudParamC,2)"!]U),          /*  B , C        */
     ([!"num:inttohex($Spi_MacShiftEdge,2)"!]U), ([!"num:inttohex($Spi_MacClkIdleLevel,2)"!]U),          /*  CPH , CPOL   */
     ([!"num:inttohex($Spi_MacParitysupport,2)"!]U)                    /*  PAREN        */
    ),
[!ENDCODE!]

[!/******** Delay Calculation **********/!]
  [!IF "./SpiParitySupport != 'ODD'"!]
    [!VAR "Spi_MacParitysupport"="num:i(1)"!]
  [!ELSE!]
    [!VAR "Spi_MacParitysupport"="num:i(0)"!]
  [!ENDIF!]

  [!IF "(./SpiEnableCs = 'true') and (./SpiCsSelection/*[1] = 'CS_VIA_GPIO')"!]
    [!CODE!][!//
    Spi_IdleLeadTrailParam(
    (1U), (1U), /* IPRE,IDLE:   IdleA/B delay = 1.0E-7s */
    (1U), (1U), /* LPRE,LEAD:   Lead delay    = 1.0E-7s */
    (1U), (1U),/* TPRE, TRAIL: Trail delay   = 1.0E-7s */
    ([!"num:i($Spi_MacParitysupport)"!]U)
    ),
    [!ENDCODE!]
  [!ELSE!]
  [!VAR "Spi_MacDelayIdlePre"="num:i(1)"!]
  [!VAR "Spi_MacDelayIdleLength"="num:i(1)"!]
  [!VAR "Spi_MacDelayLeadPre"="num:i(1)"!]
  [!VAR "Spi_MacDelayLeadLength"="num:i(1)"!]
  [!VAR "Spi_MacDelayTrailPre"="num:i(1)"!]
  [!VAR "Spi_MacDelayTrailLength"="num:i(1)"!]
  [!IF "node:value(./SpiAutoCalcDelayParams) = 'true'"!]
    [!VAR "Spi_MacIdleTime"="./SpiIdleTime "!]
    [!VAR "Spi_MacLeadTime"="./SpiTimeClk2Cs"!]
    [!VAR "Spi_MacTrailTime"="./SpiTrailingTime "!]

 [!/* Idle Delay Params */!]
 [!VAR "Spi_IPre"="num:i(0)"!]
 [!VAR "Spi_xIdleDelay"="num:i(0)"!]
 [!FOR "Spi_xIdleDelay"="1" TO "9"!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (1 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(0)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (4 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(1)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (16 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(2)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (64 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(3)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (256 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(4)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (1024 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(5)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (4096 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(6)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacIdleTime * $Spi_MacQspiFreq)) = (16384 * ($Spi_xIdleDelay))"!]
   [!VAR "Spi_IPre"="num:i(7)"!]
   [!BREAK!]
  [!ENDIF!]
 [!ENDFOR!]

 [!IF "$Spi_xIdleDelay < num:i(9)"!]
  [!VAR "Spi_xIdleDelay"="num:i(($Spi_xIdleDelay) -1)"!]
 [!ELSE!]
   [!ERROR!]
    Autocalculation for the spcified Idle Delay([!"$Spi_MacIdleTime"!]s) could not be done for the given frequence(FQspi = [!"$Spi_MacQspiFreq"!]Hz)
   [!ENDERROR!]
 [!ENDIF!]

  [!/* Lead Delay Params */!]
 [!VAR "Spi_LPre"="num:i(0)"!]
 [!VAR "Spi_xLeadDelay"="num:i(0)"!]
 [!FOR "Spi_xLeadDelay"="1" TO "9"!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (1 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(0)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (4 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(1)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (16 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(2)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (64 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(3)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (256 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(4)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (1024 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(5)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (4096 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(6)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacLeadTime * $Spi_MacQspiFreq)) = (16384 * ($Spi_xLeadDelay))"!]
   [!VAR "Spi_LPre"="num:i(7)"!]
   [!BREAK!]
  [!ENDIF!]
 [!ENDFOR!]

 [!IF "$Spi_xLeadDelay < num:i(9)"!]
  [!VAR "Spi_xLeadDelay"="num:i(($Spi_xLeadDelay) -1)"!]
 [!ELSE!]
    [!ERROR!]
        Autocalculation for the spcified Idle Delay([!"$Spi_MacLeadTime"!]s) could not be done for the given frequence(FQspi = [!"$Spi_MacQspiFreq"!]Hz)
    [!ENDERROR!]
 [!ENDIF!]
 [!/* Trail Delay Params */!]
 [!VAR "Spi_TPre"="num:i(0)"!]
 [!VAR "Spi_xTrailDelay"="num:i(0)"!]
 [!FOR "Spi_xTrailDelay"="1" TO "9"!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (1 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(0)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (4 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(1)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (16 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(2)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (64 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(3)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (256 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(4)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (1024 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(5)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (4096 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(6)"!]
   [!BREAK!]
  [!ENDIF!]
  [!IF "(round($Spi_MacTrailTime * $Spi_MacQspiFreq)) = (16384 * ($Spi_xTrailDelay))"!]
   [!VAR "Spi_TPre"="num:i(7)"!]
   [!BREAK!]
  [!ENDIF!]
 [!ENDFOR!]

 [!IF "$Spi_xTrailDelay < num:i(9)"!]
  [!VAR "Spi_xTrailDelay"="num:i(($Spi_xTrailDelay) -1)"!]
 [!ELSE!]
  [!ERROR!]
   Autocalculation for the spcified Idle Delay([!"$Spi_MacTrailTime"!]s) could not be done for the given frequence(FQspi = [!"$Spi_MacQspiFreq"!]Hz)
  [!ENDERROR!]
 [!ENDIF!]
[!ELSE!]
[!VAR "Spi_IPre"="node:value(./SpiDelayParams/*[1]/SpiDelayParamIdlePre)"!]
    [!VAR "Spi_xIdleDelay"="node:value(./SpiDelayParams/*[1]/SpiDelayParamIdleLength)"!]
    [!VAR "Spi_LPre"="node:value(./SpiDelayParams/*[1]/SpiDelayParamLeadPre)"!]
    [!VAR "Spi_xLeadDelay"="node:value(./SpiDelayParams/*[1]/SpiDelayParamLeadLength)"!]
    [!VAR "Spi_TPre"="node:value(./SpiDelayParams/*[1]/SpiDelayParamTrailPre)"!]
    [!VAR "Spi_xTrailDelay"="node:value(./SpiDelayParams/*[1]/SpiDelayParamTrailLength)"!]
    [!VAR "Spi_MacIdleTime"="(bit:shl(1,$Spi_MacDelayIdlePre*2)*($Spi_MacDelayIdleLength + 1)) div $Spi_MacQspiFreq"!]
    [!VAR "Spi_MacLeadTime"="(bit:shl(1,$Spi_MacDelayLeadPre*2)*($Spi_MacDelayLeadLength + 1)) div $Spi_MacQspiFreq"!]
    [!VAR "Spi_MacTrailTime"="(bit:shl(1,$Spi_MacDelayTrailPre*2)*($Spi_MacDelayTrailLength + 1)) div $Spi_MacQspiFreq"!]
[!ENDIF!]

[!CODE!][!//
    Spi_IdleLeadTrailParam(
     ([!"num:i($Spi_IPre)"!]U), ([!"num:i($Spi_xIdleDelay)"!]U), /* IPRE,IDLE:   IdleA/B delay = [!"$Spi_MacIdleTime"!]s */
     ([!"num:i($Spi_LPre)"!]U), ([!"num:i($Spi_xLeadDelay)"!]U), /* LPRE,LEAD:   Lead delay    = [!"$Spi_MacLeadTime"!]s */
     ([!"num:i($Spi_TPre)"!]U), ([!"num:i($Spi_xTrailDelay)"!]U),/* TPRE, TRAIL: Trail delay   = [!"$Spi_MacTrailTime"!]s */
     ([!"num:i($Spi_MacParitysupport)"!]U)
    ),
[!ENDCODE!]
[!ENDIF!]
[!ENDSELECT!]
[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
TRACEABILITY : [cover parentID={C10A3192-881A-4127-860C-339D6F8F9B36}][/cover]
MACRO: Spi_CGGenerateJobConfigSyncOrAsync
Macro to generates the job configuration
******************************************************************************/!]
[!MACRO "Spi_CGGenerateJobConfigSyncOrAsync", "Spi_OutJobQSPIxCount" = "", "Spi_OutJobQSPIx" = ""!][!//
[!NOCODE!][!//

[!FOR "Spi_LoopCntr" = "num:i(1)" TO "$Spi_OutJobQSPIxCount"!]
  [!SELECT "SpiDriver/SpiJob/*[node:name(.) = text:split($Spi_OutJobQSPIx,',')[position() = $Spi_LoopCntr]]"!]
[!CODE!]
[!//
  /* Job:[!"node:name(.)"!] */
  {
    SpiConf_SpiJob_[!"node:name(.)"!],
[!ENDCODE!]
    [!IF "(../../../SpiGeneral/SpiLevelDelivered = num:i(1)) or (../../../SpiGeneral/SpiLevelDelivered = num:i(2))"!]
      [!IF "node:exists(./SpiJobEndNotification/*[1])"!]
        [!IF "not(num:isnumber(./SpiJobEndNotification/*[1])) and (./SpiJobEndNotification/*[1] != 'NULL_PTR')"!]
[!CODE!][!//
    &[!"./SpiJobEndNotification/*[1]"!], /* Notification function */
[!ENDCODE!]
         [!ELSEIF "num:isnumber(./SpiJobEndNotification/*[1])"!]
[!CODE!][!//
    [!"num:inttohex(./SpiJobEndNotification/*[1],8)"!], /* Notification function address */
[!ENDCODE!]
        [!ELSE!]
[!CODE!][!//
    NULL_PTR,                   /* No Notification function */
[!ENDCODE!]
        [!ENDIF!]
      [!ELSE!]
[!CODE!][!//
    NULL_PTR,                   /* No Notification function */
[!ENDCODE!]
      [!ENDIF!]
    [!ENDIF!]
[!CALL "Spi_CGCalcBaudAndDelayParams","Spi_OutDevice" = "node:name(node:ref(./SpiDeviceAssignment))"!][!//
[!CODE!][!//
    [!"node:name(.)"!]_ChannelLinkPtr_Physical, /* Channel linked list Physical*/
[!ENDCODE!]
   [!IF "node:ref(./SpiDeviceAssignment)/SpiEnableCs = 'true'"!]
     [!IF "node:ref(./SpiDeviceAssignment)/SpiCsSelection/*[1] = 'CS_VIA_GPIO'"!]
[!CODE!][!//
    (uint16)(([!"node:ref(./SpiDeviceAssignment)/SpiCsGpio/*[1]/SpiCsGpioPortSelection"!]U << 4U)|([!"node:ref(./SpiDeviceAssignment)/SpiCsGpio/*[1]/SpiCsGpioPinSelection"!]U)), /* CS_VIA_GPIO */
[!ENDCODE!]
     [!ELSE!]
[!CODE!][!//
    SPI_CS_VIA_HW_OR_NONE,   /* CS_VIA_HW */
[!ENDCODE!]
     [!ENDIF!]
   [!ELSE!]
[!CODE!][!//
    SPI_CS_VIA_HW_OR_NONE,   /* CS Disabled */
[!ENDCODE!]
   [!ENDIF!]

[!CODE!][!//
    (uint8)[!"./SpiJobPriority"!]U,               /* Job Priority : 0...3*/
[!ENDCODE!]

[!CODE!][!//
    (uint8)STD_[!"node:ref(./SpiDeviceAssignment)/SpiCsPolarity"!],              /* CS polarity */
[!ENDCODE!]

[!CODE!][!//
     /* Chnl[bit:7:4],QSPI[3:0] */
    (uint8)((SPI_QSPI_[!"node:ref(./SpiDeviceAssignment)/SpiCsIdentifier"!] << 4U)|SPI_[!"(node:ref(./SpiDeviceAssignment)/SpiHwUnit)"!]_INDEX),
[!ENDCODE!]
[!CODE!][!//
    SPI_PARITY_[!"node:ref(./SpiDeviceAssignment)/SpiParitySupport"!],        /* Parity support */
[!//
    [!IF "./SpiFrameBasedCS = 'true'"!][!//
(1U)                    /*Frame based CS is enabled*/
    [!ELSE!][!//
(0U)                    /*Frame based CS is disabled*/
[!ENDIF!][!//
[!ENDCODE!]
  [!ENDSELECT!]
[!CODE!][!//
  }[!//
[!ENDCODE!]
      [!IF "num:i($Spi_MacTotalJobCount) != num:i(1)"!]
[!CODE!][!//
,
[!ENDCODE!]
        [!VAR "Spi_MacTotalJobCount"="$Spi_MacTotalJobCount - num:i(1)"!]
      [!ENDIF!]
    [!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY :  [cover parentID={5AFCD94B-3B2D-4707-BD12-D2F57A6D857F}][/cover]
MACRO: Spi_CGGenerateJobConfig
Macro to fetch job in order of synchronous and asynchronous for a QSPIx belonging to a core
******************************************************************************/!]
[!MACRO "Spi_CGGenerateJobConfig","CPUID" = ""!][!//
[!NOCODE!][!//





[!VAR "Spi_MacTotalJobCount"="num:i(0)"!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(0)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
  [!VAR "Spi_MacTotalJobCount"="$Spi_MacTotalJobCount + $Spi_JobSyncQSPI0Count + $Spi_JobSyncQSPI1Count + $Spi_JobSyncQSPI2Count + $Spi_JobSyncQSPI3Count + $Spi_JobSyncQSPI4Count + $Spi_JobSyncQSPI5Count"!]
[!ENDIF!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(1)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
  [!VAR "Spi_MacTotalJobCount"="($Spi_MacTotalJobCount + $Spi_JobAsyncQSPI0Count + $Spi_JobAsyncQSPI1Count + $Spi_JobAsyncQSPI2Count + $Spi_JobAsyncQSPI3Count + $Spi_JobAsyncQSPI4Count + $Spi_JobAsyncQSPI5Count)"!]
[!ENDIF!]

[!/************* For Synchronous and ASYNCHRONOUS QSPI0 **************************/!]

    [!IF "$QSPI0CoreID = $CPUID"!]
          [!IF "$Spi_JobSyncQSPI0Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Job[s] */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobSyncQSPI0Count","Spi_OutJobQSPIx" = "$Spi_JobSyncQSPI0"!][!//
          [!ENDIF!]


          [!IF "$Spi_JobAsyncQSPI0Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Job[s] on QSPI0 */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobAsyncQSPI0Count","Spi_OutJobQSPIx" = "$Spi_JobAsyncQSPI0"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI1 **************************/!]
    [!IF "$QSPI1CoreID = $CPUID"!]
          [!IF "$Spi_JobSyncQSPI1Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Job[s] */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobSyncQSPI1Count","Spi_OutJobQSPIx" = "$Spi_JobSyncQSPI1"!][!//
          [!ENDIF!]


          [!IF "$Spi_JobAsyncQSPI1Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Job[s] on QSPI1 */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobAsyncQSPI1Count","Spi_OutJobQSPIx" = "$Spi_JobAsyncQSPI1"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI2 **************************/!]
    [!IF "$QSPI2CoreID = $CPUID"!]
          [!IF "$Spi_JobSyncQSPI2Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Job[s] */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobSyncQSPI2Count","Spi_OutJobQSPIx" = "$Spi_JobSyncQSPI2"!][!//
          [!ENDIF!]


          [!IF "$Spi_JobAsyncQSPI2Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Job[s] on QSPI2 */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobAsyncQSPI2Count","Spi_OutJobQSPIx" = "$Spi_JobAsyncQSPI2"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI3 **************************/!]
    [!IF "$QSPI3CoreID = $CPUID"!]
          [!IF "$Spi_JobSyncQSPI3Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Job[s] */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobSyncQSPI3Count","Spi_OutJobQSPIx" = "$Spi_JobSyncQSPI3"!][!//
          [!ENDIF!]


          [!IF "$Spi_JobAsyncQSPI3Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Job[s] on QSPI3 */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobAsyncQSPI3Count","Spi_OutJobQSPIx" = "$Spi_JobAsyncQSPI3"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI4 **************************/!]
    [!IF "$QSPI4CoreID = $CPUID"!]
          [!IF "$Spi_JobSyncQSPI4Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Job[s] */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobSyncQSPI4Count","Spi_OutJobQSPIx" = "$Spi_JobSyncQSPI4"!][!//
          [!ENDIF!]


          [!IF "$Spi_JobAsyncQSPI4Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Job[s] on QSPI4 */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobAsyncQSPI4Count","Spi_OutJobQSPIx" = "$Spi_JobAsyncQSPI4"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI5 **************************/!]
    [!IF "$QSPI5CoreID = $CPUID"!]
          [!IF "$Spi_JobSyncQSPI5Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Job[s] */
[!//
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobSyncQSPI5Count","Spi_OutJobQSPIx" = "$Spi_JobSyncQSPI5"!][!//
          [!ENDIF!]


          [!IF "$Spi_JobAsyncQSPI5Count != num:i(0)"!]
        [!CODE!][!//
  /* Asynchronous Job[s] on QSPI5 */
[!ENDCODE!][!//
        [!CALL "Spi_CGGenerateJobConfigSyncOrAsync","Spi_OutJobQSPIxCount" = "$Spi_JobAsyncQSPI5Count","Spi_OutJobQSPIx" = "$Spi_JobAsyncQSPI5"!][!//
          [!ENDIF!]
    [!ENDIF!]



[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGGenerateQspix
Macro to generate the QspiHw configuration
******************************************************************************/!]
[!MACRO "Spi_CGGenerateQspix","Spi_OutQSPIx" = ""!][!//
[!NOCODE!][!//
[!//[cover parentID={811D80FF-21BB-4b8a-A141-05DA956B0016}][/cover][!//
[!// Initialize parameters as per input QSPI hardware unit
[!IF "$Spi_OutQSPIx = 'QSPI0'"!]
[!VAR "Spi_MacQspixUsed"="$Spi_MacQspi0Used"!]
[!VAR "Spi_MacQspixHwType"="$Spi_MacQspi0HwType"!]
[!VAR "Spi_MacQspixHwref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi'"!]
[!VAR "Spi_MacQspixSleepref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix'"!]
[!VAR "Spi_MacQspixMRSTref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix'"!]
[!ELSEIF "$Spi_OutQSPIx = 'QSPI1'"!]
[!VAR "Spi_MacQspixUsed"="$Spi_MacQspi1Used"!]
[!VAR "Spi_MacQspixHwType"="$Spi_MacQspi1HwType"!]
[!VAR "Spi_MacQspixHwref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi'"!]
[!VAR "Spi_MacQspixSleepref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix'"!]
[!VAR "Spi_MacQspixMRSTref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix'"!]
[!ELSEIF "$Spi_OutQSPIx = 'QSPI2'"!]
[!VAR "Spi_MacQspixUsed"="$Spi_MacQspi2Used"!]
[!VAR "Spi_MacQspixHwType"="$Spi_MacQspi2HwType"!]
[!VAR "Spi_MacQspixHwref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi'"!]
[!VAR "Spi_MacQspixSleepref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix'"!]
[!VAR "Spi_MacQspixMRSTref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix'"!]]
[!ELSEIF "$Spi_OutQSPIx = 'QSPI3'"!]
[!VAR "Spi_MacQspixUsed"="$Spi_MacQspi3Used"!]
[!VAR "Spi_MacQspixHwType"="$Spi_MacQspi3HwType"!]
[!VAR "Spi_MacQspixHwref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi'"!]
[!VAR "Spi_MacQspixSleepref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix'"!]
[!VAR "Spi_MacQspixMRSTref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix'"!]
[!ELSEIF "$Spi_OutQSPIx = 'QSPI4'"!]
[!VAR "Spi_MacQspixUsed"="$Spi_MacQspi4Used"!]
[!VAR "Spi_MacQspixHwType"="$Spi_MacQspi4HwType"!]
[!VAR "Spi_MacQspixHwref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi'"!]
[!VAR "Spi_MacQspixSleepref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix'"!]
[!VAR "Spi_MacQspixMRSTref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix'"!]
[!ELSEIF "$Spi_OutQSPIx = 'QSPI5'"!]
[!VAR "Spi_MacQspixUsed"="$Spi_MacQspi5Used"!]
[!VAR "Spi_MacQspixHwType"="$Spi_MacQspi5HwType"!]
[!VAR "Spi_MacQspixHwref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi'"!]
[!VAR "Spi_MacQspixSleepref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix'"!]
[!VAR "Spi_MacQspixMRSTref"="'./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix'"!]
[!ENDIF!]

[!IF "$Spi_MacQspixUsed = num:i(1)"!]
  [!VAR "Spi_MacQspiIndex"="num:i(substring-after($Spi_OutQSPIx, 'QSPI'))"!]
[!CODE!][!//
  /* [!"$Spi_OutQSPIx"!] */
static const Spi_QspiHwConfigType Spi_kQspiHwConfig[!"$Spi_OutQSPIx"!] =
{
[!ENDCODE!]
  [!VAR "Spi_MacActiveCSPol"="num:i(0)"!]
  [!LOOP "SpiDriver/SpiExternalDevice/*[SpiHwUnit = $Spi_OutQSPIx]"!]
    [!IF "./SpiEnableCs = 'true'"!]
      [!IF "./SpiCsSelection/*[1] = 'CS_VIA_PERIPHERAL_ENGINE'"!]
        [!VAR "Spi_MacCSChnl"="num:i(substring-after(./SpiCsIdentifier, 'CHANNEL'))"!]
        [!VAR "Spi_MacActiveCSPol"="bit:bitset($Spi_MacActiveCSPol,($Spi_MacCSChnl + num:i(16)))"!]
        [!IF "./SpiCsPolarity = 'HIGH'"!]
          [!VAR "Spi_MacActiveCSPol"="bit:bitset($Spi_MacActiveCSPol,$Spi_MacCSChnl)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!CODE!][!//
  [!"num:inttohex($Spi_MacActiveCSPol,8)"!]U,               /* Active CS Level, SSOC SFR value */
[!ENDCODE!]

     [!IF "$Spi_MacQspixHwType = num:i(1)"!]
[!CODE!][!//
  SPI_ASYNC_IB_BUFFER_SIZE_QSPI[!"$Spi_MacQspiIndex"!],  /* Buffers on QSPI[!"$Spi_MacQspiIndex"!] only */
  SPI_JOB_QUEUE_LENGTH_QSPI[!"$Spi_MacQspiIndex"!],/* Job Queue Length */
[!ENDCODE!]
     [!ELSE!]
[!CODE!][!//
  0,   /* Buffers on all synchronous QSPI Hw */
  0U,                        /* Queue length can be ignored for Sync */
[!ENDCODE!]
     [!ENDIF!]
  [!IF "node:value(SpiGeneral/SpiLevelDelivered) != num:i(0)"!]
    [!IF "$Spi_MacQspixHwType = num:i(1)"!]
[!CODE!][!//
  (uint8)[!"node:ref(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi/*[1]/SpiHwDmaChannelReceptionRef)/DmaChannelId"!]U,                 /* DMA Rx Channel */
  (uint8)[!"node:ref(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHwDmaConfigurationQspi/*[1]/SpiHwDmaChannelTransmissionRef)/DmaChannelId"!]U,                 /* DMA Tx Channel */
  SPI_DMA_MAX_TCS_NUM_QSPI[!"$Spi_MacQspiIndex"!], /* DMA TCS count, for both Rx and Tx */
[!ENDCODE!]
    [!ELSE!]
[!CODE!][!//
  (uint8)SPI_DMA_CHNL_INVALID,   /* DMA Tx Channel */
  (uint8)SPI_DMA_CHNL_INVALID,   /* DMA Rx Channel */
  0U,                        /* DMA TCS value can be ignored for Sync */
[!ENDCODE!]
    [!ENDIF!]
  [!ENDIF!]

    [!IF "node:value(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiSleepEnableQspix) = 'true'"!]
[!CODE!][!//
  SPI_CLK_SLEEP_ENABLE,      /* Module Sleep enabled */
[!ENDCODE!]
    [!ELSE!]
[!CODE!][!//
  SPI_CLK_SLEEP_DISABLE,     /* Module Sleep disabled */
[!ENDCODE!]
    [!ENDIF!]
    [!VAR "Spi_MRISVal"="num:i(0)"!]
    [!IF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'A_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(0)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'B_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(1)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'C_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(2)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'CN_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(2)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'CP_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(2)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'D_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(3)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'DN_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(3)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'DP_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(3)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'E_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(4)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'F_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(5)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'FN_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(5)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'FP_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(5)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix),'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'G_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(6)"!]U,
    [!ELSEIF "contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'MRST') = 'true' and contains(./SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = $Spi_OutQSPIx]/SpiHWPinMRSTQspix,'H_') = 'true'"!][!//
    [!VAR "Spi_MRISVal"="num:i(7)"!]U,
    [!ENDIF!][!//
[!CODE!][!//
  (uint8)[!"num:i($Spi_MRISVal)"!]U,                 /* Input class, MRIS bit field in PISEL SFR */
[!ENDCODE!]

     [!IF "$Spi_MacQspixHwType = num:i(1)"!]
[!CODE!][!//
  [!"num:i(count(SpiDriver/SpiSequence/*[node:ref(node:ref(SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQSPIx]))"!]U                         /* Max Sequence Count on the QSPI */
[!ENDCODE!]
     [!ELSE!]
[!CODE!][!//
  [!"num:i(count(SpiDriver/SpiSequence/*[node:ref(node:ref(SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQSPIx]))"!]U                         /* Applicable only for Async QSPI */
[!ENDCODE!]
     [!ENDIF!]

[!CODE!][!//
};
[!ENDCODE!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={DD13C2CB-8839-4278-AC09-EE7F8A1BE438}][/cover]
MACRO: Spi_CGGenerateChnlConfigSyncOrAsync
Macro to generates the Channel configuration
******************************************************************************/!]
[!MACRO "Spi_CGGenerateChnlConfigSyncOrAsync", "Spi_OutChnlQSPIxCount" = "", "Spi_OutChnlQSPIx" = "", "Spi_OutHwUnit" = ""!][!//
[!NOCODE!]
[!//
[!FOR "Spi_LoopCntr" = "$Spi_OutChnlQSPIxCount" TO "num:i(1)" STEP "-1"!]
  [!SELECT "SpiDriver/SpiChannel/*[node:name(.) = text:split($Spi_OutChnlQSPIx,',')[position() = $Spi_LoopCntr]]"!]
[!// [cover parentID={D05F33EF-7CB8-46da-8F4E-0CD77F956603}][/cover]
[!CODE!]
  [!//
  /* Channel:[!"node:name(.)"!] */
  {
[!ENDCODE!]
    [!VAR "Spi_MacDefaultData"="num:i(0)"!]
    [!IF "node:exists(./SpiDefaultData/*[1])"!]
      [!VAR "Spi_MacDefaultData"="num:i(./SpiDefaultData/*[1])"!]
    [!ENDIF!]
[!CODE!][!//
    [!"num:inttohex($Spi_MacDefaultData,8)"!]U,     /* Default data */
[!ENDCODE!]

    [!IF "./SpiChannelType = 'EB'"!]
[!CODE!][!//
    [!"num:inttohex(./SpiEbMaxLength,4)"!]U,         /* Number of Data Elements */
    SPI_EB_CHANNEL,  /* External Buffer Channel */
[!ENDCODE!]
    [!ELSE!]
[!CODE!][!//
    [!"num:inttohex(./SpiIbNBuffers,4)"!]U,         /* Number of Data Elements */
    SPI_IB_CHANNEL,  /* Internal Buffer Channel */
[!ENDCODE!]
    [!ENDIF!]

[!IF "../../../SpiGeneral/SpiChannelBuffersAllowed != num:i(1)"!]
[!CODE!][!//
    [!"num:inttohex($Spi_OutHwUnit,2)"!]U,           /* Sync/Async[7:4], QSPIHW[3:0], NA for EB */
[!ENDCODE!]
[!ENDIF!]

    [!VAR "Spi_MacInitialBit"="num:i(0)"!]
    [!IF "./SpiTransferStart = 'MSB'"!]
      [!VAR "Spi_MacInitialBit"="num:i(1)"!]
    [!ENDIF!]
[!CODE!][!//
    [!"num:inttohex(bit:or(bit:shl($Spi_MacInitialBit,7),(num:i(./SpiDataWidth))),2)"!]U,            /* [!"./SpiTransferStart"!][7], DataWidth=[!"num:i(./SpiDataWidth)"!][6:0] */
    SpiConf_SpiChannel_[!"node:name(.)"!]
[!ENDCODE!]

  [!ENDSELECT!]
[!CODE!][!//
  }[!//
[!ENDCODE!]
      [!IF "num:i($Spi_MacTotalChnlCount) != num:i(1)"!]
[!CODE!][!//
,
[!ENDCODE!]
        [!VAR "Spi_MacTotalChnlCount"="$Spi_MacTotalChnlCount - num:i(1)"!]
      [!ENDIF!]
    [!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={960B764B-AEE3-4ac9-94BF-6530F7879CB8}][/cover]
MACRO: Spi_CGGenerateChnlConfig
Macro to fetch channel in order of synchronous and asynchronous IB  and synchronous and asynchronous EB  for a QSPIx belonging to a core.
******************************************************************************/!]
[!MACRO "Spi_CGGenerateChnlConfig", "CPUID" = ""!][!//
[!NOCODE!][!//

[!VAR "Spi_MacTotalChnlCount"="num:i(0)"!]
[!VAR "Spi_MacTotalChnlCount"="$Spi_MacTotalChnlCount + $Spi_EBChnlCount0Sync + $Spi_EBChnlCount1Sync + $Spi_EBChnlCount2Sync + $Spi_EBChnlCount3Sync + $Spi_EBChnlCount4Sync + $Spi_EBChnlCount5Sync + $Spi_EBChnlCount0Async + $Spi_EBChnlCount1Async + $Spi_EBChnlCount2Async + $Spi_EBChnlCount3Async + $Spi_EBChnlCount4Async + $Spi_EBChnlCount5Async"!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(0)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
  [!VAR "Spi_MacTotalChnlCount"="$Spi_MacTotalChnlCount + $Spi_ChnlSyncQSPI0Count + $Spi_ChnlSyncQSPI1Count + $Spi_ChnlSyncQSPI2Count + $Spi_ChnlSyncQSPI3Count + $Spi_ChnlSyncQSPI4Count + $Spi_ChnlSyncQSPI5Count"!]
[!ENDIF!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(1)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
  [!VAR "Spi_MacTotalChnlCount"="($Spi_MacTotalChnlCount + $Spi_ChnlAsyncQSPI0Count + $Spi_ChnlAsyncQSPI1Count + $Spi_ChnlAsyncQSPI2Count + $Spi_ChnlAsyncQSPI3Count + $Spi_ChnlAsyncQSPI4Count + $Spi_ChnlAsyncQSPI5Count)"!]
[!ENDIF!]

[!IF "(SpiGeneral/SpiChannelBuffersAllowed = num:i(0)) or (SpiGeneral/SpiChannelBuffersAllowed = num:i(2))"!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI0 IB **************************/!]
    [!IF "$QSPI0CoreID = $CPUID"!]
          [!IF "$Spi_ChnlSyncQSPI0Count != num:i(0)"!]
[!CODE!][!//
  /* Synchronous Chnl[s] QSPI0 core[!"num:i($CPUID)"!]!*/
[!ENDCODE!]
        [!/* bit:or(bit:shl(SYNC/ASYNC,4),QSPIx)
             SYNC=0, ASYNC=0, QSPIx=index of Qspi(0,1,2,3,4 or 5) */!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlSyncQSPI0Count","Spi_OutChnlQSPIx" = "$Spi_ChnlSyncQSPI0","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


              [!IF "$Spi_ChnlAsyncQSPI0Count != num:i(0)"!]
            [!CODE!]

[!//
  /* Asynchronous Chnl[s] on QSPI0 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
            [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlAsyncQSPI0Count","Spi_OutChnlQSPIx" = "$Spi_ChnlAsyncQSPI0","Spi_OutHwUnit"="bit:or(bit:shl(1,4),0)"!][!//
              [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI1 IB **************************/!]
    [!IF "$QSPI1CoreID = $CPUID"!]
          [!IF "$Spi_ChnlSyncQSPI1Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Chnl[s] QSPI1 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!/* bit:or(bit:shl(SYNC/ASYNC,4),QSPIx)
             SYNC=0, ASYNC=0, QSPIx=index of Qspi(0,1,2,3,4 or 5) */!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlSyncQSPI1Count","Spi_OutChnlQSPIx" = "$Spi_ChnlSyncQSPI1","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]

          [!IF "$Spi_ChnlAsyncQSPI1Count != num:i(0)"!]
        [!CODE!]

[!//
    /* Asynchronous Chnl[s] on QSPI1 core[!"num:i($CPUID)"!]*/
        [!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlAsyncQSPI1Count","Spi_OutChnlQSPIx" = "$Spi_ChnlAsyncQSPI1","Spi_OutHwUnit"="bit:or(bit:shl(1,4),1)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI2 IB **************************/!]
    [!IF "$QSPI2CoreID = $CPUID"!]
          [!IF "$Spi_ChnlSyncQSPI2Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Chnl[s] QSPI2 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!/* bit:or(bit:shl(SYNC/ASYNC,4),QSPIx)
             SYNC=0, ASYNC=0, QSPIx=index of Qspi(0,1,2,3,4 or 5) */!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlSyncQSPI2Count","Spi_OutChnlQSPIx" = "$Spi_ChnlSyncQSPI2","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


          [!IF "$Spi_ChnlAsyncQSPI2Count != num:i(0)"!]
        [!CODE!]

[!//
    /* Asynchronous Chnl[s] on QSPI2 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlAsyncQSPI2Count","Spi_OutChnlQSPIx" = "$Spi_ChnlAsyncQSPI2","Spi_OutHwUnit"="bit:or(bit:shl(1,4),2)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI3 IB **************************/!]
    [!IF "$QSPI3CoreID = $CPUID"!]
          [!IF "$Spi_ChnlSyncQSPI3Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Chnl[s] QSPI3 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!/* bit:or(bit:shl(SYNC/ASYNC,4),QSPIx)
             SYNC=0, ASYNC=0, QSPIx=index of Qspi(0,1,2,3,4 or 5) */!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlSyncQSPI3Count","Spi_OutChnlQSPIx" = "$Spi_ChnlSyncQSPI3","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


          [!IF "$Spi_ChnlAsyncQSPI3Count != num:i(0)"!]
        [!CODE!]

[!//
    /* Asynchronous Chnl[s] on QSPI3 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlAsyncQSPI3Count","Spi_OutChnlQSPIx" = "$Spi_ChnlAsyncQSPI3","Spi_OutHwUnit"="bit:or(bit:shl(1,4),3)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI4 IB **************************/!]
    [!IF "$QSPI4CoreID = $CPUID"!]
          [!IF "$Spi_ChnlSyncQSPI4Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Chnl[s] QSPI4 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!/* bit:or(bit:shl(SYNC/ASYNC,4),QSPIx)
             SYNC=0, ASYNC=0, QSPIx=index of Qspi(0,1,2,3,4 or 5) */!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlSyncQSPI4Count","Spi_OutChnlQSPIx" = "$Spi_ChnlSyncQSPI4","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


          [!IF "$Spi_ChnlAsyncQSPI4Count != num:i(0)"!]
        [!CODE!]

[!//
    /* Asynchronous Chnl[s] on QSPI4 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlAsyncQSPI4Count","Spi_OutChnlQSPIx" = "$Spi_ChnlAsyncQSPI4","Spi_OutHwUnit"="bit:or(bit:shl(1,4),4)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI5 IB **************************/!]
    [!IF "$QSPI5CoreID = $CPUID"!]
          [!IF "$Spi_ChnlSyncQSPI5Count != num:i(0)"!]
        [!CODE!][!//
  /* Synchronous Chnl[s] QSPI5 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!/* bit:or(bit:shl(SYNC/ASYNC,4),QSPIx)
             SYNC=0, ASYNC=0, QSPIx=index of Qspi(0,1,2,3,4 or 5) */!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlSyncQSPI5Count","Spi_OutChnlQSPIx" = "$Spi_ChnlSyncQSPI5","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


          [!IF "$Spi_ChnlAsyncQSPI5Count != num:i(0)"!]
        [!CODE!]

[!//
    /* Asynchronous Chnl[s] on QSPI5 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_ChnlAsyncQSPI5Count","Spi_OutChnlQSPIx" = "$Spi_ChnlAsyncQSPI5","Spi_OutHwUnit"="bit:or(bit:shl(1,4),5)"!][!//
          [!ENDIF!]
    [!ENDIF!]

[!ENDIF!]



[!IF "(SpiGeneral/SpiChannelBuffersAllowed = num:i(1)) or (SpiGeneral/SpiChannelBuffersAllowed = num:i(2))"!]
[!/************* For Synchronous and ASYNCHRONOUS QSPI0 EB **************************/!]
    [!IF "$QSPI0CoreID = $CPUID"!]
         [!IF "$Spi_EBChnlCount0Sync != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI0 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount0Sync","Spi_OutChnlQSPIx" = "$Spi_EBChnl0Sync","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


         [!IF "$Spi_EBChnlCount0Async != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI0 core[!"num:i($CPUID)"!]*/
        [!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount0Async","Spi_OutChnlQSPIx" = "$Spi_EBChnl0Async","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI1 EB **************************/!]
    [!IF "$QSPI1CoreID = $CPUID"!]
         [!IF "$Spi_EBChnlCount1Sync != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI1 sync core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount1Sync","Spi_OutChnlQSPIx" = "$Spi_EBChnl1Sync","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


         [!IF "$Spi_EBChnlCount1Async != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI1 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount1Async","Spi_OutChnlQSPIx" = "$Spi_EBChnl1Async","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI2 EB **************************/!]
    [!IF "$QSPI2CoreID = $CPUID"!]
         [!IF "$Spi_EBChnlCount2Sync != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI2 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount2Sync","Spi_OutChnlQSPIx" = "$Spi_EBChnl2Sync","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


         [!IF "$Spi_EBChnlCount2Async != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI2 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount2Async","Spi_OutChnlQSPIx" = "$Spi_EBChnl2Async","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI3 EB **************************/!]
    [!IF "$QSPI3CoreID = $CPUID"!]
         [!IF "$Spi_EBChnlCount3Sync != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI3 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount3Sync","Spi_OutChnlQSPIx" = "$Spi_EBChnl3Sync","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


         [!IF "$Spi_EBChnlCount3Async != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI3 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount3Async","Spi_OutChnlQSPIx" = "$Spi_EBChnl3Async","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI4 EB **************************/!]
    [!IF "$QSPI4CoreID = $CPUID"!]
         [!IF "$Spi_EBChnlCount4Sync != num:i(0)"!]
        [!CODE!]

[!//
  /* EB Chnl[s] on QSPI4 core[!"num:i($CPUID)"!]*/
        [!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount4Sync","Spi_OutChnlQSPIx" = "$Spi_EBChnl4Sync","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


         [!IF "$Spi_EBChnlCount4Async != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI4 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount4Async","Spi_OutChnlQSPIx" = "$Spi_EBChnl4Async","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]
    [!ENDIF!]


[!/************* For Synchronous and ASYNCHRONOUS QSPI5 EB **************************/!]
    [!IF "$QSPI5CoreID = $CPUID"!]
         [!IF "$Spi_EBChnlCount5Sync != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI5 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount5Sync","Spi_OutChnlQSPIx" = "$Spi_EBChnl5Sync","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]


         [!IF "$Spi_EBChnlCount5Async != num:i(0)"!]
        [!CODE!]

[!//
    /* EB Chnl[s] on QSPI5 core[!"num:i($CPUID)"!]*/
[!ENDCODE!]
        [!CALL "Spi_CGGenerateChnlConfigSyncOrAsync","Spi_OutChnlQSPIxCount" = "$Spi_EBChnlCount5Async","Spi_OutChnlQSPIx" = "$Spi_EBChnl5Async","Spi_OutHwUnit"="bit:or(bit:shl(0,4),0)"!][!//
          [!ENDIF!]
    [!ENDIF!]

[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={9590C8B4-FF2D-471e-B4A5-EC235701891C}][/cover]
MACRO: Spi_CGCalculateMaxSequence
Macro to generate Max sequence in QspiHw configuration
******************************************************************************/!]
[!MACRO "Spi_CGCalculateMaxSequence","Spi_OutQspiIndex" = ""!][!//!][!//
[!NOCODE!][!//

[!// for input QSPIx hardware unit maximum number of sequence initialize to 0
[!VAR "Spi_MaxSeqCount"="num:i(0)"!]
[!LOOP "SpiDriver/SpiSequence/*"!]

    [!// check sequence belongs to input QSPIx
    [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = $Spi_OutQspiIndex"!]
        [!// increment count
        [!VAR "Spi_MaxSeqCount"="$Spi_MaxSeqCount + num:i(1)"!]
    [!ENDIF!]

[!ENDLOOP!]

[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGGenerateSequence_IDPhysical
Macro to generate Symbolic names for Sequences and indexing as per position in each core
******************************************************************************/!]
[!MACRO "Spi_CGGenerateSequence_IDPhysical"!][!//
[!NOCODE!][!//

[!VAR "Spi_SqCounterIndex" = "num:i(count(SpiDriver/SpiSequence/*))"!][!VAR "Spi_SqCounterIndex" = "num:i(count(SpiDriver/SpiSequence/*))"!]
[!VAR "Spi_SequencePhysicalIndex" = "0"!]
[!FOR "Spi_SqCounterIndex1" = "0" TO "$Spi_SqCounterIndex - 1"!]
[!VAR "Spi_SequencePhysicalIndex" = "concat($Spi_SequencePhysicalIndex,',',$Spi_SqCounterIndex1 + 300)"!]
[!ENDFOR!]

[!// Sequence Id type - physical ID type (1), sequential ID type (0)
[!VAR "Spi_SequenceIDType" = "num:i(1)"!]

[!// first all Sync and then Async sequence will be genrated for QSPI0 to QSPI5 sequencially for all instance belonging to same core in order of core 0 to core 5
[!VAR "CPU_ID" = "num:i(0)"!]
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!]
    [!VAR "Spi_SequenceID"="num:i(0)"!]
    [!//checking if QSPI0 is have same index for which index is being generated for
    [!IF "$QSPI0CoreID = $CPU_ID"!]
    [!// if there are sync sequence for QSPI0
         [!IF "$Spi_SeqSyncQSPI0Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqSyncQSPI0Count","SpiOutQSPIxSeq" = "$Spi_SeqSyncQSPI0","Spi_OutSequenceID" = "$Spi_SequenceID"!]
         [!ENDIF!]
    [!// if there are Async sequence for QSPI0
          [!IF "$Spi_SeqAsyncQSPI0Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqAsyncQSPI0Count","SpiOutQSPIxSeq" = "$Spi_SeqAsyncQSPI0","Spi_OutSequenceID" = "$Spi_SequenceID"!]
          [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI1CoreID = $CPU_ID"!]
          [!IF "$Spi_SeqSyncQSPI1Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqSyncQSPI1Count","SpiOutQSPIxSeq" = "$Spi_SeqSyncQSPI1","Spi_OutSequenceID" = "$Spi_SequenceID"!]
          [!ENDIF!]

        [!IF "$Spi_SeqAsyncQSPI1Count != num:i(0)"!]
         [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqAsyncQSPI1Count","SpiOutQSPIxSeq" = "$Spi_SeqAsyncQSPI1","Spi_OutSequenceID" = "$Spi_SequenceID"!]
        [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI2CoreID = $CPU_ID"!]
          [!IF "$Spi_SeqSyncQSPI2Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqSyncQSPI2Count","SpiOutQSPIxSeq" = "$Spi_SeqSyncQSPI2","Spi_OutSequenceID" = "$Spi_SequenceID"!]
          [!ENDIF!]

    [!IF "$Spi_SeqAsyncQSPI2Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqAsyncQSPI2Count","SpiOutQSPIxSeq" = "$Spi_SeqAsyncQSPI2","Spi_OutSequenceID" = "$Spi_SequenceID"!]
        [!ENDIF!]
    [!ENDIF!]


    [!IF "$QSPI3CoreID = $CPU_ID"!]
          [!IF "$Spi_SeqSyncQSPI3Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqSyncQSPI3Count","SpiOutQSPIxSeq" = "$Spi_SeqSyncQSPI3","Spi_OutSequenceID" = "$Spi_SequenceID"!]
          [!ENDIF!]

    [!IF "$Spi_SeqAsyncQSPI3Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqAsyncQSPI3Count","SpiOutQSPIxSeq" = "$Spi_SeqAsyncQSPI3","Spi_OutSequenceID" = "$Spi_SequenceID"!]
        [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI4CoreID = $CPU_ID"!]
          [!IF "$Spi_SeqSyncQSPI4Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqSyncQSPI4Count","SpiOutQSPIxSeq" = "$Spi_SeqSyncQSPI4","Spi_OutSequenceID" = "$Spi_SequenceID"!]
          [!ENDIF!]

    [!IF "$Spi_SeqAsyncQSPI4Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqAsyncQSPI4Count","SpiOutQSPIxSeq" = "$Spi_SeqAsyncQSPI4","Spi_OutSequenceID" = "$Spi_SequenceID"!]
        [!ENDIF!]
    [!ENDIF!]
    [!IF "$QSPI5CoreID = $CPU_ID"!]
          [!IF "$Spi_SeqSyncQSPI5Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqSyncQSPI5Count","SpiOutQSPIxSeq" = "$Spi_SeqSyncQSPI5","Spi_OutSequenceID" = "$Spi_SequenceID"!]
          [!ENDIF!]


    [!IF "$Spi_SeqAsyncQSPI5Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "$Spi_SeqAsyncQSPI5Count","SpiOutQSPIxSeq" = "$Spi_SeqAsyncQSPI5","Spi_OutSequenceID" = "$Spi_SequenceID"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDFOR!]

[!//


[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGGenerateJob_IDPhysical
Macro to generate Symbolic names for Jobs and indexing as per position in each core
******************************************************************************/!]
[!MACRO "Spi_CGGenerateJob_IDPhysical"!][!//
[!NOCODE!][!//


[!//  - Generate ID per core and kernel

[!VAR "Spi_JobCounterIndex" = "num:i(count(SpiDriver/SpiJob/*))"!]
[!VAR "Spi_JobPhysicalIndex" = "0"!]
[!FOR "Spi_JobCounterIndex1" = "0" TO "$Spi_JobCounterIndex - 1"!]
[!VAR "Spi_JobPhysicalIndex" = "concat($Spi_JobPhysicalIndex,',',$Spi_JobCounterIndex1 + 300)"!]
[!ENDFOR!]

[!// job Id type physical ID (1) sequential (0)
[!VAR "SpiJobIDType" = "num:i(1)"!]
[!// first all the sync and the async job belonging to QSPI 0 to 1 respectively being generated if The QSPI instance belong to core 0 to core 5 respectively
[!VAR "CPU_ID" = "num:i(0)"!]
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!]
    [!VAR "Spi_JobID"="num:i(0)"!]
[!// checking if QSPI0 belongs to the core for which job if is being assigned
    [!IF "$QSPI0CoreID = $CPU_ID"!]
    [!// checking if Sync job is present for the QSPI
          [!IF "$Spi_JobSyncQSPI0Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobSyncQSPI0Count","SpiOutQSPIxJob" = "$Spi_JobSyncQSPI0","Spi_OutJobID" = "$Spi_JobID"!]
          [!ENDIF!]


        [!IF "$Spi_JobAsyncQSPI0Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobAsyncQSPI0Count","SpiOutQSPIxJob" = "$Spi_JobAsyncQSPI0","Spi_OutJobID" = "$Spi_JobID"!]
          [!ENDIF!]

    [!ENDIF!]

    [!IF "$QSPI1CoreID = $CPU_ID"!]
          [!IF "$Spi_JobSyncQSPI1Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobSyncQSPI1Count","SpiOutQSPIxJob" = "$Spi_JobSyncQSPI1","Spi_OutJobID" = "$Spi_JobID"!]
          [!ENDIF!]


         [!IF "$Spi_JobAsyncQSPI1Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobAsyncQSPI1Count","SpiOutQSPIxJob" = "$Spi_JobAsyncQSPI1","Spi_OutJobID" = "$Spi_JobID"!]
          [!ENDIF!]

    [!ENDIF!]

    [!IF "$QSPI2CoreID = $CPU_ID"!]
          [!IF "$Spi_JobSyncQSPI2Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobSyncQSPI2Count","SpiOutQSPIxJob" = "$Spi_JobSyncQSPI2","Spi_OutJobID" = "$Spi_JobID"!]
        [!ENDIF!]


        [!IF "$Spi_JobAsyncQSPI2Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobAsyncQSPI2Count","SpiOutQSPIxJob" = "$Spi_JobAsyncQSPI2","Spi_OutJobID" = "$Spi_JobID"!]
        [!ENDIF!]

    [!ENDIF!]

    [!IF "$QSPI3CoreID = $CPU_ID"!]
          [!IF "$Spi_JobSyncQSPI3Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobSyncQSPI3Count","SpiOutQSPIxJob" = "$Spi_JobSyncQSPI3","Spi_OutJobID" = "$Spi_JobID"!]
        [!ENDIF!]


        [!IF "$Spi_JobAsyncQSPI3Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobAsyncQSPI3Count","SpiOutQSPIxJob" = "$Spi_JobAsyncQSPI3","Spi_OutJobID" = "$Spi_JobID"!]
        [!ENDIF!]

    [!ENDIF!]

    [!IF "$QSPI4CoreID = $CPU_ID"!]
          [!IF "$Spi_JobSyncQSPI4Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobSyncQSPI4Count","SpiOutQSPIxJob" = "$Spi_JobSyncQSPI4","Spi_OutJobID" = "$Spi_JobID"!]
          [!ENDIF!]


        [!IF "$Spi_JobAsyncQSPI4Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobAsyncQSPI4Count","SpiOutQSPIxJob" = "$Spi_JobAsyncQSPI4","Spi_OutJobID" = "$Spi_JobID"!]
        [!ENDIF!]

    [!ENDIF!]

    [!IF "$QSPI5CoreID = $CPU_ID"!]
          [!IF "$Spi_JobSyncQSPI5Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobSyncQSPI5Count","SpiOutQSPIxJob" = "$Spi_JobSyncQSPI5","Spi_OutJobID" = "$Spi_JobID"!]
          [!ENDIF!]


        [!IF "$Spi_JobAsyncQSPI5Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "$Spi_JobAsyncQSPI5Count","SpiOutQSPIxJob" = "$Spi_JobAsyncQSPI5","Spi_OutJobID" = "$Spi_JobID"!]
        [!ENDIF!]

    [!ENDIF!]

[!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGGenerateChannel_IDPhysical
Macro to generate Symbolic names for Channels and indexing as per position in each core
******************************************************************************/!]
[!MACRO "Spi_CGGenerateChannel_IDPhysical"!][!//
[!NOCODE!][!//

[!VAR "Spi_ChCounterIndex" = "num:i(count(SpiDriver/SpiChannel/*))"!]
[!VAR "Spi_ChannelPhysicalIndex" = "0"!]
[!FOR "Spi_ChCounterIndex1" = "0" TO "$Spi_ChCounterIndex - 1"!]
[!VAR "Spi_ChannelPhysicalIndex" = "concat($Spi_ChannelPhysicalIndex,',',$Spi_ChCounterIndex1 + 300)"!]
[!ENDFOR!]

[!// physical ID (1) or sequential ID (0) type
[!VAR "Spi_ChannelIDType"="num:i(1)"!]
[!// first all the IB sync and async with respect of QSPI 0 to 5 will be assigned ID then all the EB sync and async with respect of QSPI 0 to 5 if it belongs to core for which the ID is being genrated core 0 to core 5
[!VAR "CPU_ID" = "num:i(0)"!]
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!]
    [!VAR "Spi_ChannelID"="num:i(0)"!]
   [!IF "SpiGeneral/SpiChannelBuffersAllowed != num:i(1)"!]
    [!IF "$QSPI0CoreID = $CPU_ID"!]
          [!IF "$Spi_ChnlSyncQSPI0Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlSyncQSPI0Count","SpiOutQSPIxChannel" = "$Spi_ChnlSyncQSPI0","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]

          [!IF "$Spi_ChnlAsyncQSPI0Count != num:i(0)"!]

            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlAsyncQSPI0Count","SpiOutQSPIxChannel" = "$Spi_ChnlAsyncQSPI0","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI1CoreID = $CPU_ID"!]
          [!IF "$Spi_ChnlSyncQSPI1Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlSyncQSPI1Count","SpiOutQSPIxChannel" = "$Spi_ChnlSyncQSPI1","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]


         [!IF "$Spi_ChnlAsyncQSPI1Count != num:i(0)"!]

            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlAsyncQSPI1Count","SpiOutQSPIxChannel" = "$Spi_ChnlAsyncQSPI1","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI2CoreID = $CPU_ID"!]
          [!IF "$Spi_ChnlSyncQSPI2Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlSyncQSPI2Count","SpiOutQSPIxChannel" = "$Spi_ChnlSyncQSPI2","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]


        [!IF "$Spi_ChnlAsyncQSPI2Count != num:i(0)"!]

            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlAsyncQSPI2Count","SpiOutQSPIxChannel" = "$Spi_ChnlAsyncQSPI2","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI3CoreID = $CPU_ID"!]
          [!IF "$Spi_ChnlSyncQSPI3Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlSyncQSPI3Count","SpiOutQSPIxChannel" = "$Spi_ChnlSyncQSPI3","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]


        [!IF "$Spi_ChnlAsyncQSPI3Count != num:i(0)"!]

            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlAsyncQSPI3Count","SpiOutQSPIxChannel" = "$Spi_ChnlAsyncQSPI3","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI4CoreID = $CPU_ID"!]
          [!IF "$Spi_ChnlSyncQSPI4Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlSyncQSPI4Count","SpiOutQSPIxChannel" = "$Spi_ChnlSyncQSPI4","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]


        [!IF "$Spi_ChnlAsyncQSPI4Count != num:i(0)"!]

            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlAsyncQSPI4Count","SpiOutQSPIxChannel" = "$Spi_ChnlAsyncQSPI4","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]
    [!ENDIF!]

    [!IF "$QSPI5CoreID = $CPU_ID"!]
          [!IF "$Spi_ChnlSyncQSPI5Count != num:i(0)"!]
            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlSyncQSPI5Count","SpiOutQSPIxChannel" = "$Spi_ChnlSyncQSPI5","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]


        [!IF "$Spi_ChnlAsyncQSPI5Count != num:i(0)"!]

            [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_ChnlAsyncQSPI5Count","SpiOutQSPIxChannel" = "$Spi_ChnlAsyncQSPI5","Spi_OutChannelID" = "$Spi_ChannelID"!]
          [!ENDIF!]
    [!ENDIF!]
   [!ENDIF!]

[!// EB channel
   [!IF "SpiGeneral/SpiChannelBuffersAllowed != num:i(0)"!]
    [!IF "$QSPI0CoreID = $CPU_ID"!]
              [!IF "$Spi_EBChnlCount0Sync != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount0Sync","SpiOutQSPIxChannel" = "$Spi_EBChnl0Sync","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]

              [!IF "$Spi_EBChnlCount0Async != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount0Async","SpiOutQSPIxChannel" = "$Spi_EBChnl0Async","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]
        [!ENDIF!]

    [!IF "$QSPI1CoreID = $CPU_ID"!]
              [!IF "$Spi_EBChnlCount1Sync != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount1Sync","SpiOutQSPIxChannel" = "$Spi_EBChnl1Sync","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]

              [!IF "$Spi_EBChnlCount1Async != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount1Async","SpiOutQSPIxChannel" = "$Spi_EBChnl1Async","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]
        [!ENDIF!]

    [!IF "$QSPI2CoreID = $CPU_ID"!]
              [!IF "$Spi_EBChnlCount2Sync != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount2Sync","SpiOutQSPIxChannel" = "$Spi_EBChnl2Sync","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]



              [!IF "$Spi_EBChnlCount2Async != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount2Async","SpiOutQSPIxChannel" = "$Spi_EBChnl2Async","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]
        [!ENDIF!]

    [!IF "$QSPI3CoreID = $CPU_ID"!]
              [!IF "$Spi_EBChnlCount3Sync != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount3Sync","SpiOutQSPIxChannel" = "$Spi_EBChnl3Sync","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]



              [!IF "$Spi_EBChnlCount3Async != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount3Async","SpiOutQSPIxChannel" = "$Spi_EBChnl3Async","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]
        [!ENDIF!]

    [!IF "$QSPI4CoreID = $CPU_ID"!]
              [!IF "$Spi_EBChnlCount4Sync != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount4Sync","SpiOutQSPIxChannel" = "$Spi_EBChnl4Sync","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]

              [!IF "$Spi_EBChnlCount4Async != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount4Async","SpiOutQSPIxChannel" = "$Spi_EBChnl4Async","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]
        [!ENDIF!]

            [!IF "$QSPI5CoreID = $CPU_ID"!]
              [!IF "$Spi_EBChnlCount5Sync != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount5Sync","SpiOutQSPIxChannel" = "$Spi_EBChnl5Sync","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]



              [!IF "$Spi_EBChnlCount5Async != num:i(0)"!]

                [!CALL "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "$Spi_EBChnlCount5Async","SpiOutQSPIxChannel" = "$Spi_EBChnl5Async","Spi_OutChannelID" = "$Spi_ChannelID"!]
              [!ENDIF!]
        [!ENDIF!]
       [!ENDIF!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGGenerateRootConfig
To generarte root configuration
******************************************************************************/!]
[!MACRO "Spi_CGGenerateRootConfig"!][!//
[!NOCODE!][!//







[!VAR "CPUINDEX" = "num:i(0)"!]
[!FOR "CPUINDEX" = "0" TO "num:i($Spi_MaxCore)"!][!//
    [!// If any of the QSPIx hw unit is configured for core from core0 to core5
    [!IF "($QSPI0CoreID = $CPUINDEX) or ($QSPI1CoreID = $CPUINDEX) or ($QSPI2CoreID = $CPUINDEX) or ($QSPI3CoreID = $CPUINDEX) or ($QSPI4CoreID = $CPUINDEX) or ($QSPI5CoreID = $CPUINDEX)"!]
            [!CODE!]
  [!IF "$VariantsConfigured = num:i(1)"!][!//
  &Spi_Config_Core[!"num:i($CPUINDEX)"!]_[!"$PredefinedVarName"!][!//
  [!ELSE!][!//
  &Spi_Config_Core[!"num:i($CPUINDEX)"!][!//
  [!ENDIF!][!//
[!IF "$CPUINDEX != num:i($Spi_MaxCore)"!][!//
[!CODE!][!//
[!//
,[!//
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDCODE!]
    [!ELSE!]
            [!CODE!]
    NULL_PTR[!//
[!IF "$CPUINDEX != num:i($Spi_MaxCore)"!][!//
[!CODE!][!//
,[!//
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDCODE!]

    [!ENDIF!]
[!ENDFOR!]
[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGStoreCoreConfig
Macro to check which cores are assigned atleast one kernel
******************************************************************************/!]
[!MACRO "Spi_CGStoreCoreConfig"!][!//
[!NOCODE!][!//




[!// For all core starting from core0 to core5, list represent if they are configured for any QSPIx then 1 else 0
[!VAR "Core_config" = "''"!]
[!VAR "CPUINDEX" = "num:i(0)"!]

[!// for all Core ID
[!FOR "CPUINDEX" = "0" TO "num:i($Spi_MaxCore)"!][!//

    [!// any QSPIx is configured for a core insert 1 in the respective position else 0
    [!IF "($QSPI0CoreID = $CPUINDEX) or ($QSPI1CoreID = $CPUINDEX) or ($QSPI2CoreID = $CPUINDEX) or ($QSPI3CoreID = $CPUINDEX) or ($QSPI4CoreID = $CPUINDEX) or ($QSPI5CoreID = $CPUINDEX)"!]
        [!VAR "Core_config"="concat($Core_config,num:i(1),',')"!]
    [!ELSE!]
        [!VAR "Core_config"="concat($Core_config,num:i(0),',')"!]
    [!ENDIF!]

    [!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGStoreKernelCoreConfig
Macro to know core ID for each QSPI kernel
******************************************************************************/!]
[!MACRO "Spi_CGStoreKernelCoreConfig"!][!//
[!NOCODE!][!//




[!VAR "QSPICore_config" = "''"!]

        [!VAR "QSPICore_config"="concat($QSPICore_config,$QSPI0CoreID,',')"!]

        [!VAR "QSPICore_config"="concat($QSPICore_config,$QSPI1CoreID,',')"!]

        [!VAR "QSPICore_config"="concat($QSPICore_config,$QSPI2CoreID,',')"!]

        [!VAR "QSPICore_config"="concat($QSPICore_config,$QSPI3CoreID,',')"!]

        [!VAR "QSPICore_config"="concat($QSPICore_config,$QSPI4CoreID,',')"!]

        [!VAR "QSPICore_config"="concat($QSPICore_config,$QSPI5CoreID,',')"!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY :  [cover parentID={3D7479E8-5AC3-45d6-A145-1E1476837A8C}][/cover]
MACRO: Spi_CGCalculateTotalSequencePerCore
Macro to calculate and generate coude for count of total number of sequence per core.
******************************************************************************/!]
[!MACRO "Spi_CGCalculateTotalSequencePerCore"!][!//
[!NOCODE!][!//

[!CALL "Spi_CGStoreKernelCoreConfig"!]

    [!FOR "CPUID" = "0" TO "num:i($Spi_MaxCore)"!]

    [!VAR "TotalSequence"="num:i(0)"!]

        [!// If for a QSPIx current core ID is configured
        [!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $CPUID"!]
            [!// for all sequence belongs to QSPI0 increment count
            [!LOOP "SpiDriver/SpiSequence/*"!]
                [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = 'QSPI0'"!]
                    [!VAR "TotalSequence"="$TotalSequence + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $CPUID"!]
            [!// for all sequence belongs to QSPI1 increment count
            [!LOOP "SpiDriver/SpiSequence/*"!]
                [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = 'QSPI1'"!]
                    [!VAR "TotalSequence"="$TotalSequence + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $CPUID"!]
            [!// for all sequence belongs to QSPI2 increment count
            [!LOOP "SpiDriver/SpiSequence/*"!]
                [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = 'QSPI2'"!]
                    [!VAR "TotalSequence"="$TotalSequence + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $CPUID"!]
            [!// for all sequence belongs to QSPI3 increment count
            [!LOOP "SpiDriver/SpiSequence/*"!]
                [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = 'QSPI3'"!]
                    [!VAR "TotalSequence"="$TotalSequence + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $CPUID"!]
            [!// for all sequence belongs to QSPI4 increment count
            [!LOOP "SpiDriver/SpiSequence/*"!]
                [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = 'QSPI4'"!]
                    [!VAR "TotalSequence"="$TotalSequence + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $CPUID"!]
            [!// for all sequence belongs to QSPI5 increment count
            [!LOOP "SpiDriver/SpiSequence/*"!]
                [!IF "node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit = 'QSPI5'"!]
                    [!VAR "TotalSequence"="$TotalSequence + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!CODE!]
#define SPI_SEQUENCE_COUNT_CORE[!"num:i($CPUID)"!]      [!"num:i($TotalSequence)"!]U
        [!ENDCODE!]
    [!ENDFOR!]
[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY :  [cover parentID={0C00C609-AB37-4e67-B59B-C42CA2398BB9}][/cover]
MACRO: Spi_CGCalculateTotalJobPerCore
Macro to calculate and generate code for count of total number of job per core.
******************************************************************************/!]
[!MACRO "Spi_CGCalculateTotalJobPerCore"!][!//
[!NOCODE!][!//

[!CALL "Spi_CGStoreKernelCoreConfig"!]

    [!FOR "CPUID" = "0" TO "num:i($Spi_MaxCore)"!]

    [!VAR "TotalJob"="num:i(0)"!]

        [!// If for a QSPIx current core ID is configured
        [!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $CPUID"!]
            [!// for all job belongs to QSPI0 increment count
            [!LOOP "SpiDriver/SpiJob/*"!]
                [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI0'"!]
                    [!VAR "TotalJob"="$TotalJob + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $CPUID"!]
            [!LOOP "SpiDriver/SpiJob/*"!]
                [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI1'"!]
                    [!VAR "TotalJob"="$TotalJob + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $CPUID"!]
            [!LOOP "SpiDriver/SpiJob/*"!]
                [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI2'"!]
                    [!VAR "TotalJob"="$TotalJob + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $CPUID"!]
            [!LOOP "SpiDriver/SpiJob/*"!]
                [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI3'"!]
                    [!VAR "TotalJob"="$TotalJob + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $CPUID"!]
            [!LOOP "SpiDriver/SpiJob/*"!]
                [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI4'"!]
                    [!VAR "TotalJob"="$TotalJob + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $CPUID"!]
            [!LOOP "SpiDriver/SpiJob/*"!]
                [!IF "node:ref(./SpiDeviceAssignment)/SpiHwUnit = 'QSPI5'"!]
                    [!VAR "TotalJob"="$TotalJob + num:i(1)"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]

        [!CODE!]
#define SPI_JOB_COUNT_CORE[!"num:i($CPUID)"!]       [!"num:i($TotalJob)"!]U
        [!ENDCODE!]
    [!ENDFOR!]
[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGGenerateQspiMapConfigVal
Macro to generate QSPIx hardware map
******************************************************************************/!]
[!MACRO "Spi_CGGenerateQspiMapConfigVal","CPU_ID"=""!][!//
[!NOCODE!][!//

[!CALL "Spi_CGIsQSPIzUsed"!][!//
[!CALL "Spi_CGStoreKernelCoreConfig"!]

    [!// If input core ID is configured for any one of the QSPIx
    [!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!]
    [!VAR "Spi_HwMap" = "num:i(0)"!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]

        [!// If QSPI5 is configured for the input core ID
        [!IF "text:split($QSPICore_config,',')[position() = 6] = $CPU_ID"!]

                [!// if hardware type is synchronous set LSB (001)
                [!IF "num:i($Spi_MacQspi5HwType) = num:i(0)"!]
                    [!VAR "Spi_HwMap1" = "num:i(1)"!]
                [!// if hardware type is asynchronous set 2nd bit (010)
                [!ELSE!]
                    [!VAR "Spi_HwMap1" = "num:i(2)"!]
                [!ENDIF!]

        [!ENDIF!]

        [!// Shift bit to left by 3 and or with 0 for next QSPI map
        [!VAR "Spi_HwMap"="bit:or( $Spi_HwMap, $Spi_HwMap1 )"!]
        [!CODE!]
  /*
  (000 QSPI not configured for core[!"num:i($CPU_ID)"!])
  (001 QSPI configured as Sync for core[!"num:i($CPU_ID)"!])
  (010 QSPI configured as Async for core[!"num:i($CPU_ID)"!])

  QSPI5 - [!"num:i($Spi_HwMap1)"!]
[!ENDCODE!]
        [!VAR "Spi_HwMap"="bit:shl( $Spi_HwMap, 3 )"!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]

        [!IF "text:split($QSPICore_config,',')[position() = 5] = $CPU_ID"!]
                [!IF "num:i($Spi_MacQspi4HwType) = num:i(0)"!]
                    [!VAR "Spi_HwMap1" = "num:i(1)"!]
                [!ELSE!]
                    [!VAR "Spi_HwMap1" = "num:i(2)"!]
                [!ENDIF!]
        [!ENDIF!]

        [!VAR "Spi_HwMap"="bit:or( $Spi_HwMap, $Spi_HwMap1 )"!]
        [!CODE!]
  QSPI4 - [!"num:i($Spi_HwMap1)"!]
[!ENDCODE!]
        [!VAR "Spi_HwMap"="bit:shl( $Spi_HwMap, 3 )"!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]
=

        [!IF "text:split($QSPICore_config,',')[position() = 4] = $CPU_ID"!]
                [!IF "num:i($Spi_MacQspi3HwType) = num:i(0)"!]
                    [!VAR "Spi_HwMap1" = "num:i(1)"!]
                [!ELSE!]
                    [!VAR "Spi_HwMap1" = "num:i(2)"!]
                [!ENDIF!]
        [!ENDIF!]

        [!VAR "Spi_HwMap"="bit:or( $Spi_HwMap, $Spi_HwMap1 )"!]
        [!CODE!]
  QSPI3 - [!"num:i($Spi_HwMap1)"!]
[!ENDCODE!]
        [!VAR "Spi_HwMap"="bit:shl( $Spi_HwMap, 3 )"!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]
=

        [!IF "text:split($QSPICore_config,',')[position() = 3] = $CPU_ID"!]
                [!IF "num:i($Spi_MacQspi2HwType) = num:i(0)"!]
                    [!VAR "Spi_HwMap1" = "num:i(1)"!]
                [!ELSE!]
                    [!VAR "Spi_HwMap1" = "num:i(2)"!]
                [!ENDIF!]
        [!ENDIF!]

        [!VAR "Spi_HwMap"="bit:or( $Spi_HwMap, $Spi_HwMap1 )"!]
        [!CODE!]
  QSPI2 - [!"num:i($Spi_HwMap1)"!]
  [!ENDCODE!]
        [!VAR "Spi_HwMap"="bit:shl( $Spi_HwMap, 3 )"!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]


        [!IF "text:split($QSPICore_config,',')[position() = 2] = $CPU_ID"!]
                [!IF "num:i($Spi_MacQspi1HwType) = num:i(0)"!]
                    [!VAR "Spi_HwMap1" = "num:i(1)"!]
                [!ELSE!]
                    [!VAR "Spi_HwMap1" = "num:i(2)"!]
                [!ENDIF!]
        [!ENDIF!]

        [!VAR "Spi_HwMap"="bit:or( $Spi_HwMap, $Spi_HwMap1 )"!]
        [!CODE!]
  QSPI1 - [!"num:i($Spi_HwMap1)"!]
[!ENDCODE!]
        [!VAR "Spi_HwMap"="bit:shl( $Spi_HwMap, 3 )"!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]

        [!IF "text:split($QSPICore_config,',')[position() = 1] = $CPU_ID"!]
                [!IF "num:i($Spi_MacQspi0HwType) = num:i(0)"!]
                    [!VAR "Spi_HwMap1" = "num:i(1)"!]
                [!ELSE!]
                    [!VAR "Spi_HwMap1" = "num:i(2)"!]
                [!ENDIF!]
        [!ENDIF!]

        [!VAR "Spi_HwMap"="bit:or( $Spi_HwMap, $Spi_HwMap1 )"!]
        [!CODE!]
  QSPI0 - [!"num:i($Spi_HwMap1)"!]
  */
[!ENDCODE!]
        [!VAR "Spi_HwMap1" = "num:i(0)"!]

[!CODE!]
  [!"num:inttohex( $Spi_HwMap, 5 )"!]U[!//
[!ENDCODE!]
    [!ENDIF!]


[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={DB4976B8-8660-451a-B637-CFBFDC88D0A9}][/cover]
MACRO: Spi_CGGenerateSequenceIndexMapping
Macro to generate SequenceLookupIndex
******************************************************************************/!]
[!MACRO "Spi_CGGenerateSequenceIndexMapping"!][!//
[!NOCODE!][!//
[!CALL "Spi_CGStoreSequence_ID"!]
[!CALL "Spi_CGGenerateSequence_IDPhysical"!]

[!VAR "Spi_SeqCount" = "num:i(count(SpiDriver/SpiSequence/*))"!]
[!CODE!]
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const uint8 SequenceLookupIndex_[!"$PredefinedVarName"!][[!"num:i(count(SpiDriver/SpiSequence/*))"!]] =
[!ELSE!][!//
static const uint8 SequenceLookupIndex[[!"num:i(count(SpiDriver/SpiSequence/*))"!]] =
[!ENDIF!][!//
{
[!//
[!ENDCODE!]

[!FOR "Spi_SeqIdCounter" = "1" TO "$Spi_SeqCount"!]
[!CODE!]
    /* Physical index value for Sequence [!"node:name(SpiDriver/SpiSequence/*[SpiSequenceId = $Spi_SeqIdCounter - 1])"!] Sequence ID [!"num:i($Spi_SeqIdCounter -1)"!] */
    [!"text:split($Spi_SequencePhysicalIndex,',')[position() = $Spi_SeqIdCounter + 1]"!]U[!//
[!IF "$Spi_SeqIdCounter < $Spi_SeqCount"!][!//
,
[!ENDIF!][!//
[!ENDCODE!]
[!ENDFOR!]

[!CODE!][!//

};
[!ENDCODE!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={65BB8E7C-58CE-411f-87DC-82D5DDD94125}][/cover]
MACRO: Spi_CGGenerateJobIndexMapping
Macro to generate JobLookupIndex
******************************************************************************/!]
[!MACRO "Spi_CGGenerateJobIndexMapping"!][!//
[!NOCODE!][!//
[!CALL "Spi_CGStoreJob_ID"!]
[!CALL "Spi_CGGenerateJob_IDPhysical"!]

[!VAR "Spi_JobCount" = "num:i(count(SpiDriver/SpiJob/*))"!]
[!VAR "Spi_count" = "num:i(0)"!]
[!CODE!]
/* MISRA2012_RULE_8_3_JUSTIFICATION: Agreed violation */
/* MISRA2012_RULE_8_9_JUSTIFICATION: Agreed violation */
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const uint16 JobLookupIndex_[!"$PredefinedVarName"!][[!"num:i(count(SpiDriver/SpiJob/*))"!]] =
[!ELSE!][!//
static const uint16 JobLookupIndex[[!"num:i(count(SpiDriver/SpiJob/*))"!]] =
[!ENDIF!][!//
{
[!//
[!ENDCODE!]

[!FOR "Spi_JobIdCounter" = "1" TO "$Spi_JobCount"!]
[!CODE!]
    /* Physical index value for Job [!"node:name(SpiDriver/SpiJob/*[SpiJobId = $Spi_JobIdCounter - 1])"!] Job ID [!"num:i($Spi_JobIdCounter -1)"!] */
    [!"text:split($Spi_JobPhysicalIndex,',')[position() = $Spi_JobIdCounter + 1]"!]U[!//
[!IF "$Spi_JobIdCounter < $Spi_JobCount"!][!//
,
[!ENDIF!][!//
[!ENDCODE!]
[!ENDFOR!]

[!CODE!][!//

};
[!ENDCODE!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
TRACEABILITY : [cover parentID={779814B0-12B1-499a-9B4F-219446E3CFDC}][/cover]
MACRO: Spi_CGGenerateChannelIndexMapping
Macro to generate ChannelLookupIndex
******************************************************************************/!]
[!MACRO "Spi_CGGenerateChannelIndexMapping"!][!//
[!NOCODE!][!//
[!CALL "Spi_CGStoreChannel_ID"!]
[!CALL "Spi_CGGenerateChannel_IDPhysical"!]

[!VAR "Spi_ChannelCount" = "num:i(count(SpiDriver/SpiChannel/*))"!]
[!VAR "Spi_count" = "num:i(0)"!]
[!//
[!CODE!]
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const uint8 ChannelLookupIndex_[!"$PredefinedVarName"!][[!"num:i(count(SpiDriver/SpiChannel/*))"!]] =
[!ELSE!][!//
static const uint8 ChannelLookupIndex[[!"num:i(count(SpiDriver/SpiChannel/*))"!]] =
[!ENDIF!][!//
{
[!//
[!ENDCODE!]

[!FOR "Spi_ChannelIdCounter" = "1" TO "$Spi_ChannelCount"!]
[!CODE!]
    /* Physical index value for channel [!"node:name(SpiDriver/SpiChannel/*[SpiChannelId = $Spi_ChannelIdCounter - 1])"!] channel ID [!"num:i($Spi_ChannelIdCounter -1)"!] */
    [!"text:split($Spi_ChannelPhysicalIndex,',')[position() = $Spi_ChannelIdCounter + 1]"!]U[!//
[!IF "$Spi_ChannelIdCounter < $Spi_ChannelCount"!][!//
,
[!ENDIF!][!//
[!ENDCODE!]
[!ENDFOR!]

[!CODE!][!//

};
[!ENDCODE!]

[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGGetCore
Macro to know core ID for each QSPI kernel
******************************************************************************/!]
[!MACRO "Spi_CGGetCore"!][!//
[!NOCODE!][!//
  [!VAR "QSPI0CoreID" = "num:i(255)"!]
  [!VAR "QSPI1CoreID" = "num:i(255)"!]
  [!VAR "QSPI2CoreID" = "num:i(255)"!]
  [!VAR "QSPI3CoreID" = "num:i(255)"!]
  [!VAR "QSPI4CoreID" = "num:i(255)"!]
  [!VAR "QSPI5CoreID" = "num:i(255)"!]

        [!// If QSPIx is configured than extract core ID
        [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI0']) = num:i(1)"!]
            [!CALL "Spi_CG_GetCore", "Channel" = "'QSPI0'"!]
            [!VAR "QSPI0CoreID" = "$CGCoreId_Extract"!]
        [!ENDIF!]

        [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI1']) = num:i(1)"!]
            [!CALL "Spi_CG_GetCore", "Channel" = "'QSPI1'"!]
            [!VAR "QSPI1CoreID" = "$CGCoreId_Extract"!]
        [!ENDIF!]

        [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI2']) = num:i(1)"!]
            [!CALL "Spi_CG_GetCore", "Channel" = "'QSPI2'"!]
            [!VAR "QSPI2CoreID" = "$CGCoreId_Extract"!]
        [!ENDIF!]

        [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI3']) = num:i(1)"!]
            [!CALL "Spi_CG_GetCore", "Channel" = "'QSPI3'"!]
            [!VAR "QSPI3CoreID" = "$CGCoreId_Extract"!]
        [!ENDIF!]

        [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI4']) = num:i(1)"!]
            [!CALL "Spi_CG_GetCore", "Channel" = "'QSPI4'"!]
            [!VAR "QSPI4CoreID" = "$CGCoreId_Extract"!]
        [!ENDIF!]

        [!IF "count(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI5']) = num:i(1)"!]
            [!CALL "Spi_CG_GetCore", "Channel" = "'QSPI5'"!]
            [!VAR "QSPI5CoreID" = "$CGCoreId_Extract"!]
        [!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!]


[!/*****************************************************************************
MACRO: Spi_CGGenerateSequence_IDCode
Macro to generate code for #define with sequence ID
******************************************************************************/!]
[!MACRO "Spi_CGGenerateSequence_IDCode", "SpiOutQSPIxCount" = "","SpiOutQSPIxSeq" = "","Spi_OutSequenceID" = ""!][!//
[!NOCODE!][!//

[!FOR "Spi_LoopCntr" = "num:i(1)" TO "$SpiOutQSPIxCount"!]
[!VAR "SpiExtractSeqIndex" = "num:i((node:value(concat('SpiDriver/SpiSequence/',text:split($SpiOutQSPIxSeq,',')[position() = $Spi_LoopCntr],'/SpiSequenceId'))) + 300)"!][!//
[!VAR "Spi_SequencePhysicalIndex" = "text:replace( $Spi_SequencePhysicalIndex, $SpiExtractSeqIndex, num:i($Spi_SequenceID ))"!][!//
[!VAR "Spi_SequenceID"="$Spi_SequenceID + num:i(1)"!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGGenerateJob_IDCode
Macro to generate code for #define with Job ID
******************************************************************************/!]
[!MACRO "Spi_CGGenerateJob_IDCode", "SpiOutQSPIxCount" = "","SpiOutQSPIxJob" = "","Spi_OutJobID" = ""!][!//
[!NOCODE!][!//

[!FOR "Spi_LoopCntr" = "num:i(1)" TO "$SpiOutQSPIxCount"!]
[!VAR "SpiExtractJobIndex" = "num:i((node:value(concat('SpiDriver/SpiJob/',text:split($SpiOutQSPIxJob,',')[position() = $Spi_LoopCntr],'/SpiJobId'))) + 300)"!][!//
[!VAR "Spi_JobPhysicalIndex" = "text:replace( $Spi_JobPhysicalIndex, $SpiExtractJobIndex, num:i($Spi_JobID ))"!][!//
[!VAR "Spi_JobID"="$Spi_JobID + num:i(1)"!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
MACRO: Spi_CGGenerateChannel_IDCode
Macro to generate code for #define with Channel ID
******************************************************************************/!]
[!MACRO "Spi_CGGenerateChannel_IDCode", "SpiOutQSPIxCount" = "","SpiOutQSPIxChannel" = "","Spi_OutChannelID" = ""!][!//
[!NOCODE!][!//

[!FOR "Spi_LoopCntr" = "$SpiOutQSPIxCount" TO "num:i(1)" STEP "-1"!]
[!VAR "SpiExtractChnlIndex" = "num:i((node:value(concat('SpiDriver/SpiChannel/',text:split($SpiOutQSPIxChannel,',')[position() = $Spi_LoopCntr],'/SpiChannelId'))) + 300)"!][!//
[!VAR "Spi_ChannelPhysicalIndex" = "text:replace( $Spi_ChannelPhysicalIndex, $SpiExtractChnlIndex, num:i($Spi_ChannelID ))"!][!//
[!VAR "Spi_ChannelID"="$Spi_ChannelID + num:i(1)"!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!ENDMACRO!]

/*******************************************************************************
** Name             : Spi_CGGenerateModuleMap                                    **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
[!MACRO "Spi_CGGenerateModuleMap", "Module" = ""!][!//
[!NOCODE!][!//
[!SELECT "as:modconf('ResourceM')[1]"!][!//
  [!VAR "CGMasterCoreId_Extract" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
  [!VAR "CGCoreID" = "num:i(0)"!][!//
  [!VAR "CGAllocatedChannelMap" = "''"!][!//
  [!VAR "CGCoreMap" = "''"!][!//
  [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
    [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
    [!LOOP "ResourceMAllocation/*"!][!//
      [!IF "$Module = ./ResourceMModuleName"!][!//
        [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
        [!VAR "ResourceName" = "node:value(node:ref(./ResourceMResourceRef)/SpiHwConfigKernel)"!][!//
        [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGCoreID, '_', $ResourceName, ','))"!][!//
        [!VAR "CGAllocatedChannelMap" = "text:toupper(concat($CGAllocatedChannelMap, $ResourceName, ','))"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Spi_CG_GetCore                                          **
**                                                                            **
** Description      : Macro to get the core to which the channel is assigned  **
**                                                                            **
** Pre-requisite    : CG_GenerateModuleMap macro should be called before      **
**                    calling this macro                                      **
*******************************************************************************/
[!MACRO "Spi_CG_GetCore", "Channel" = ""!][!//
[!NOCODE!]

  [!IF "(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!]
    [!VAR "CGCoreIndexPos" = "num:i(text:indexOf(text:split($CGCoreMap), concat(text:toupper($Channel),',')) - 2)"!]
    [!VAR "CGCoreId_Extract" = "num:i(substring( $CGCoreMap, $CGCoreIndexPos, num:i(1)))"!]
  [!ELSE!]
    [!VAR "CGCoreId_Extract" = "num:i($CGMasterCoreId_Extract)"!]
  [!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]]