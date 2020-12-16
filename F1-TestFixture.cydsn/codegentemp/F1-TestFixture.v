// ======================================================================
// F1-TestFixture.v generated from TopDesign.cysch
// 12/16/2020 at 14:47
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PSOC5LP 2
`define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
`define CYDEV_CHIP_REV_PSOC5LP_ES0 0
`define CYDEV_CHIP_DIE_PSOC5TM 3
`define CYDEV_CHIP_REV_PSOC5TM_PRODUCTION 1
`define CYDEV_CHIP_REV_PSOC5TM_ES1 1
`define CYDEV_CHIP_REV_PSOC5TM_ES0 0
`define CYDEV_CHIP_DIE_TMA4 4
`define CYDEV_CHIP_REV_TMA4_PRODUCTION 17
`define CYDEV_CHIP_REV_TMA4_ES 17
`define CYDEV_CHIP_REV_TMA4_ES2 33
`define CYDEV_CHIP_DIE_PSOC4A 5
`define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17
`define CYDEV_CHIP_REV_PSOC4A_ES0 17
`define CYDEV_CHIP_DIE_PSOC6ABLE2 6
`define CYDEV_CHIP_REV_PSOC6ABLE2_ES 17
`define CYDEV_CHIP_REV_PSOC6ABLE2_PRODUCTION 33
`define CYDEV_CHIP_REV_PSOC6ABLE2_NO_UDB 33
`define CYDEV_CHIP_DIE_VOLANS 7
`define CYDEV_CHIP_REV_VOLANS_PRODUCTION 0
`define CYDEV_CHIP_DIE_BERRYPECKER 8
`define CYDEV_CHIP_REV_BERRYPECKER_PRODUCTION 0
`define CYDEV_CHIP_DIE_CRANE 9
`define CYDEV_CHIP_REV_CRANE_PRODUCTION 0
`define CYDEV_CHIP_DIE_FM3 10
`define CYDEV_CHIP_REV_FM3_PRODUCTION 0
`define CYDEV_CHIP_DIE_FM4 11
`define CYDEV_CHIP_REV_FM4_PRODUCTION 0
`define CYDEV_CHIP_DIE_EXPECT 2
`define CYDEV_CHIP_REV_EXPECT 0
`define CYDEV_CHIP_DIE_ACTUAL 2
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_FAMILY_PSOC6 4
`define CYDEV_CHIP_FAMILY_FM0P 5
`define CYDEV_CHIP_FAMILY_FM3 6
`define CYDEV_CHIP_FAMILY_FM4 7
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_MEMBER_5B 2
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_4G 4
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 5
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 6
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0
`define CYDEV_CHIP_MEMBER_4X 7
`define CYDEV_CHIP_REVISION_4X_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4O 8
`define CYDEV_CHIP_REVISION_4O_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4R 9
`define CYDEV_CHIP_REVISION_4R_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4T 10
`define CYDEV_CHIP_REVISION_4T_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 11
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4S 12
`define CYDEV_CHIP_REVISION_4S_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4W 13
`define CYDEV_CHIP_REVISION_4W_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AC 14
`define CYDEV_CHIP_REVISION_4AC_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Q 15
`define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Y 16
`define CYDEV_CHIP_REVISION_4Y_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Z 17
`define CYDEV_CHIP_REVISION_4Z_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 18
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 19
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 20
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4V 21
`define CYDEV_CHIP_REVISION_4V_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 22
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AA 23
`define CYDEV_CHIP_REVISION_4AA_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 24
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 25
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4P 26
`define CYDEV_CHIP_REVISION_4P_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4M 27
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AB 28
`define CYDEV_CHIP_REVISION_4AB_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 29
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 30
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_6A 31
`define CYDEV_CHIP_REVISION_6A_ES 17
`define CYDEV_CHIP_REVISION_6A_PRODUCTION 33
`define CYDEV_CHIP_REVISION_6A_NO_UDB 33
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 32
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 33
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 34
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM3 35
`define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM4 36
`define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_USED 3
`define CYDEV_CHIP_MEMBER_USED 2
`define CYDEV_CHIP_REVISION_USED 0
// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: B_UART_v2_50
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\B_UART_v2_50"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\B_UART_v2_50\B_UART_v2_50.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\B_UART_v2_50"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\B_UART_v2_50\B_UART_v2_50.v"
`endif

// UART_v2_50(Address1=0, Address2=0, BaudRate=230400, BreakBitsRX=13, BreakBitsTX=13, BreakDetect=false, CRCoutputsEn=false, Enable_RX=1, Enable_RXIntInterrupt=0, Enable_TX=1, Enable_TXIntInterrupt=1, EnableHWAddress=0, EnIntRXInterrupt=false, EnIntTXInterrupt=true, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=false, InternalClock=true, InternalClockToleranceMinus=3.93736842105263, InternalClockTolerancePlus=3.93736842105263, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=1, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=true, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=true, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, ParityTypeSw=false, RequiredClock=1843200, RXAddressMode=0, RXBufferSize=4, RxBuffRegSizeReplacementString=uint8, RXEnable=true, TXBitClkGenDP=true, TXBufferSize=1024, TxBuffRegSizeReplacementString=uint16, TXEnable=true, Use23Polling=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=UART_v2_50, CY_CONFIG_TITLE=UART_230400, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=UART_230400, CY_INSTANCE_SHORT_NAME=UART_230400, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=50, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.3, INSTANCE_NAME=UART_230400, )
module UART_v2_50_0 (
    cts_n,
    tx,
    rts_n,
    tx_en,
    clock,
    reset,
    rx,
    tx_interrupt,
    rx_interrupt,
    tx_data,
    tx_clk,
    rx_data,
    rx_clk);
    input       cts_n;
    output      tx;
    output      rts_n;
    output      tx_en;
    input       clock;
    input       reset;
    input       rx;
    output      tx_interrupt;
    output      rx_interrupt;
    output      tx_data;
    output      tx_clk;
    output      rx_data;
    output      rx_clk;

    parameter Address1 = 0;
    parameter Address2 = 0;
    parameter EnIntRXInterrupt = 0;
    parameter EnIntTXInterrupt = 1;
    parameter FlowControl = 0;
    parameter HalfDuplexEn = 0;
    parameter HwTXEnSignal = 0;
    parameter NumDataBits = 8;
    parameter NumStopBits = 1;
    parameter ParityType = 0;
    parameter RXEnable = 1;
    parameter TXEnable = 1;

          wire  Net_289;
          wire  Net_61;
          wire  Net_9;


	cy_isr_v1_0
		#(.int_type(2'b10))
		TXInternalInterrupt
		 (.int_signal(tx_interrupt));



	cy_clock_v1_0
		#(.id("17328a08-5448-4370-829c-00e8367fa784/be0a0e37-ad17-42ca-b5a1-1a654d736358"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("542534722.222222"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_9));


	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_61 = Net_9;

    B_UART_v2_50 BUART (
        .cts_n(cts_n),
        .tx(tx),
        .rts_n(rts_n),
        .tx_en(tx_en),
        .clock(Net_61),
        .reset(reset),
        .rx(rx),
        .tx_interrupt(tx_interrupt),
        .rx_interrupt(rx_interrupt),
        .tx_data(tx_data),
        .tx_clk(tx_clk),
        .rx_data(rx_data),
        .rx_clk(rx_clk));
    defparam BUART.Address1 = 0;
    defparam BUART.Address2 = 0;
    defparam BUART.BreakBitsRX = 13;
    defparam BUART.BreakBitsTX = 13;
    defparam BUART.BreakDetect = 0;
    defparam BUART.CRCoutputsEn = 0;
    defparam BUART.FlowControl = 0;
    defparam BUART.HalfDuplexEn = 0;
    defparam BUART.HwTXEnSignal = 0;
    defparam BUART.NumDataBits = 8;
    defparam BUART.NumStopBits = 1;
    defparam BUART.OverSampleCount = 8;
    defparam BUART.ParityType = 0;
    defparam BUART.ParityTypeSw = 0;
    defparam BUART.RXAddressMode = 0;
    defparam BUART.RXEnable = 1;
    defparam BUART.RXStatusIntEnable = 1;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



endmodule

// Component: cy_constant_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_constant_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_constant_v1_0\cy_constant_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_constant_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_constant_v1_0\cy_constant_v1_0.v"
`endif

// Component: demux_v1_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10\demux_v1_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10\demux_v1_10.v"
`endif

// Component: CyControlReg_v1_80
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80\CyControlReg_v1_80.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80\CyControlReg_v1_80.v"
`endif

// Component: mux_v1_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\mux_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\mux_v1_10\mux_v1_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\mux_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\mux_v1_10\mux_v1_10.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Timer_v2_80(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=false, CaptureMode=0, CONTROL3=1, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeviceFamily=PSoC5, EnableMode=0, FF16=true, FF8=false, FixedFunction=true, FixedFunctionUsed=1, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=true, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=1, NumberOfCaptures=1, param45=1, Period=479, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=0, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=false, UDB8=false, UDBControlReg=false, UsesHWEnable=0, VerilogSectionReplacementString=sT16, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=Timer_v2_80, CY_CONFIG_TITLE=Timer_20ms, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Timer_20ms, CY_INSTANCE_SHORT_NAME=Timer_20ms, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=80, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.3, INSTANCE_NAME=Timer_20ms, )
module Timer_v2_80_1 (
    reset,
    interrupt,
    enable,
    trigger,
    capture,
    capture_out,
    tc,
    clock);
    input       reset;
    output      interrupt;
    input       enable;
    input       trigger;
    input       capture;
    output      capture_out;
    output      tc;
    input       clock;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC5";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 1;
    parameter Resolution = 16;
    parameter SiliconRevision = "0";

          wire  Net_261;
          wire  Net_260;
          wire  Net_266;
          wire  Net_102;
          wire  Net_55;
          wire  Net_57;
          wire  Net_53;
          wire  Net_51;

    cy_psoc3_timer_v1_0 TimerHW (
        .timer_reset(reset),
        .capture(capture),
        .enable(Net_266),
        .kill(Net_260),
        .clock(clock),
        .tc(Net_51),
        .compare(Net_261),
        .interrupt(Net_57));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_57;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_51;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// Timer_v2_80(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=false, CaptureMode=0, CONTROL3=1, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeviceFamily=PSoC5, EnableMode=0, FF16=true, FF8=false, FixedFunction=true, FixedFunctionUsed=1, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=true, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=1, NumberOfCaptures=1, param45=1, Period=239, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=0, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=false, UDB8=false, UDBControlReg=false, UsesHWEnable=0, VerilogSectionReplacementString=sT16, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=Timer_v2_80, CY_CONFIG_TITLE=Timer_10ms, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Timer_10ms, CY_INSTANCE_SHORT_NAME=Timer_10ms, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=80, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.3, INSTANCE_NAME=Timer_10ms, )
module Timer_v2_80_2 (
    reset,
    interrupt,
    enable,
    trigger,
    capture,
    capture_out,
    tc,
    clock);
    input       reset;
    output      interrupt;
    input       enable;
    input       trigger;
    input       capture;
    output      capture_out;
    output      tc;
    input       clock;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC5";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 1;
    parameter Resolution = 16;
    parameter SiliconRevision = "0";

          wire  Net_261;
          wire  Net_260;
          wire  Net_266;
          wire  Net_102;
          wire  Net_55;
          wire  Net_57;
          wire  Net_53;
          wire  Net_51;

    cy_psoc3_timer_v1_0 TimerHW (
        .timer_reset(reset),
        .capture(capture),
        .enable(Net_266),
        .kill(Net_260),
        .clock(clock),
        .tc(Net_51),
        .compare(Net_261),
        .interrupt(Net_57));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_57;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_51;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// UART_v2_50(Address1=0, Address2=0, BaudRate=460800, BreakBitsRX=13, BreakBitsTX=13, BreakDetect=false, CRCoutputsEn=false, Enable_RX=1, Enable_RXIntInterrupt=0, Enable_TX=1, Enable_TXIntInterrupt=0, EnableHWAddress=0, EnIntRXInterrupt=false, EnIntTXInterrupt=false, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=true, InternalClock=true, InternalClockToleranceMinus=3.93736842105263, InternalClockTolerancePlus=3.93736842105263, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=1, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=false, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=true, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, ParityTypeSw=false, RequiredClock=3686400, RXAddressMode=0, RXBufferSize=4, RxBuffRegSizeReplacementString=uint8, RXEnable=true, TXBitClkGenDP=true, TXBufferSize=4, TxBuffRegSizeReplacementString=uint8, TXEnable=true, Use23Polling=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=UART_v2_50, CY_CONFIG_TITLE=UART_460800, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=UART_460800, CY_INSTANCE_SHORT_NAME=UART_460800, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=50, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.3, INSTANCE_NAME=UART_460800, )
module UART_v2_50_3 (
    cts_n,
    tx,
    rts_n,
    tx_en,
    clock,
    reset,
    rx,
    tx_interrupt,
    rx_interrupt,
    tx_data,
    tx_clk,
    rx_data,
    rx_clk);
    input       cts_n;
    output      tx;
    output      rts_n;
    output      tx_en;
    input       clock;
    input       reset;
    input       rx;
    output      tx_interrupt;
    output      rx_interrupt;
    output      tx_data;
    output      tx_clk;
    output      rx_data;
    output      rx_clk;

    parameter Address1 = 0;
    parameter Address2 = 0;
    parameter EnIntRXInterrupt = 0;
    parameter EnIntTXInterrupt = 0;
    parameter FlowControl = 0;
    parameter HalfDuplexEn = 0;
    parameter HwTXEnSignal = 1;
    parameter NumDataBits = 8;
    parameter NumStopBits = 1;
    parameter ParityType = 0;
    parameter RXEnable = 1;
    parameter TXEnable = 1;

          wire  Net_289;
          wire  Net_61;
          wire  Net_9;


	cy_clock_v1_0
		#(.id("4077b64b-d620-4b8a-8d11-e1807acbf68d/be0a0e37-ad17-42ca-b5a1-1a654d736358"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("271267361.111111"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_9));


	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_61 = Net_9;

    B_UART_v2_50 BUART (
        .cts_n(cts_n),
        .tx(tx),
        .rts_n(rts_n),
        .tx_en(tx_en),
        .clock(Net_61),
        .reset(reset),
        .rx(rx),
        .tx_interrupt(tx_interrupt),
        .rx_interrupt(rx_interrupt),
        .tx_data(tx_data),
        .tx_clk(tx_clk),
        .rx_data(rx_data),
        .rx_clk(rx_clk));
    defparam BUART.Address1 = 0;
    defparam BUART.Address2 = 0;
    defparam BUART.BreakBitsRX = 13;
    defparam BUART.BreakBitsTX = 13;
    defparam BUART.BreakDetect = 0;
    defparam BUART.CRCoutputsEn = 0;
    defparam BUART.FlowControl = 0;
    defparam BUART.HalfDuplexEn = 0;
    defparam BUART.HwTXEnSignal = 1;
    defparam BUART.NumDataBits = 8;
    defparam BUART.NumStopBits = 1;
    defparam BUART.OverSampleCount = 8;
    defparam BUART.ParityType = 0;
    defparam BUART.ParityTypeSw = 0;
    defparam BUART.RXAddressMode = 0;
    defparam BUART.RXEnable = 1;
    defparam BUART.RXStatusIntEnable = 1;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



endmodule

// Timer_v2_80(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=false, CaptureMode=0, CONTROL3=1, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeviceFamily=PSoC5, EnableMode=0, FF16=true, FF8=false, FixedFunction=true, FixedFunctionUsed=1, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=true, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=1, NumberOfCaptures=1, param45=1, Period=1199, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=0, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=false, UDB8=false, UDBControlReg=false, UsesHWEnable=0, VerilogSectionReplacementString=sT16, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=Timer_v2_80, CY_CONFIG_TITLE=Timer_50ms, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Timer_50ms, CY_INSTANCE_SHORT_NAME=Timer_50ms, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=80, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.3, INSTANCE_NAME=Timer_50ms, )
module Timer_v2_80_4 (
    reset,
    interrupt,
    enable,
    trigger,
    capture,
    capture_out,
    tc,
    clock);
    input       reset;
    output      interrupt;
    input       enable;
    input       trigger;
    input       capture;
    output      capture_out;
    output      tc;
    input       clock;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC5";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 1;
    parameter Resolution = 16;
    parameter SiliconRevision = "0";

          wire  Net_261;
          wire  Net_260;
          wire  Net_266;
          wire  Net_102;
          wire  Net_55;
          wire  Net_57;
          wire  Net_53;
          wire  Net_51;

    cy_psoc3_timer_v1_0 TimerHW (
        .timer_reset(reset),
        .capture(capture),
        .enable(Net_266),
        .kill(Net_260),
        .clock(clock),
        .tc(Net_51),
        .compare(Net_261),
        .interrupt(Net_57));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_57;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_51;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// top
module top ;

          wire  Net_6271;
          wire  Net_6270;
          wire  Net_6269;
          wire  Net_6268;
          wire  Net_6267;
          wire  Net_6266;
          wire  Net_6256;
          wire [1:0] mywire_5;
          wire [1:0] mywire_2;
          wire  Net_6220;
          wire  Net_6219;
          wire  Net_6218;
          wire  Net_6217;
          wire  Net_6216;
          wire  Net_6215;
          wire  Net_6257;
          wire  Net_6214;
          wire  Net_6213;
          wire  Net_6212;
          wire  Net_6253;
          wire  Net_6211;
          wire  Net_6210;
          wire  Net_6252;
          wire  Net_6255;
          wire  Net_6254;
          wire  Net_6209;
          wire  Net_6208;
          wire  Net_6207;
          wire  Net_6206;
          wire  Net_6205;
          wire  Net_6204;
          wire  Net_6225;
          wire  Net_6224;
          wire  Net_6223;
          wire  Net_6222;
          wire  Net_6203;
          wire  Net_6202;
          wire  Net_6201;
          wire  Net_6200;
          wire  Net_6199;
          wire  Net_6198;
          wire  Net_6197;
          wire  Net_6196;
          wire  Net_6237;
          wire  Net_6193;
          wire  Net_6192;
          wire  Net_6191;
          wire  Net_6190;
          wire  Net_6189;
          wire  Net_6188;
          wire  Net_6187;
          wire  Net_6186;
          wire  Net_6185;
          wire  Net_6184;
          wire  Net_6183;
          wire  Net_6155;
          wire  Net_6154;
          wire  Net_6153;
          wire  Net_6152;
          wire  Net_6151;
          wire  Net_6150;
          wire  Net_6134;
          wire  Net_6133;
          wire  Net_6132;
          wire  Net_6131;
          wire  Net_6130;
          wire  Net_6163;
          wire  Net_6136;
          wire  Net_6048;
          wire  Net_6045;
          wire  Net_6145;
          wire  Net_6040;
          wire  Net_6039;
          wire  Net_6038;
          wire  Net_6037;
          wire  Net_6036;
          wire  Net_6035;
          wire  Net_6033;
          wire  Net_6032;
          wire  Net_6031;
          wire  Net_5869;
          wire  Net_5868;
          wire  Net_5867;
          wire  Net_5866;
          wire  Net_5865;
          wire  Net_5864;
          wire  Net_5975;
          wire  Net_5862;
          wire  Net_5861;
          wire  Net_5859;
          wire  Net_6162;
          wire  Net_5850;
          wire  Net_5846;
          wire  Net_5845;
          wire  Net_5844;
          wire  Net_5843;
          wire  Net_5842;
          wire  Net_5841;
          wire  Net_5840;
          wire  Net_5973;
          wire  Net_5838;
          wire  Net_5837;
          wire  Net_5839;
          wire  Net_5849;
          wire  Net_5997;
          wire  Net_5985;
          wire  Net_6230;
          wire  Net_6121;
          wire  Net_5995;
          wire  Net_5994;
          wire  Net_5993;
          wire  Net_5992;
          wire  Net_5991;
          wire  Net_5990;
          wire  Net_5989;
          wire  Net_5988;
          wire  Net_5987;
          wire  Net_5986;
          wire  Net_5778;
          wire  Net_5777;
          wire  Net_5776;
          wire  Net_5775;
          wire  Net_5774;
          wire [3:0] mywire_1;
          wire  Net_5773;
          wire  Net_822;
          wire  Net_5772;
          wire  Net_5771;
          wire  Net_5770;
          wire  Net_5769;
          wire  Net_6243;
          wire  Net_5767;
          wire  Net_5765;
          wire  Net_5764;
          wire  Net_5763;
          wire  Net_5762;
          wire  Net_5761;
          wire  Net_191;
          wire  Net_5760;
          wire  Net_5759;
          wire  Net_5758;
          wire  Net_5757;
          wire  Net_144;
          wire  Net_5756;
          wire  Net_6013;
          wire  Net_6012;
          wire  Net_6011;
          wire  Net_6010;
          wire  Net_6009;
          wire  Net_6008;
          wire  Net_6007;
          wire  Net_6006;
          wire  Net_6005;
          wire  Net_6004;
          wire  Net_163;
          wire  Net_5983;
          wire  Net_6002;
          wire  Net_6000;
          wire  Net_6001;
          wire  Net_6244;
          wire  Net_5747;
          wire  Net_5746;
          wire  Net_5745;
          wire  Net_5744;
          wire  Net_5742;
          wire  Net_5741;
          wire  Net_5740;
          wire  Net_5739;
          wire  Net_5738;
          wire  Net_5737;
          wire  Net_6169;
          wire  Net_6276;
          wire  Net_6278;
          wire  Net_5971;
          wire  Net_6277;
          wire  Net_6167;
          wire  Net_6241;
          wire  Net_6170;
          wire  Net_6168;
          wire  Net_6161;
          wire  Net_5858;
          wire  Net_5854;
          wire  Net_5853;
          wire  Net_6016;
          wire  Net_5857;
          wire  Net_6003;
          wire [1:0] Net_5612;
          wire  Net_6017;
          wire  Net_5623;
          wire  Net_5610;
          wire  Net_5518;
          wire  Net_10;
          wire  Net_12;
          wire  Net_568;
          wire  Net_6050;
          wire  Net_5743;
          wire [1:0] Net_5977;
          wire [1:0] Net_5974;
          wire  Net_179;


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_UART_230400
		 (.int_signal(Net_5743));


    UART_v2_50_0 UART_230400 (
        .cts_n(1'b0),
        .tx(Net_6003),
        .rts_n(Net_5738),
        .tx_en(Net_5739),
        .clock(1'b0),
        .reset(Net_5741),
        .rx(Net_568),
        .tx_interrupt(Net_5742),
        .rx_interrupt(Net_5743),
        .tx_data(Net_5744),
        .tx_clk(Net_5745),
        .rx_data(Net_5746),
        .rx_clk(Net_5747));
    defparam UART_230400.Address1 = 0;
    defparam UART_230400.Address2 = 0;
    defparam UART_230400.EnIntRXInterrupt = 0;
    defparam UART_230400.EnIntTXInterrupt = 1;
    defparam UART_230400.FlowControl = 0;
    defparam UART_230400.HalfDuplexEn = 0;
    defparam UART_230400.HwTXEnSignal = 0;
    defparam UART_230400.NumDataBits = 8;
    defparam UART_230400.NumStopBits = 1;
    defparam UART_230400.ParityType = 0;
    defparam UART_230400.RXEnable = 1;
    defparam UART_230400.TXEnable = 1;

    assign Net_5741 = 1'h0;

    // -- De Mux start --
    if (1)
    begin : DEMUX_230400
        reg  tmp__DEMUX_230400_0_reg;
        reg  tmp__DEMUX_230400_1_reg;
        reg  tmp__DEMUX_230400_2_reg;
        reg  tmp__DEMUX_230400_3_reg;
        always @(Net_6003 or Net_5977)
        begin
            case (Net_5977[1:0])
                2'b00:
                begin
                    tmp__DEMUX_230400_0_reg = Net_6003;
                    tmp__DEMUX_230400_1_reg = 1'b0;
                    tmp__DEMUX_230400_2_reg = 1'b0;
                    tmp__DEMUX_230400_3_reg = 1'b0;
                end
                2'b01:
                begin
                    tmp__DEMUX_230400_0_reg = 1'b0;
                    tmp__DEMUX_230400_1_reg = Net_6003;
                    tmp__DEMUX_230400_2_reg = 1'b0;
                    tmp__DEMUX_230400_3_reg = 1'b0;
                end
                2'b10:
                begin
                    tmp__DEMUX_230400_0_reg = 1'b0;
                    tmp__DEMUX_230400_1_reg = 1'b0;
                    tmp__DEMUX_230400_2_reg = Net_6003;
                    tmp__DEMUX_230400_3_reg = 1'b0;
                end
                2'b11:
                begin
                    tmp__DEMUX_230400_0_reg = 1'b0;
                    tmp__DEMUX_230400_1_reg = 1'b0;
                    tmp__DEMUX_230400_2_reg = 1'b0;
                    tmp__DEMUX_230400_3_reg = Net_6003;
                end
            endcase
        end
        assign Net_6244 = tmp__DEMUX_230400_0_reg;
        assign Net_6001 = tmp__DEMUX_230400_1_reg;
        assign Net_6000 = tmp__DEMUX_230400_2_reg;
        assign Net_6002 = tmp__DEMUX_230400_3_reg;
    end
    // -- De Mux end --

    CyControlReg_v1_80 DEMUX_CTRL_230400 (
        .control_1(Net_6004),
        .control_2(Net_6005),
        .control_3(Net_6006),
        .control_0(Net_6007),
        .control_4(Net_6008),
        .control_5(Net_6009),
        .control_6(Net_6010),
        .control_7(Net_6011),
        .clock(1'b0),
        .reset(1'b0),
        .control_bus(Net_5977[1:0]));
    defparam DEMUX_CTRL_230400.Bit0Mode = 0;
    defparam DEMUX_CTRL_230400.Bit1Mode = 0;
    defparam DEMUX_CTRL_230400.Bit2Mode = 0;
    defparam DEMUX_CTRL_230400.Bit3Mode = 0;
    defparam DEMUX_CTRL_230400.Bit4Mode = 0;
    defparam DEMUX_CTRL_230400.Bit5Mode = 0;
    defparam DEMUX_CTRL_230400.Bit6Mode = 0;
    defparam DEMUX_CTRL_230400.Bit7Mode = 0;
    defparam DEMUX_CTRL_230400.BitValue = 0;
    defparam DEMUX_CTRL_230400.BusDisplay = 1;
    defparam DEMUX_CTRL_230400.ExtrReset = 0;
    defparam DEMUX_CTRL_230400.NumOutputs = 2;

    CyControlReg_v1_80 MUX_CTRL_230400 (
        .control_1(Net_5986),
        .control_2(Net_5987),
        .control_3(Net_5988),
        .control_0(Net_5989),
        .control_4(Net_5990),
        .control_5(Net_5991),
        .control_6(Net_5992),
        .control_7(Net_5993),
        .clock(1'b0),
        .reset(1'b0),
        .control_bus(Net_5974[1:0]));
    defparam MUX_CTRL_230400.Bit0Mode = 0;
    defparam MUX_CTRL_230400.Bit1Mode = 0;
    defparam MUX_CTRL_230400.Bit2Mode = 0;
    defparam MUX_CTRL_230400.Bit3Mode = 0;
    defparam MUX_CTRL_230400.Bit4Mode = 0;
    defparam MUX_CTRL_230400.Bit5Mode = 0;
    defparam MUX_CTRL_230400.Bit6Mode = 0;
    defparam MUX_CTRL_230400.Bit7Mode = 0;
    defparam MUX_CTRL_230400.BitValue = 0;
    defparam MUX_CTRL_230400.BusDisplay = 1;
    defparam MUX_CTRL_230400.ExtrReset = 0;
    defparam MUX_CTRL_230400.NumOutputs = 2;

    // -- Mux start --
    if (1)
    begin : MUX_230400
        reg  tmp__MUX_230400_reg;
        always @(Net_6230 or Net_5974)
        begin
            case (Net_5974[1:0])
                2'b00 :  tmp__MUX_230400_reg = 1'b0;
                2'b01 :  tmp__MUX_230400_reg = Net_6230;
                2'b10 :  tmp__MUX_230400_reg = 1'b0;
                2'b11 :  tmp__MUX_230400_reg = 1'b0;
            endcase
        end
        assign Net_568 = tmp__MUX_230400_reg;
    end
    // -- Mux end --

	wire [0:0] tmpOE__RS485_RX_EN_net;
	wire [0:0] tmpFB_0__RS485_RX_EN_net;
	wire [0:0] tmpIO_0__RS485_RX_EN_net;
	wire [0:0] tmpINTERRUPT_0__RS485_RX_EN_net;
	electrical [0:0] tmpSIOVREF__RS485_RX_EN_net;

	cy_psoc3_pins_v1_10
		#(.id("e851a3b9-efb8-48be-bbb8-b303b216c393"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		RS485_RX_EN
		 (.oe(tmpOE__RS485_RX_EN_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__RS485_RX_EN_net[0:0]}),
		  .io({tmpIO_0__RS485_RX_EN_net[0:0]}),
		  .siovref(tmpSIOVREF__RS485_RX_EN_net),
		  .interrupt({tmpINTERRUPT_0__RS485_RX_EN_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__RS485_RX_EN_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("c0fb34bd-1044-4931-9788-16b01ce89812"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("41666666666.6667"),
		  .is_direct(0),
		  .is_digital(1))
		timer_clock
		 (.clock_out(Net_10));


    ZeroTerminal ZeroTerminal_1 (
        .z(Net_12));

    Timer_v2_80_1 Timer_20ms (
        .reset(Net_12),
        .interrupt(Net_6163),
        .enable(1'b1),
        .trigger(1'b1),
        .capture(1'b0),
        .capture_out(Net_6133),
        .tc(Net_6134),
        .clock(Net_10));
    defparam Timer_20ms.CaptureCount = 2;
    defparam Timer_20ms.CaptureCounterEnabled = 0;
    defparam Timer_20ms.DeviceFamily = "PSoC5";
    defparam Timer_20ms.InterruptOnCapture = 0;
    defparam Timer_20ms.InterruptOnTC = 1;
    defparam Timer_20ms.Resolution = 16;
    defparam Timer_20ms.SiliconRevision = "0";

	wire [0:0] tmpOE__LED_EN_net;
	wire [0:0] tmpFB_0__LED_EN_net;
	wire [0:0] tmpIO_0__LED_EN_net;
	wire [0:0] tmpINTERRUPT_0__LED_EN_net;
	electrical [0:0] tmpSIOVREF__LED_EN_net;

	cy_psoc3_pins_v1_10
		#(.id("86969b19-12ee-431b-979f-f6172fe2f363"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		LED_EN
		 (.oe(tmpOE__LED_EN_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__LED_EN_net[0:0]}),
		  .io({tmpIO_0__LED_EN_net[0:0]}),
		  .siovref(tmpSIOVREF__LED_EN_net),
		  .interrupt({tmpINTERRUPT_0__LED_EN_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__LED_EN_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_Timer_20ms
		 (.int_signal(Net_6134));


    Timer_v2_80_2 Timer_10ms (
        .reset(Net_12),
        .interrupt(Net_6150),
        .enable(1'b1),
        .trigger(1'b1),
        .capture(1'b0),
        .capture_out(Net_6154),
        .tc(Net_6155),
        .clock(Net_10));
    defparam Timer_10ms.CaptureCount = 2;
    defparam Timer_10ms.CaptureCounterEnabled = 0;
    defparam Timer_10ms.DeviceFamily = "PSoC5";
    defparam Timer_10ms.InterruptOnCapture = 0;
    defparam Timer_10ms.InterruptOnTC = 1;
    defparam Timer_10ms.Resolution = 16;
    defparam Timer_10ms.SiliconRevision = "0";


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_Timer_10ms
		 (.int_signal(Net_6155));


	wire [0:0] tmpOE__DIAG_UART_RX_net;
	wire [0:0] tmpIO_0__DIAG_UART_RX_net;
	wire [0:0] tmpINTERRUPT_0__DIAG_UART_RX_net;
	electrical [0:0] tmpSIOVREF__DIAG_UART_RX_net;

	cy_psoc3_pins_v1_10
		#(.id("8d318d8b-cf7b-4b6b-b02c-ab1c5c49d0ba"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		DIAG_UART_RX
		 (.oe(tmpOE__DIAG_UART_RX_net),
		  .y({1'b0}),
		  .fb({Net_6230}),
		  .io({tmpIO_0__DIAG_UART_RX_net[0:0]}),
		  .siovref(tmpSIOVREF__DIAG_UART_RX_net),
		  .interrupt({tmpINTERRUPT_0__DIAG_UART_RX_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__DIAG_UART_RX_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__DIAG_UART_TX_net;
	wire [0:0] tmpFB_0__DIAG_UART_TX_net;
	wire [0:0] tmpIO_0__DIAG_UART_TX_net;
	wire [0:0] tmpINTERRUPT_0__DIAG_UART_TX_net;
	electrical [0:0] tmpSIOVREF__DIAG_UART_TX_net;

	cy_psoc3_pins_v1_10
		#(.id("2ea4b42a-7f67-4d70-a186-5b62b51aed18"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		DIAG_UART_TX
		 (.oe(tmpOE__DIAG_UART_TX_net),
		  .y({Net_6000}),
		  .fb({tmpFB_0__DIAG_UART_TX_net[0:0]}),
		  .io({tmpIO_0__DIAG_UART_TX_net[0:0]}),
		  .siovref(tmpSIOVREF__DIAG_UART_TX_net),
		  .interrupt({tmpINTERRUPT_0__DIAG_UART_TX_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__DIAG_UART_TX_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b00))
		isr_UART_460800
		 (.int_signal(Net_5623));


    UART_v2_50_3 UART_460800 (
        .cts_n(1'b0),
        .tx(Net_5610),
        .rts_n(Net_6184),
        .tx_en(Net_6185),
        .clock(1'b0),
        .reset(Net_6187),
        .rx(Net_5518),
        .tx_interrupt(Net_6188),
        .rx_interrupt(Net_5623),
        .tx_data(Net_6189),
        .tx_clk(Net_6190),
        .rx_data(Net_6191),
        .rx_clk(Net_6192));
    defparam UART_460800.Address1 = 0;
    defparam UART_460800.Address2 = 0;
    defparam UART_460800.EnIntRXInterrupt = 0;
    defparam UART_460800.EnIntTXInterrupt = 0;
    defparam UART_460800.FlowControl = 0;
    defparam UART_460800.HalfDuplexEn = 0;
    defparam UART_460800.HwTXEnSignal = 1;
    defparam UART_460800.NumDataBits = 8;
    defparam UART_460800.NumStopBits = 1;
    defparam UART_460800.ParityType = 0;
    defparam UART_460800.RXEnable = 1;
    defparam UART_460800.TXEnable = 1;

    // -- Mux start --
    if (1)
    begin : mux_1
        reg  tmp__mux_1_reg;
        always @(Net_6017 or Net_6017 or Net_6017 or Net_6017 or Net_6017 or Net_6017 or mywire_1)
        begin
            case (mywire_1[3:0])
                4'b0000 :  tmp__mux_1_reg = 1'b0;
                4'b0001 :  tmp__mux_1_reg = 1'b0;
                4'b0010 :  tmp__mux_1_reg = 1'b0;
                4'b0011 :  tmp__mux_1_reg = 1'b0;
                4'b0100 :  tmp__mux_1_reg = 1'b0;
                4'b0101 :  tmp__mux_1_reg = 1'b0;
                4'b0110 :  tmp__mux_1_reg = 1'b0;
                4'b0111 :  tmp__mux_1_reg = 1'b0;
                4'b1000 :  tmp__mux_1_reg = 1'b0;
                4'b1001 :  tmp__mux_1_reg = 1'b0;
                4'b1010 :  tmp__mux_1_reg = Net_6017;
                4'b1011 :  tmp__mux_1_reg = Net_6017;
                4'b1100 :  tmp__mux_1_reg = Net_6017;
                4'b1101 :  tmp__mux_1_reg = Net_6017;
                4'b1110 :  tmp__mux_1_reg = Net_6017;
                4'b1111 :  tmp__mux_1_reg = Net_6017;
            endcase
        end
        assign Net_5518 = tmp__mux_1_reg;
    end
    // -- Mux end --

    assign Net_6187 = 1'h0;

    CyControlReg_v1_80 MUX_CTRL_460800 (
        .control_1(Net_6222),
        .control_2(Net_6223),
        .control_3(Net_6224),
        .control_0(Net_6225),
        .control_4(Net_6204),
        .control_5(Net_6205),
        .control_6(Net_6206),
        .control_7(Net_6207),
        .clock(1'b0),
        .reset(1'b0),
        .control_bus(mywire_1[3:0]));
    defparam MUX_CTRL_460800.Bit0Mode = 0;
    defparam MUX_CTRL_460800.Bit1Mode = 0;
    defparam MUX_CTRL_460800.Bit2Mode = 0;
    defparam MUX_CTRL_460800.Bit3Mode = 0;
    defparam MUX_CTRL_460800.Bit4Mode = 0;
    defparam MUX_CTRL_460800.Bit5Mode = 0;
    defparam MUX_CTRL_460800.Bit6Mode = 0;
    defparam MUX_CTRL_460800.Bit7Mode = 0;
    defparam MUX_CTRL_460800.BitValue = 0;
    defparam MUX_CTRL_460800.BusDisplay = 1;
    defparam MUX_CTRL_460800.ExtrReset = 0;
    defparam MUX_CTRL_460800.NumOutputs = 4;

    assign Net_6017 = 1'h0;

    // -- De Mux start --
    if (1)
    begin : demux_1
        reg  tmp__demux_1_0_reg;
        reg  tmp__demux_1_1_reg;
        reg  tmp__demux_1_2_reg;
        reg  tmp__demux_1_3_reg;
        always @(Net_5610 or Net_5612)
        begin
            case (Net_5612[1:0])
                2'b00:
                begin
                    tmp__demux_1_0_reg = Net_5610;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                end
                2'b01:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = Net_5610;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                end
                2'b10:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = Net_5610;
                    tmp__demux_1_3_reg = 1'b0;
                end
                2'b11:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = Net_5610;
                end
            endcase
        end
        assign Net_6252 = tmp__demux_1_0_reg;
        assign Net_6210 = tmp__demux_1_1_reg;
        assign Net_6211 = tmp__demux_1_2_reg;
        assign Net_6253 = tmp__demux_1_3_reg;
    end
    // -- De Mux end --

    CyControlReg_v1_80 DEMUX_CTRL_460800 (
        .control_1(Net_6212),
        .control_2(Net_6213),
        .control_3(Net_6214),
        .control_0(Net_6257),
        .control_4(Net_6215),
        .control_5(Net_6216),
        .control_6(Net_6217),
        .control_7(Net_6218),
        .clock(1'b0),
        .reset(1'b0),
        .control_bus(Net_5612[1:0]));
    defparam DEMUX_CTRL_460800.Bit0Mode = 0;
    defparam DEMUX_CTRL_460800.Bit1Mode = 0;
    defparam DEMUX_CTRL_460800.Bit2Mode = 0;
    defparam DEMUX_CTRL_460800.Bit3Mode = 0;
    defparam DEMUX_CTRL_460800.Bit4Mode = 0;
    defparam DEMUX_CTRL_460800.Bit5Mode = 0;
    defparam DEMUX_CTRL_460800.Bit6Mode = 0;
    defparam DEMUX_CTRL_460800.Bit7Mode = 0;
    defparam DEMUX_CTRL_460800.BitValue = 0;
    defparam DEMUX_CTRL_460800.BusDisplay = 1;
    defparam DEMUX_CTRL_460800.ExtrReset = 0;
    defparam DEMUX_CTRL_460800.NumOutputs = 2;

    Timer_v2_80_4 Timer_50ms (
        .reset(Net_12),
        .interrupt(Net_6266),
        .enable(1'b1),
        .trigger(1'b1),
        .capture(1'b0),
        .capture_out(Net_6270),
        .tc(Net_6271),
        .clock(Net_10));
    defparam Timer_50ms.CaptureCount = 2;
    defparam Timer_50ms.CaptureCounterEnabled = 0;
    defparam Timer_50ms.DeviceFamily = "PSoC5";
    defparam Timer_50ms.InterruptOnCapture = 0;
    defparam Timer_50ms.InterruptOnTC = 1;
    defparam Timer_50ms.Resolution = 16;
    defparam Timer_50ms.SiliconRevision = "0";


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_Timer_50ms
		 (.int_signal(Net_6271));




endmodule

