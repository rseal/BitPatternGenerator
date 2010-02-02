////////////////////////////////////////////////////////////////////////////////
///\file ControlStatus.h
///
///The ControlStatus class performs communication with the FPGA. A number of 
///methods are provided to control the FPGA and also receive its status.
///
///Author: Ryan Seal
///Modified: 07/06/2007
////////////////////////////////////////////////////////////////////////////////

#ifndef CONTROL_STATUS_H
#define CONTROL_STATUS_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <sthread/SThread.hpp>
#include <bitset>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
///\brief Communicates control and status information between the host PC and 
///the FPGA.
////////////////////////////////////////////////////////////////////////////////
class ControlStatus: public SThread {
    
    typedef std::bitset<16> BitArray;

    okCUsbFrontPanel& okFrontPanel_;
    int updateRate_;
    bool reset1_;
    bool reset2_;
    bool start1_;
    bool start2_;
    bool stop1_;
    bool stop2_;
    int  sync_;
    int  clkSource_;
    bool activeBuffer1_;
    bool activeBuffer2_;
    bool preload1_;
    bool preload2_;
    bool loadComplete1_;
    bool loadComplete2_;
    bool ready1_;
    bool ready2_;
    bool active1_;
    bool active2_;
    int& exit_;
    BitArray status1_;
    BitArray status2_;
    BitArray control_;
    Mutex& mutex_;

///Writes Control words to the FPGA
    void SendControl(const BitArray& bitArray){
	ScopedLock Lock(mutex_);
	okFrontPanel_.SetWireInValue(CONTROL, bitArray.to_ulong());
	okFrontPanel_.UpdateWireIns();
// 	std::cout << std::hex;
// 	std::cout << "sent 0x" << bitArray.to_ulong() << std::endl;
// 	std::cout << std::dec;
    }
    
    
//////////////////////////////////////////////////////////////////////////////////
/// Reads status register for both ports and assigns them to the proper variables
/// allowing for individual status checks through a number of class methods
//////////////////////////////////////////////////////////////////////////////////
    void ParseStatus(){
	activeBuffer1_ = status1_[0];
	preload1_      = status1_[1];
	loadComplete1_ = status1_[2];
	active1_       = status1_[3];
	ready1_        = status1_[4];
    
	activeBuffer2_ = status2_[0];
	preload2_      = status2_[1];
	loadComplete2_ = status2_[2];
	active2_       = status2_[3];
	ready2_        = status2_[4];
    }

public:    

/// Constructor to initialize control and status variables
/// okCUsbFrontPanel is passed by reference and provides 
/// the interface with the FPGA
    ControlStatus(okCUsbFrontPanel& okFrontPanel, int& exit, Mutex& mutex): 
	okFrontPanel_(okFrontPanel), updateRate_(10), exit_(exit),
	reset1_(0), reset2_(0), start1_(0), start2_(0), stop1_(0),
	stop2_(0), sync_(0), clkSource_(0), activeBuffer1_(0),
	activeBuffer2_(0), preload1_(0), preload2_(0),
	loadComplete1_(0), loadComplete2_(0), ready1_(0), ready2_(0),
	active1_(0), active2_(0), control_(0), mutex_(mutex)
	{}

/// Reset and initialize the FPGA - also start a thread to read the status
    void Initialize(){
	Control(RESET, PORTAB, CLEAR);
  	usleep(50000);
 	Control(RESET, PORTAB, SET);
	SThread::Start();
    }

/// Creates a seperate thread to update the status word from the 
/// FPGA. This function sleeps for a user specified time to alleviate
/// CPU usage.
virtual void Run() {
    
    static int oldStat1 =0;
    while(!exit_){

	mutex_.Lock();
	okFrontPanel_.UpdateWireOuts();
	status1_ = okFrontPanel_.GetWireOutValue(STATUS1);
	status2_ = okFrontPanel_.GetWireOutValue(STATUS2);		    
	ParseStatus();
	mutex_.Unlock();

	this->Sleep(sthread::msec, updateRate_);
    }
    std::cout << "thread stopped" << std::endl;
}

/// Reset a selected port on the FPGA
const bool Reset(int channelNumber){ 
    return channelNumber == PORTAB ? reset1_ && reset2_ :
	channelNumber == PORTA  ? reset1_ : reset2_;
}
    
/// Starts the loaded mode on the specified PORT
const bool Start(int channelNumber){ 
    return channelNumber == PORTAB ? start1_ && start2_ :
	channelNumber == PORTA  ? start1_ : start2_;
}

/// Returns the active buffer for the specified port
const bool ActiveBuffer(int channelNumber){ 
    return channelNumber == PORTAB ? activeBuffer1_ && activeBuffer2_ :
	channelNumber == PORTA  ? activeBuffer1_ : activeBuffer2_;
}

/// The Preload signal is a status signal sent from the FPGA
/// to alert the host PC that a new buffer is needed.
const bool Preload(int channelNumber){ 
    return channelNumber == PORTAB ? preload1_ && preload2_ :
	channelNumber == PORTA  ? preload1_ : preload2_;
}

/// Tells the host PC that the last mode sent is properly loaded
const bool LoadComplete(int channelNumber){ 
    return channelNumber == PORTAB ? loadComplete1_ && loadComplete2_ :
	channelNumber == PORTA  ? loadComplete1_ : loadComplete2_;
}

/// Ready is set when the FPGA is properly initialized and the first mode
/// has been properly loaded into the system
const bool Ready(int channelNumber){
    return channelNumber == PORTAB ? ready1_ && ready2_ :
	channelNumber == PORTA  ? ready1_ : ready2_;
}

/// Returns true if the specified port is currently active
const bool Active(int channelNumber){
    return channelNumber == PORTAB ? active1_ && active2_ :
	channelNumber == PORTA  ? active1_ : active2_;
}

/// User definable status update rate in milliseconds
void UpdateRate(int updateRate) { updateRate_ = updateRate;}

/// Returns current status update rate in milliseconds
const int& UpdateRate() { return updateRate_;}

/// Returns the specified port's status word
    const int Status(int channelNumber){ 
	return channelNumber == PORTA ?  
	    status1_.to_ulong() :
	    status2_.to_ulong();
    }

/// Select the proper synchronization variable for the system
    /// values are : 1PPS, 10PPS, and EXT
    void Sync(int value){
	switch(value){
	case INT_SYNC:
	    control_.set(6,0);
	    control_.set(7,0);
	    break;
	case PPS1_SYNC:
	    control_.set(6,1);
	    control_.set(7,0);
	    break;
	case PPS10_SYNC:
	    control_.set(6,0);
	    control_.set(7,1);
	    break;
	case EXT_SYNC:
	    control_.set(6,1);
	    control_.set(7,1);
	    break;
	default:
	    std::cerr << "Invalid sync setting: default to INT_SYNC" << std::endl;
	    control_.set(6,0);
	    control_.set(7,0);
	}

	sync_ = value;
	std::bitset<2> temp(value);
	control_.set(6, static_cast<int>(temp[0]));
	control_.set(7, static_cast<int>(temp[1]));
	SendControl(control_);
    }

/// Specify either the standard clock or the drifted version
void ClockSource(const int& value){

    switch(value){
    case STD_CLK:
	control_.set(8,0);
	control_.set(9,0);
	clkSource_ = value;
	break;
    case DRIFTED_CLK:
	control_.set(8,0);
	control_.set(9,1);
	clkSource_ = value;
	break;
    case INT_CLK:
	control_.set(8,1);
	control_.set(9,1);
	clkSource_ = value;
	break;
    default:
	control_.set(8,0);
	control_.set(9,0);
	std::cerr << "Invalid Reference clock setting of " << value << " - default to standard clk " << std::endl;
    }
    SendControl(control_);
};
    

/// Enables/Disables optional DAC connected to PortB
    void UseDAC(const bool& state){
      control_.set(12,static_cast<int>(state));
      SendControl(control_);
    };

/// Enables/Disables coded long pulse phase coding
    void UseCLP(const bool& state){
      control_.set(13, static_cast<int>(state));
      SendControl(control_);
    };


/// Send a control command to the FPGA
void Control(int type, int channelNumber, int value){

    switch(type){

    case RESET:
	switch (channelNumber){
	case PORTAB: 
	    control_.set(0,value);
	    control_.set(1,value);
	    break;
	case PORTA:
	    control_.set(0,value);
	    break;
	case PORTB:
	    control_.set(1,value);
	    break;
	default: 
	    std::cerr << "ControlStatus::Control invalid channelNumber" << std::endl;
	}
	break;
	    
    case START:
	switch (channelNumber){
	case PORTAB: 
	    control_.set(2,value);
	    control_.set(3,value);
	    break;
	case PORTA:
	    control_.set(2,value);
	    break;
	case PORTB:
	    control_.set(3,value);
	    break;
	default: 
	    std::cerr << "ControlStatus::Control invalid channelNumber" << std::endl;
	}
	break;

    case STOP:
	switch (channelNumber){
	case PORTAB: 
	    control_.set(4,value);
	    control_.set(5,value);
	    break;
	case PORTA:
	    control_.set(4,value);
	    break;
	case PORTB:
	    control_.set(5,value);
	    break;
	default: 
	    std::cerr << "ControlStatus::Control invalid channelNumber" << std::endl;
	}
	break;
	
    case SWITCH:
	switch (channelNumber){
	case PORTAB: 
	    control_.set(10,value);
	    control_.set(11,value);
	    break;
	case PORTA:
	    control_.set(10,value);
	    break;
	case PORTB:
	    control_.set(11,value);
	    break;
	default: 
	    std::cerr << "ControlStatus::Control invalid channelNumber" << std::endl;
	}
	break;
    }
    
    SendControl(control_);
}

/// Get the status of various variables for the specified port
const int Status(int type, int channelNumber){
    int result;

    switch(type){
    case RESET: result = channelNumber ? reset1_ : reset2_; break;
    case START: result = channelNumber ? start1_ : start2_; break;
    case STOP:  result = channelNumber ? stop1_  : stop2_; break;
    case SYNC:  result = sync_; break;
    case CLK_SOURCE: result = clkSource_;
    }
	
    return result;
}   
    
/// \enumerate ControlStatus enumerations to better express settings.
enum{PORTA=0, PORTB=1, PORTAB=2};
enum{STATUS1 = 0x20, STATUS2 = 0x21, CONTROL = 0x00};
enum{RESET, START, STOP, SYNC, CLK_SOURCE, SWITCH};
enum{SET=1, CLEAR=0};
enum{INT_CLK=200, STD_CLK=201, DRIFTED_CLK=202};
enum{INT_SYNC=300, EXT_SYNC=301, PPS1_SYNC=302, PPS10_SYNC=303};
};

#endif
