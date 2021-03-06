#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
            
			// Config interface as we can't talk to composite directly
			USB_Descriptor_Interface_t            Config_Interface;
			USB_Descriptor_Endpoint_t             Config_DataOutEndpoint;
			USB_Descriptor_Endpoint_t             Config_DataInEndpoint;
            
			// Inputs HID Interface
			USB_Descriptor_Interface_t            HID1_Interface;
			USB_HID_Descriptor_HID_t              HID1_InputsHID;
			USB_Descriptor_Endpoint_t             HID1_ReportINEndpoint;
            
            // LED HID Interface for pretty lights
			USB_Descriptor_Interface_t            HID2_Interface;
			USB_HID_Descriptor_HID_t              HID2_LEDHID;
			USB_Descriptor_Endpoint_t             HID2_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;

		/** Enum for the device interface descriptor IDs within the device.
		 */
		enum InterfaceDescriptors_t
		{
            INTERFACE_ID_Config   = 0, /**< Config interface descriptor ID  */
			INTERFACE_ID_Inputs   = 1, /**< Keyboard and mouse interface descriptor ID */
            INTERFACE_ID_LED      = 2, /**< LED interface descriptor ID  */
		};

		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 */
		enum StringDescriptors_t
		{
			STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
			STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
			STRING_ID_Product      = 2, /**< Product string ID */
            STRING_ID_Controls     = 3, 
            STRING_ID_Config       = 4, 
            STRING_ID_LED          = 5,  /**< LED string ID */
            STRING_ID_LED_Indiv    = 6,
		};
        
        enum URLDescriptors_t
        {
            URL_ID_Config     = 1,
        };
        
		/** Enum for the HID report IDs used in the device. */
		enum
		{
			HID_REPORTID_MouseReport    = 0x01,
			HID_REPORTID_KeyboardReport = 0x02,
			HID_REPORTID_JoystickReport = 0x03,
		} HID_Report_IDs;

	/* Macros: */
        #define CONFIG_OUT_EPADDR            (ENDPOINT_DIR_OUT | 1)
        #define CONFIG_IN_EPADDR             (ENDPOINT_DIR_IN  | 2)
		#define INPUTS_EPADDR                (ENDPOINT_DIR_IN  | 3)
        #define LED_EPADDR                   (ENDPOINT_DIR_IN  | 4)
        
        /* Contrary to my incorrect earlier assumptions, this is NOT the size
         * of reports that can go out to the host - that's defined by the HID
         * report descriptor. Instead, it's the maximum packet size for the transfer,
         * which will be split up as needed to fit all the bytes in the report.
         * For ease of use, I've set this to the control endpoint size.
         *
         * I can only hope this is finally correct - buffer overflow could also
         * cause this I think, but I have so much free RAM I don't think so */
		#define INPUTS_EPSIZE    FIXED_CONTROL_ENDPOINT_SIZE
        #define LED_EPSIZE       FIXED_CONTROL_ENDPOINT_SIZE
        // ignoring board limits, bulk endpoints MUST be 8, 16, 32 or 64 bytes
        // set to max EP size of the atmega16u2, to give room to grow and not eat frames
        #define CONFIG_EPSIZE    64

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);
        
        void USB_Process_BOS(void);

#endif

