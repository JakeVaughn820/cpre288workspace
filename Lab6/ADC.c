#include <ADC.h>

void init_ADC()
{
// 1. Setup GPIO
 // A) Configure GPIO module associated with ADC
 // i. Turn on clock for GPIO Port E
 SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | 0b010000; // 0x10
 // ii. Enable alternate function
 GPIO_PORTE_AFSEL_R |= 0b00010100; //ADC channels 1&9 on pins 2&4

 // iii. Configure pins for input and analog mode
 GPIO_PORTE_DIR_R &= 0b11101011; //Pins 2 & 4 set to input
 GPIO_PORTE_DEN_R &= 0b11101011; //Disable digital mode pins 2&4
 GPIO_PORTE_AMSEL_R |= 0b00010100; //Enable analog mode pins 2&4
// iv. Use default sample trigger source
// By default, the processor (your program) is selected as the
// trigger source and is initiated by the sample sequencer (SS)
 GPIO_PORTE_ADCCTL_R = 0x0; //Trigger in software
// 2. Setup ADC
 // A) Configure ADC (choose ADC0 or ADC1)
 SYSCTL_RCGCADC_R |= 0x1; // Enable ADC0 clock
 ADC0_ADCCC = 0x0; //Use SysClk as ADC clk. Default, OK if omitted
 // Choose a sample sequencer (SS0, SS1, SS2 or SS3)
 // Disable ADC sample sequencer SS0 while configuring
 // OK to use SS1 or SS2 (cannot use SS3 for multiple samples)
 ADC0_ACTSS_R &= 0xFFFE; //Disable ADC0 SS0 by clearing bit 0

 // Set ADC SS0 functionality
 ADC0_EMUX_R &= 0xFFF0; //Set SS0 to trigger using ADCPSSI reg.
 ADC0_SSMUX0_R |= 0x0000000A; // Sample channel 1, then 9

 // Configure which sample is end of sequence (bit 1 of 4-bit
 // field), after which sample the RIS flag is asserted (bit 2)
 // Use second sample (channel 1 is first, channel 9 is second)
 ADC0_SSCTL0_R = 0x00000000; // First clear register to 0
 ADC0_SSCTL0_R |= 0x00000060 // Set bits 1 and 2 for second sample
 // B) Set up ADC interrupts
 NONE
// 3. Initialize NVIC
4
 // A) Configure NVIC to allow ADC interrupts
 NONE
 // B) Bind ADC interrupt requests to user’s interrupt handler
 NONE
 // Re-enable ADC SS0
 ADC0_ACTSS_R |= 0x1; //Re-enable ADC0 SS0 by setting bit 0
}


int adc_read(void){
    // Initiate SS0 conversion sequence
   ADC0_PSSI_R = 0x1;
   // Wait for SS0 ADC conversions to complete
   while((ADC0_RIS_R & 0x1) == 0) // or (~ADC0_RIS_R & 0x1)
    {
    //wait
    }
   // Clear raw interrupt status flag for SS0
   ADC0_ISC_R = 0x01;
    // Get converted results from SS0 FIFO
    return ADC0_SSFIFO0_R; // Channel 10
};

