#include "nxtpp.h"
#include "nxtppimpl.h"

NxtPP::NxtPP() {
	comm = new Comm::NXTComm;
	connected = false;
}

NxtPP::~NxtPP() {
}

bool NxtPP::create() {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;

	// initialize the NXT and continue if it succeds
    if( !NXT::Open( xcomm ) ) 
		return( false );

	connected = true;
	return( true );
}

void NxtPP::destroy() {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;

	if( connected ) {
		NXT::StopProgram( xcomm );
		NXT::Motor::Stop( xcomm , 0 , true );
		NXT::Motor::Stop( xcomm , 1 , true );
		NXT::Motor::Stop( xcomm , 2 , true );
		NXT::Close( xcomm ); //close the NXT
		connected = false;
	}
}

void NxtPP::motorSetPower( int motor123 , int power100 ) {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;
	if( !connected )
		return;

	if( motor123 < 1 || motor123 > 3 )
		return;

	if( power100 > 0 ) {
		if( power100 > 100 )
			power100 = 100;

		NXT::Motor::SetForward( xcomm , motor123 - 1 , power100 );
	}
	else if( power100 < 0 ) {
		power100 = -power100;
		if( power100 > 100 )
			power100 = 100;

		NXT::Motor::SetReverse( xcomm , motor123 - 1 , power100 );
	}
	else {
		NXT::Motor::Stop( xcomm , motor123 - 1 , false );
	}
}

void NxtPP::motorStop( int motor123 , bool brake ) {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;
	if( !connected )
		return;

	if( motor123 < 1 || motor123 > 3 )
		return;

	NXT::Motor::Stop( xcomm , motor123 - 1 , brake );
}

void NxtPP::motorBrake( int motor123 , bool brake ) {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;
	if( !connected )
		return;

	if( motor123 < 1 || motor123 > 3 )
		return;

	if( brake )
		NXT::Motor::BrakeOn( xcomm , motor123 - 1 );
	else
		NXT::Motor::BrakeOff( xcomm , motor123 - 1 );
}

void NxtPP::motorRotate( int motor123 , int power100 , int rotateDegrees , bool brake ) {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;
	if( !connected )
		return;

	if( motor123 < 1 || motor123 > 3 )
		return;

	if( power100 < 1 )
		return;

	if( power100 > 100 )
		power100 = 100;

	NXT::Motor::ResetRotationCount( xcomm , motor123 - 1 , false );
	NXT::Motor::GoTo( xcomm , motor123 - 1 , power100 , rotateDegrees , brake );
}

int NxtPP::motorRotateDone( int motor123 ) {
	Comm::NXTComm *xcomm = ( Comm::NXTComm * )comm;
	if( !connected )
		return( 0 );

	if( motor123 < 1 || motor123 > 3 )
		return( 0 );

	return( NXT::Motor::GetRotationCount( xcomm , motor123 - 1 ) );
}

