/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/**********PREPROCESSOR DIRECTIVES**********/
#include "CommonVariables.h"
#include "SirenState.h"
#include "Tones.h"
#include "DACaudio.h"

/**********DEFINED CONSTANTS**********/
static const uint8 DEFAULT_CONFIGURATION_LIST[SPEAKER_COUNT * CHANNEL_COUNT_PER_SPEAKER] = 
    {COPS_SONG, WAIL, SLOW_YELP, PHASER, HORN, HORN_PHASER,
    COPS_SONG, WAIL, SLOW_YELP, PHASER, HORN, HORN_PHASER};

static const uint16 EEPROM_KEY_INDEX = 0xFF;
static const uint8 EEPROM_KEY_VALUE = 0x55;

enum InputType
{
	RADIO_MIC,
	AUDIO_TONE,
	PARK_KILL,
	HORN_RING,
	SIREN_TONE,
	NO_INPUT
};

enum ToneChannelNumber
{
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6,
	NO_CHANNEL
};

/**********DATA STRUCTURES**********/
static struct
{
    uint8 bRadioAndMicKey;
    uint8 bParkKill;
    uint8 bTackSwitch;
    uint8 bHornRing;  
    uint8 bDualDelay;
    enum ToneChannelNumber highestPriorityChannel[SPEAKER_COUNT];
}InputRead;

typedef struct
{
	enum ToneType currentTone;
	uint8 bRisingEdge;
	uint8 bManualWailToneStatus;
	uint8 bAudioToneStatus;
}SpeakerStatus;

static SpeakerStatus Speaker[SPEAKER_COUNT];

/**********GLOBAL VARIABLES**********/
static enum ToneType toneConfigurationList[SPEAKER_COUNT][CHANNEL_COUNT_PER_SPEAKER];
static uint8 bToneChangeOnHornRing = false;

/**********FUNCTION PROTOTYPES**********/
static void processInputLogic(void);
static void updateAudio(void);
static enum ToneChannelNumber getHighestPriorityChannel(uint8 bSpeakerNumber);
static enum InputType getHighestPriorityInput(void);
static enum ToneType getAlternatingTone(enum ToneType toneSelection);
static uint8 isTrailingAudioTone(enum ToneType toneSelection);
static uint8 isSong(enum ToneType toneSelection);
static uint8 isAudioTone(enum ToneType toneSelection);

/**********DEFINED FUNCTIONS**********/

/*******************************************************************************
* Function Name: initializeToneConfigurationList
********************************************************************************
*
* Summary:
*  Sets the configuration list to the tones saved in EEPROM
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void initializeToneConfigurationList(void)
{
    uint8 bHasNoTone = false;  
    uint8 bSpeakerIndex = SPEAKER_1;
    uint8 channelIndex = NO_CHANNEL;   
    uint16 addressIndex = 0;
    
    EEPROM_Start();   
    
    for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
    {   //Check for indices with no tone written to it
        for(channelIndex = 0; channelIndex < CHANNEL_COUNT_PER_SPEAKER; channelIndex++)
        {
            addressIndex = (uint16)(CHANNEL_COUNT_PER_SPEAKER * bSpeakerIndex + channelIndex);
            if(EEPROM_ReadByte(addressIndex) >= TONE_TYPE_LIST_SIZE)
            {   //Terminate loop after finding first invalid tone
                bHasNoTone = true;
                break;
            }
        }
    }
    
    if((bHasNoTone == true) || (EEPROM_ReadByte(EEPROM_KEY_INDEX) != EEPROM_KEY_VALUE))
    {   //Write to EEPROM 
        EEPROM_UpdateTemperature(); //Optimizes write timings based on temperature reading 
        
        for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
        {   //Obtain tones from EEPROM to configure channels
            for(channelIndex = 0; channelIndex < CHANNEL_COUNT_PER_SPEAKER; channelIndex++)
            {
                addressIndex = (uint16)(CHANNEL_COUNT_PER_SPEAKER * bSpeakerIndex + channelIndex);
                EEPROM_WriteByte(DEFAULT_CONFIGURATION_LIST[addressIndex], addressIndex);
            }
        }
        
        EEPROM_WriteByte(EEPROM_KEY_VALUE, EEPROM_KEY_INDEX);
    }
    
    for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
    {   //Obtain tones from EEPROM to configure channels
        for(channelIndex = 0; channelIndex < CHANNEL_COUNT_PER_SPEAKER; channelIndex++)
        {
            addressIndex = (uint16)(CHANNEL_COUNT_PER_SPEAKER * bSpeakerIndex + channelIndex);
            toneConfigurationList[bSpeakerIndex][channelIndex] = EEPROM_ReadByte(addressIndex);
        }
    }
}

/*******************************************************************************
* Function Name: initializeInputReadings
********************************************************************************
*
* Summary:
*  Sets InputRead struct to current input readings at the beginning of the program
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void initializeInputReadings(void)
{
    InputRead.bRadioAndMicKey = RadioRebroadcastInput_Read() ||  MicKeyInput_Read();
    InputRead.bParkKill = ParkKillStatus_Read() & 0x01;
    InputRead.bHornRing = HornRingStatus_Read() & 0x01;
    InputRead.highestPriorityChannel[SPEAKER_1] = getHighestPriorityChannel(SPEAKER_1);
    InputRead.highestPriorityChannel[SPEAKER_2] = getHighestPriorityChannel(SPEAKER_2);
    
    processInputLogic();
	updateAudio();
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void enableToneInputInterrupts(void)
{
    TackSwitchISR_Start();
    TackSwitchStatus_InterruptEnable();
    
    DualDelayISR_Start();
    DualDelayStatus_InterruptEnable();
    
    ModeStatusISR_Start();
    ModeStatus_InterruptEnable();
    
    ModeStatus2ISR_Start();
    ModeStatus2_InterruptEnable();
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void disableToneInputInterrupts(void)
{
    TackSwitchStatus_InterruptDisable();
    TackSwitchISR_Stop();
    
    DualDelayStatus_InterruptDisable();
    DualDelayISR_Stop();
    
    ModeStatus_InterruptDisable();
    ModeStatusISR_Stop();
    
    ModeStatus2_InterruptDisable();
    ModeStatus2ISR_Stop();
}

/*******************************************************************************
* Function Name: processRadioMicKeyRoutine
********************************************************************************
*
* Summary:
*  Updates the siren system for the radio rebroadcast or mic key input change,
*  called in RadioMicKeyISR
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void processRadioMicKeyRoutine(void)
{
    InputRead.bRadioAndMicKey = RadioRebroadcastInput_Read() ||  MicKeyInput_Read();
    processInputLogic();
	updateAudio();
}

/*******************************************************************************
* Function Name: processParkKillRoutine
********************************************************************************
*
* Summary:
*  Updates the siren system for the park kill input change, called in ParkKillISR
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void processParkKillRoutine(void)
{
    InputRead.bParkKill = ParkKillStatus_Read() & 0x01;    
    processInputLogic();
	updateAudio();
}

/*******************************************************************************
* Function Name: processTackSwitchRoutine
********************************************************************************
*
* Summary:
*  Cycles through the tones and configures the tone selection for the specified
*  input, called in TackSwitchISR
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void processTackSwitchRoutine(void)
{
    enum ToneType toneToPlay = NO_TONE;
    uint16 addressIndex = 0;
    uint8 channelIndex = 0;
    uint8 bSpeakerIndex = SPEAKER_1;
    
    InputRead.bTackSwitch = TackSwitchStatus_Read() & 0x01;
    
    if((!InputRead.bRadioAndMicKey) && (!InputRead.bParkKill))
    {
        if(InputRead.bTackSwitch)
        {   
            deactivateAudio();
            deactivateManualWail();
            stopPWMTone(SPEAKER_1);
            stopPWMTone(SPEAKER_2); 
    		stopAudioTone(SPEAKER_1);
    		stopAudioTone(SPEAKER_2);
        }
        else
        {   //Tack switch is disabled
            EEPROM_UpdateTemperature(); //Optimizes write timings based on temperature reading
            
            for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
            {   //Speaker 1 addresses range 0x00 to 0x05, Speaker 2 addresses range 0x06 to 0x0B 
                channelIndex = InputRead.highestPriorityChannel[bSpeakerIndex];
                addressIndex = (uint16)(CHANNEL_COUNT_PER_SPEAKER * bSpeakerIndex + channelIndex);
                
                if(channelIndex != NO_CHANNEL)
                {
                    if(toneToPlay == NO_TONE)
                    {   //Gets original tone for that channel as starting tone in the list               
                        toneToPlay = EEPROM_ReadByte(addressIndex);    
                        toneToPlay = (toneToPlay + 1) % TONE_TYPE_LIST_SIZE;  //Increments to next tone in circular list
                        
                        if(toneToPlay == NO_TONE)
                            toneToPlay++;  //Makes sure a tone is always selected
                    }
                    
                    if(toneToPlay != NO_TONE)
                    {   //Configure new tone to the enabled channels
                        EEPROM_WriteByte(toneToPlay, addressIndex);
                        toneConfigurationList[bSpeakerIndex][channelIndex] = toneToPlay;
                        Speaker[bSpeakerIndex].currentTone = toneToPlay;
                        
                        if(Speaker[bSpeakerIndex].currentTone == MANUAL_WAIL)
                            Speaker[bSpeakerIndex].bManualWailToneStatus = true;
                    }
                    
                    if(isSong(toneToPlay))
                        Speaker[bSpeakerIndex].bRisingEdge = true;
                }
            }
            
            updateAudio();  
        }
    }
}

/*******************************************************************************
* Function Name: processHornRingRoutine
********************************************************************************
*
* Summary:
*  Updates the siren system for the horn input change, called in HornRingISR
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void processHornRingRoutine(void)
{
    InputRead.bHornRing = HornRingStatus_Read() & 0x01;
    processInputLogic();
	updateAudio();
}

/*******************************************************************************
* Function Name: processDualDelayRoutine
********************************************************************************
*
* Summary:
*  Activates delay functionality for the two current tones, called in DualDelayISR
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void processDualDelayRoutine(void)
{
    InputRead.bDualDelay = DualDelayStatus_Read() & 0x01;
    processInputLogic();
	updateAudio();
}

/*******************************************************************************
* Function Name: processToneChangeRoutine
********************************************************************************
*
* Summary:
*  Updates the siren system for the tone input change, called in ModeStatusISR
*   and ModeStatus2ISR
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void processToneChangeRoutine(uint8 bSpeaker)
{  
    uint8 currentChannel = NO_CHANNEL;
    
    if((bSpeaker != SPEAKER_1) && (bSpeaker != SPEAKER_2))
        return;
	
	currentChannel = getHighestPriorityChannel(bSpeaker);
	if(currentChannel == NO_CHANNEL)
		Speaker[bSpeaker].bRisingEdge = false;
	else
	{
		if((InputRead.highestPriorityChannel[bSpeaker] == NO_CHANNEL) ||
			(currentChannel > InputRead.highestPriorityChannel[bSpeaker]))
			Speaker[bSpeaker].bRisingEdge = true;
		else
			Speaker[bSpeaker].bRisingEdge = false;
	}
    
	Speaker[!bSpeaker].bRisingEdge = false;
    InputRead.highestPriorityChannel[bSpeaker] = currentChannel;
    processInputLogic();
	updateAudio();
}

/*******************************************************************************
* Function Name: getHighestPriorityChannel
********************************************************************************
*
* Summary:
*  Determines the active tone with the highest priority
*
* Parameters: 
*   bSpeakerNumber - The speaker selection for the input reading
*
* Return:
*   The active tone mode with the highest priority
*
*******************************************************************************/
static enum ToneChannelNumber getHighestPriorityChannel(uint8 bSpeakerNumber)
{
    uint8 modeStatusByte = 0;
    
    if((bSpeakerNumber != 0) && (bSpeakerNumber != SPEAKER_2))
        return NO_CHANNEL;
    
    if(bSpeakerNumber)
        modeStatusByte = ModeStatus2_Read();
    else
        modeStatusByte = ModeStatus_Read();
    
    if(modeStatusByte & 0x20)
        return CHANNEL_6;
    if(modeStatusByte & 0x10)
        return CHANNEL_5;
    if(modeStatusByte & 0x08)
        return CHANNEL_4;
    if(modeStatusByte & 0x04)
        return CHANNEL_3;    
    if(modeStatusByte & 0x02)
        return CHANNEL_2;
    if(modeStatusByte & 0x01)
        return CHANNEL_1;
    
    return NO_CHANNEL;
}

/*******************************************************************************
* Function Name: processInputLogic
********************************************************************************
*
* Summary:
*  The state machine that determines the tone outcome for each speaker.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void processInputLogic(void)
{
	enum InputType highestPriorityInput = NO_INPUT;
	enum ToneChannelNumber currentChannel = NO_CHANNEL;
    uint8 bSpeakerIndex = SPEAKER_1;
	
	highestPriorityInput = getHighestPriorityInput();
	
	switch(highestPriorityInput)
	{
		case RADIO_MIC:
			Speaker[SPEAKER_1].currentTone = NO_TONE;
			Speaker[SPEAKER_2].currentTone = NO_TONE;			
			break;
			
		case AUDIO_TONE:	//One of the speakers is configured to an audio tone
            currentChannel = InputRead.highestPriorityChannel[SPEAKER_1];
			if((currentChannel != NO_CHANNEL) && (!isAudioTone(toneConfigurationList[SPEAKER_1][currentChannel])))
			{
                currentChannel = InputRead.highestPriorityChannel[SPEAKER_2];
                if(!isSong(toneConfigurationList[SPEAKER_2][currentChannel]))
                {
                    Speaker[SPEAKER_1].currentTone = toneConfigurationList[SPEAKER_2][currentChannel];
					Speaker[SPEAKER_2].currentTone = toneConfigurationList[SPEAKER_2][currentChannel];    
                }
                else
                {
                    if((Speaker[SPEAKER_2].bRisingEdge == true) || (!isSongFinished()))
                    {
                        Speaker[SPEAKER_1].currentTone = toneConfigurationList[SPEAKER_2][currentChannel];
    					Speaker[SPEAKER_2].currentTone = toneConfigurationList[SPEAKER_2][currentChannel];    
                    }
                    else
                    {
                        Speaker[SPEAKER_1].currentTone = NO_TONE;
					    Speaker[SPEAKER_2].currentTone = NO_TONE;
                    }
                }
            }
            else
            {
                if(!isSong(toneConfigurationList[SPEAKER_1][currentChannel]))
                {
                    Speaker[SPEAKER_1].currentTone = toneConfigurationList[SPEAKER_1][currentChannel];
					Speaker[SPEAKER_2].currentTone = toneConfigurationList[SPEAKER_1][currentChannel];    
                }
                else
                {
                    if((Speaker[SPEAKER_1].bRisingEdge == true) || (!isSongFinished()))
                    {
                        Speaker[SPEAKER_1].currentTone = toneConfigurationList[SPEAKER_1][currentChannel];
    					Speaker[SPEAKER_2].currentTone = toneConfigurationList[SPEAKER_1][currentChannel];    
                    }
                    else
                    {
                        Speaker[SPEAKER_1].currentTone = NO_TONE;
					    Speaker[SPEAKER_2].currentTone = NO_TONE;
                    }
                }
            }		
			break;
			
		case PARK_KILL:
			Speaker[SPEAKER_1].currentTone = NO_TONE;
			Speaker[SPEAKER_2].currentTone = NO_TONE;
			break;
			
		case HORN_RING:
			if((InputRead.highestPriorityChannel[SPEAKER_1] == NO_CHANNEL) &&
				(InputRead.highestPriorityChannel[SPEAKER_2] == NO_CHANNEL))
			{
				bToneChangeOnHornRing = false;
				Speaker[SPEAKER_1].currentTone = HORN;
				Speaker[SPEAKER_2].currentTone = HORN;
			}
			else
			{
				bToneChangeOnHornRing = !bToneChangeOnHornRing;
				Speaker[SPEAKER_1].currentTone = NO_TONE;
				Speaker[SPEAKER_2].currentTone = NO_TONE;
			}
			break;
			
		case SIREN_TONE:
			for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
			{
				currentChannel = InputRead.highestPriorityChannel[bSpeakerIndex];
				
				if(currentChannel == NO_CHANNEL)
				{
					if(isTrailingAudioTone(Speaker[bSpeakerIndex].currentTone) && isAudioActive())
						Speaker[bSpeakerIndex].bAudioToneStatus = true;
					else if((Speaker[bSpeakerIndex].currentTone == MANUAL_WAIL) && 
                        isManualWailActive(bSpeakerIndex))
						Speaker[bSpeakerIndex].bManualWailToneStatus = true;
					else
					{
						Speaker[bSpeakerIndex].bAudioToneStatus = false;
						Speaker[bSpeakerIndex].bManualWailToneStatus = false;
						Speaker[bSpeakerIndex].currentTone = NO_TONE;
					}
				}
				else
				{
					if(bToneChangeOnHornRing)
						Speaker[bSpeakerIndex].currentTone = getAlternatingTone(toneConfigurationList[bSpeakerIndex][currentChannel]);
					else
						Speaker[bSpeakerIndex].currentTone = toneConfigurationList[bSpeakerIndex][currentChannel];
				}
			}
			break;
			
		case NO_INPUT:
            bToneChangeOnHornRing = false;
			for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
			{
				if(isTrailingAudioTone(Speaker[bSpeakerIndex].currentTone) && isAudioActive())
					Speaker[bSpeakerIndex].bAudioToneStatus = true;
				else if((Speaker[bSpeakerIndex].currentTone == MANUAL_WAIL) && 
                    isManualWailActive(bSpeakerIndex))
					Speaker[bSpeakerIndex].bManualWailToneStatus = true;
				else
				{
					Speaker[bSpeakerIndex].bAudioToneStatus = false;
					Speaker[bSpeakerIndex].bManualWailToneStatus = false;
					Speaker[bSpeakerIndex].currentTone = NO_TONE;
				}
			}
			break;
			
		default: break;
	}
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters: 
*   
*
* Return:
*   
*
*******************************************************************************/
static void updateAudio(void)
{
    enum InputType highestPriorityInput = NO_INPUT;
	uint8 bSpeakerIndex = SPEAKER_1;
	
	for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
	{
		stopPWMTone(bSpeakerIndex);
		stopAudioTone(bSpeakerIndex);
	}
    
    highestPriorityInput = getHighestPriorityInput();
	
	switch(highestPriorityInput)
	{
		case RADIO_MIC:
			deactivateManualWail(); //Deactivate tones and leave one power amp on
			deactivateAudio();
			PowerAmpOutput1_Write(true);
			PowerAmpOutput2_Write(false);			
			break;
			
		case AUDIO_TONE:	//One of the speakers is configured to an audio tone
            deactivateManualWail();
			if(isAudioTone(Speaker[SPEAKER_1].currentTone))
			{
                playAudioTone(SPEAKER_1, Speaker[SPEAKER_1].currentTone, Speaker[SPEAKER_1].bAudioToneStatus);
    			PowerAmpOutput1_Write(true);    //Enable both speakers
    			PowerAmpOutput2_Write(true);
            }
            else if(isAudioTone(Speaker[SPEAKER_2].currentTone))
			{
                playAudioTone(SPEAKER_2, Speaker[SPEAKER_2].currentTone, Speaker[SPEAKER_2].bAudioToneStatus);
			    PowerAmpOutput1_Write(true);    //Enable both speakers
			    PowerAmpOutput2_Write(true);
            }
            else
            {
                PowerAmpOutput1_Write(false);
			    PowerAmpOutput2_Write(false);
            }
                
						
			break;
			
		case PARK_KILL:
			deactivateManualWail(); //Deactivate tones and turn off both amplifiers
            deactivateAudio();
    		PowerAmpOutput1_Write(false);
            PowerAmpOutput2_Write(false);
			break;
			
		case HORN_RING:
			deactivateManualWail(); //Deactivate tones and turn off both amplifiers
            deactivateAudio();			
			if((Speaker[SPEAKER_1].currentTone == HORN) &&
				(Speaker[SPEAKER_2].currentTone == HORN))
			{
				playPWMTone(SPEAKER_1, HORN, false, false);
				playPWMTone(SPEAKER_2, HORN, false, false);
				PowerAmpOutput1_Write(true);    //Enable both speakers
				PowerAmpOutput2_Write(true);
			}
			else
			{
				PowerAmpOutput1_Write(false);
				PowerAmpOutput2_Write(false);
			}
			break;
			
		case SIREN_TONE:
		case NO_INPUT:
			for(bSpeakerIndex = 0; bSpeakerIndex < SPEAKER_COUNT; bSpeakerIndex++)
			{
				playPWMTone(bSpeakerIndex, Speaker[bSpeakerIndex].currentTone, 
					Speaker[bSpeakerIndex].bManualWailToneStatus, InputRead.bDualDelay);
				
				if(Speaker[bSpeakerIndex].currentTone != NO_TONE)
				{
					if(bSpeakerIndex)
                        PowerAmpOutput2_Write(true);
                    else
                        PowerAmpOutput1_Write(true);
				}
				else
				{
					if(bSpeakerIndex)
                        PowerAmpOutput2_Write(false);
                    else
                        PowerAmpOutput1_Write(false);
					
					playAudioTone(bSpeakerIndex, NO_TONE, false);
				}
			}
			break;

		default: break;
	}
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters: 
*   
*
* Return:
*   
*
*******************************************************************************/
static enum InputType getHighestPriorityInput(void)
{
	uint8 speakerIndex = SPEAKER_1;
	enum ToneChannelNumber channelNumber[SPEAKER_COUNT];
	enum ToneType toneSelection[SPEAKER_COUNT];
	
	if(InputRead.bRadioAndMicKey)
		return RADIO_MIC;
	
	for(speakerIndex = 0; speakerIndex < SPEAKER_COUNT; speakerIndex++)
	{
		channelNumber[speakerIndex] = InputRead.highestPriorityChannel[speakerIndex];		
		if(channelNumber[speakerIndex] != NO_CHANNEL)
		{
			toneSelection[speakerIndex]	= toneConfigurationList[speakerIndex][channelNumber[speakerIndex]];
			if(isAudioTone(toneSelection[speakerIndex]))
				return AUDIO_TONE;
		}
	}
	
    if(InputRead.bParkKill)
		return PARK_KILL;
    if(InputRead.bHornRing)
		return HORN_RING;
    
	for(speakerIndex = 0; speakerIndex < SPEAKER_COUNT; speakerIndex++)
	{
		if(channelNumber[speakerIndex] != NO_CHANNEL)
			return SIREN_TONE;
	}
	
	return NO_INPUT;
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters: 
*   
*
* Return:
*   
*
*******************************************************************************/
static enum ToneType getAlternatingTone(enum ToneType toneSelection)
{
	if((toneSelection == NO_TONE) || isAudioTone(toneSelection) || (toneSelection == TEST_TONE))
		return toneSelection;
	
	if((toneSelection == MECHANICAL) || (toneSelection == PCALL_FAST))
		return PHASER;
	
	if(toneSelection == PHASER_YELP)
		return HORN_PHASER;
	
	return (toneSelection + 1);
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters: 
*   
*
* Return:
*   
*
*******************************************************************************/
static uint8 isTrailingAudioTone(enum ToneType toneSelection)
{
	if(!isAudioTone(toneSelection))
		return false;

	if(toneSelection == COPS_SONG)
		return false;
	
	return true;
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters: 
*   
*
* Return:
*   
*
*******************************************************************************/
static uint8 isSong(enum ToneType toneSelection)
{
	if(toneSelection != COPS_SONG)
		return false;
	
	return true;
}

/*******************************************************************************
* Function Name: 
********************************************************************************
*
* Summary:
*  
*
* Parameters: 
*   
*
* Return:
*   
*
*******************************************************************************/
static uint8 isAudioTone(enum ToneType toneSelection)
{
	if((toneSelection < ECTOSIREN) || (toneSelection > REMAIN_WINDOW_DOWN))
		return false;
	
	return true;
}
