// *****************************************************************************
//  Copyright (C): Juan C. SanMiguel, 2015
//  Author(s): Juan C. SanMiguel
//
//  Developed at Queen Mary University of London (UK) & University Autonoma of Madrid (Spain)
//  This file is distributed under the terms in the attached LICENSE_2 file.  
//
//  This file is part of the implementation for the cost-aware coalition-based
//  tracking (CAWC) for single targets described in the paper:
//      Juan C. SanMiguel and A. Cavallaro "Cost-aware coalitions for collaborative
//      Tracker tracking", IEEE Sensors Journal, May 2015
//
//  Updated contact information:
//  - Juan C. SanMiguel - Universidad Autonoma of Madrid - juancarlos.sanmiguel@uam.es
//  - Andrea Cavallaro - Queen Mary University of London - a.cavallaro@qmul.ac.uk
//
// *****************************************************************************

#ifndef __WISECAMERACAWCTRACKER_H__
#define __WISECAMERACAWCTRACKER_H__

#include "WiseCameraPeriodicAlgo.h"
#include "WiseCameraCAWCTrackerPkt_m.h"
#include "WiseCameraCAWCTracker_utils.h"

const int MAX_SIZE_BUFFER = 10;         //!< Maximum number of neighborgs for which data is stored
const int ALARM_WAIT_NEGOTIATION  = 10; //!< Periodic alarm to check completion of the negotiation
const double MAX_UTILITY = 1;           //!< Maximum utility that cameras can provide

/*! \class WiseCameraCoalitionTracker
 *  \brief This class implements the cost-aware coalition-based tracking (CAWC)
 *         for single targets described in "JC. SanMiguel and A. Cavallaro. Cost-aware
 *          coalitions for collaborative Tracker tracking", IEEE Sensors J., May 2015
 */
class WiseCameraCAWCTracker : public WiseCameraPeriodicAlgo
{

private:
    int _camID;
    int _mode;
    std::string _testName;

    CAWC::CamTracker _tracker;                  //!< Tracker running inside each camera
    CAWC::target_initialization_t  _iniT;       //!< Structure to initialize the Tracker
    std::string _logCOAstr,_logCAMstr;

    CAWC::coalition_data_t _coa_buf;            //!< Coalition data
    CAWC::camera_data_t _cam_buf;                //!< Camera data
    std::vector<CAWC::neigbor_data_t> _nb_buf;  //!< Buffer for Neighbor data

protected:
    // Functions to be implemented from WiseCameraPeriodicAlgo class
    void at_startup();                      //!< Init internal variables. To implement in superclasses of WiseCameraPeriodicAlgo.
    void at_timer_fired(int index);         //!< Response to alarms generated by specific tracker. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_init();                         //!< Init resources. To implement in superclasses of WiseCameraPeriodicAlgo.
    void at_finishSpecific();               //!< Specific routines to execute when terminating the simulation. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_sample();                       //!< Operations at the >1st example. To implement in superclasses of WiseCameraPeriodicAlgo.
    bool at_end_sample();                   //!< Operations at the end of >1st example. To implement in superclasses of WiseCameraPeriodicAlgo.

    // Functions to be implemented from WiseBaseApplication class
    bool process_network_message(WiseApplicationPacket *);          //!< Processing of packets received from network. To implement in superclasses of WiseBaseApplication.
    void handleDirectApplicationMessage(WiseApplicationPacket *);   //!< Processing of packets received from network. To implement in superclasses of WiseBaseApplication.
    void make_measurements(const std::vector<WiseTargetDetection>&);//!< Conversion of camera detections into ordered lists of measurements for tracking. To implement in superclasses of WiseBaseApplication.

private:

    //extended functions
    bool update_data_buffer(int pos, int nodeID, int CAMID, double u, double blevel, double load, double priority, int counter);
    bool check_databuffer_ready();              //!< Checks if all data (utility) has been received from the neighbors
    bool check_manager_ack();                   //!< Checks if all cameras have sent an ACK to the new coalition manager
    bool check_manager_collaboration_data();    //!< Checks if all coalition cameras have sent the data for collaboration

    // funs to communication between cameras
    bool identify_and_announce_manager();   //!< Identifies the new manager and sends packets to the network for announcing
    bool negotiation_request_camera();      //!< Determines the next camera to join the coalition and sends a request to the network
    bool negotiation_reply();               //!< Reply to the 'join request' message by accepting or rejecting the proposal
    bool collaboration_request_data();      //!< The manager requests data from coalition cameras
    bool collaboration_send_data();         //!< The coalition cameras send the requested data to the manager
    bool collaboration_fuse();              //!< The coalition manager combines all the received data from coalition cameras
    bool collaboration_end();               //!< The coalition manager informs the cameras that coalition processing has finished

    void save_coalition_data();             //!< Saves all the generated coalition data
    void save_camera_data();                //!< Saves all the generated camera data
};

#endif // __WISECAMERACAWCTRACKER_H__
